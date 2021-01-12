#include <Arduino.h>
#include <BH1750.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <Wire.h>

#include "LED.hpp"
#include "secrets.hpp" // This file is not commited to the repository

// Debug serial baudrate
const uint16_t BAUD_RATE = 9600;

// Initialize light sensor
BH1750 lightSensorBH1750(0x23);

// Intialize communication channels with the ESP8266 Wifi module
SoftwareSerial espSerial(2, 3);
WiFiEspClient espWifiClient;
PubSubClient pubsubClient(
	AWS_ENDPOINT,
	8883,
	[](char *topic, byte *payload, unsigned int length) {
		Serial.print("[");
		Serial.print(topic);
		Serial.print("[");
		Serial.print(" : ");
		for (int i = 0; i < length; i++)
		{
			Serial.print((char)payload[i]);
		}
		Serial.println();
	},
	espWifiClient);

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	Wire.begin();
	Serial.begin(BAUD_RATE);

	// The sensor will only take a measurement when we ask it to do so, using HIGH_RES_MODE
	lightSensorBH1750.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

	// Communicate with the ESP8266 module at baudrate of 9600, the default baudrate of the ESP8266 module is 115200.
	// Connect the wifi module with the arduino board an flash a bare minimum firmware onto the arduino, wire the wifi
	// module with the arduino. Connect the arduino to a power source and start serial monitor at 115200 baudrate using
	// "Both NL & CR" as character return type. Use the following commands to check the wifi module and change the baudrate
	// -- AT => Check if the module has started
	// -- AT+RST => Restart the module
	// -- AT+GRM => Check module info
	// -- AT+UART_DEF=<baud>,8,1,0,0 => Change baudrate
	espSerial.begin(BAUD_RATE);
	// initialize ESP module
	WiFi.init(&espSerial);
	// Connect to wifi network
	uint8_t status = WiFi.status();
	// check for the presence of the shield
	if (status == WL_NO_SHIELD)
	{
		Serial.println("WiFi shield not present");
		// don't continue
		while (true)
			;
	}
	while (status != WL_CONNECTED)
	{
		Serial.print("Attempting to connect to WPA SSID: ");
		Serial.println(WL_INDOOR_PLANTING_SSID);
		// Connect to WPA/WPA2 network
		status = WiFi.begin(WL_INDOOR_PLANTING_SSID, WL_INDOOR_PLANTING_PASS);
	}

	LED::blink(LED_BUILTIN, 200, 200, 5);
}

// Sensors' measurements
float latestLux = 0;

void loop()
{
	if (!pubsubClient.connected())
	{
		// Loop until we're reconnected
		while (!pubsubClient.connected())
		{
			Serial.print("Attempting MQTT connection...");
			if (pubsubClient.connect("arduinoClient"))
			{
				Serial.println("connected");
				pubsubClient.publish("status", "on");
				pubsubClient.subscribe("commands");
			}
			else
			{
				Serial.print("failed, rc=");
				Serial.print(pubsubClient.state());
				Serial.println(" try again in 5 seconds");
				delay(5000);
			}
		}
	}
}