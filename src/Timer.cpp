#include "Timer.hpp"
#include <Arduino.h>

Timer::Timer(int millisInterval, bool repeated)
{
  this->repeated = repeated;
  this->millisInterval = millisInterval;
}

void Timer::reset()
{
  int millisInterval = this->millisInterval;
  this->millisRemaing = millisInterval;
}

void Timer::tick()
{
  /*
   * Update the remaining time using the time duration since it is last updated
   * until now
   */

  bool repeated = this->repeated;
  int millisInterval = this->millisInterval;
  int millisRemaining = this->millisRemaing;
  int millisLastUpdate = this->millisLastUpdate;

  if (repeated && millisRemaining <= 0)
  {
    this->reset();
  }

  int millisCurrent = millis();
  this->millisRemaing -= millisCurrent - millisLastUpdate;
  this->millisLastUpdate = millisCurrent;
}

bool Timer::finished()
{
  /*
   * Check if the timer is finish
   */
  return this->millisRemaing <= 0;
}
