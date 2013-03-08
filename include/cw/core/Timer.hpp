#ifndef CW_CORE_TIMER_HPP_INC
#define CW_CORE_TIMER_HPP_INC

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
        typedef double TimeType;
        explicit Timer(TimeType start);
        ~Timer();

        TimeType getElapsed() const;
    };
  }
}

#endif
