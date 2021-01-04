#include <BH1750.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "LED.hpp"
#include "Timer.hpp"

BH1750 lightSensor(0x23);
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	Wire.begin();
	lightSensor.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

	lcd.init();
	lcd.backlight();
	lcd.display();
}

Timer lightSensorTimer(5000, true);

bool updateLCD = true;
float latestLux = 0;
int latestVol = 0;

void loop()
{
	lightSensorTimer.count();
	if (lightSensorTimer.isFinish())
	{
		LED::blink(LED_BUILTIN, 100, 100, 3);
		latestLux = lightSensor.readLightLevel();
		updateLCD = true;
	}

	if (updateLCD)
	{
		updateLCD = false;

		lcd.clear();
		lcd.print("Light:");

		lcd.setCursor(2, 1);
		lcd.print(latestLux);
		lcd.print(" lx");

		lcd.setCursor(0, 2);
		lcd.print("Sound:");
		lcd.setCursor(2, 3);
		lcd.print(latestVol);
	}
}