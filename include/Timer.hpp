#ifndef INDOOR_PLANTING_TIMER_H
#define INDOOR_PLANTING_TIMER_H

class Timer
{
public:
  Timer(int millisInterval, bool repeated);
  void reset();
  void count();
  bool isFinish();

private:
  bool repeated;
  int millisInterval, millisLastUpdate, millisRemaing;
};

#endif
