#include <cw/core/Timer.hpp>

namespace cw
{
  namespace core
  {

Timer::Timer( TimeType start )
  : m_startTime(start)
  , m_currentTime(start)
{}

Timer::~Timer()
{}

Timer::TimeType Timer::getElapsed() const
{
  return m_currentTime - m_startTime;
}

void Timer::updateCurrentTime(TimeType newTime)
{
  // TODO ENFORCE( newTime >= m_currentTime, "Invalid time update request!" );
  m_currentTime = newTime;
  shotTimers();
}

void Timer::shotTimers()
{
  for( auto & shot : m_timerShots )
  {
    if ( shot.lastShot + shot.length < getElapsed() )
    {
      shot.simpleCallback();
      shot.lastShot = getElapsed();
    }
  }
}

void Timer::setUpTimer(TimeType length, SimpleCallback cb)
{
  m_timerShots.push_back( TimerShot(length, getElapsed(), cb) );
}

  }
}
