#ifndef INDOOR_PLANTING_LED_H
#define INDOOR_PLANTING_LED_H

/**
 * This namespace contains functions for controlling LEDs.
 */
namespace LED
{

    void blink(int digitalPin, int millisOnDuration, int millisOffDuration,
               int times);

} // namespace LED

#endif
