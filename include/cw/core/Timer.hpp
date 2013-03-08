#ifndef CW_CORE_TIMER_HPP_INC
#define CW_CORE_TIMER_HPP_INC

#include <functional>
#include <vector>

double operator "" _nanosec(unsigned long long val)
{
  return val * 1e-9;
}

double operator "" _microsec(unsigned long long val)
{
  return val * 1000_nanosec;
}

double operator "" _millisec(unsigned long long val)
{
  return val * 1000_microsec;
}

double operator "" _sec(unsigned long long val)
{
  return val;
}

namespace cw
{
  namespace core
  {
    /**
     * independent timer implementation
     */
    class Timer
    {
      public:
        // TODO shouldn't be an own type instead of double?
        typedef double TimeType;
        typedef std::function<void()> SimpleCallback;
        typedef std::function<void(TimeType)> DiffCallback;
        explicit Timer(TimeType start);
        ~Timer();

        TimeType getElapsed() const;
        void updateCurrentTime(TimeType newTime);
        void setUpTimer(TimeType p, SimpleCallback cb);
      private:
        struct TimerShot
        {
          const TimeType length;
          TimeType lastShot;
          bool periodic = false;
          SimpleCallback simpleCallback;
          //DiffCallback   diffCallback;
          TimerShot(TimeType len, TimeType setupTime, SimpleCallback cb)
            : length(len), lastShot(setupTime), simpleCallback(cb) {}
        };
        typedef std::vector< TimerShot > TimerShots;

        void shotTimers();

        TimeType m_startTime;
        TimeType m_currentTime;
        TimerShots m_timerShots;
    };
  }
}

#endif
