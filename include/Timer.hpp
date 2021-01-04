#ifndef INDOOR_PLANTING_TIMER_H
#define INDOOR_PLANTING_TIMER_H

/**
 * This class is used for timing periodic events
 */
class Timer
{
public:
  /**
   * Create a new timer, the timer will finish counting according to the given interval.
   * If the timer is a repeating timer, it will reset itselt if the remanining time is used up.
   */
  Timer(int millisInterval, bool repeating);

  /**
   * Reset the remaining time to the given interval
   */
  void reset();

  /**
   * Subtract the remaining time for the amount of time that has passed since the last time this
   * method was called.
   */
  void tick();

  /**
   * Return true if the remaiing time is used up.
   */
  bool finished();

private:
  bool repeated;
  int millisInterval, millisLastUpdate, millisRemaing;
};

#endif
