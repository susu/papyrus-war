#include <algorithm>

#include <cw/core/Logger.hpp>
#include <cw/core/InputDistributor.hpp>
#include <cw/core/Model.hpp>

namespace
{

template<typename MapType>
auto getNextKey(const MapType & cbMap) -> decltype(cbMap.rbegin()->first)
{
  if (cbMap.empty())
  {
    return 0;
  }
  return cbMap.rbegin()->first + 1;
}

}

namespace cw
{
  namespace core
  {

InputDistributor::InputDistributor()
{}

InputDistributor::~InputDistributor()
{}

InputDistributor::CallbackId InputDistributor::registerClickedOn(
    ClickedOnCallback callback,
    ClickedOnCondition condition)
{
  CallbackId max = getNextKey( m_clickedOnCallbacks );
  m_clickedOnCallbacks[ max ] = {callback, condition};
  return max;
}

void InputDistributor::unregisterClickedOn( CallbackId id )
{
  auto toBeDeleted = m_clickedOnCallbacks.find(id);
  if ( m_clickedOnCallbacks.end() != toBeDeleted )
  {
    m_clickedOnCallbacks.erase(toBeDeleted);
  }
}

InputDistributor::CallbackId InputDistributor::registerScroll(
    ScrollCallback callback)
{
  CallbackId key = getNextKey( m_scrollCallbacks );
  m_scrollCallbacks[key] = callback;
  return key;
}

void InputDistributor::clickedAt(int x, int y)
{
  ClickEvent event;
  event.pos.x = x;
  event.pos.y = y;
  for( auto callback : m_clickedOnCallbacks )
  {
    if (!callback.second.second) // no cond. function was set
    {
      callback.second.first( event ); // callback
    }
    else if ( callback.second.second(event) ) // condition is OK
    {
      callback.second.first( event ); // callback
    }
  }
}

void InputDistributor::zoom(ZoomDir dir)
{}

void InputDistributor::startScroll(ScrollDir dir)
{
  ScrollEvent event;
  event.scrollDir = dir;
  event.action = ScrollEvent::START;

  for(auto callback : m_scrollCallbacks)
  {
    callback.second(event);
  }
}

void InputDistributor::stopScroll(ScrollDir dir)
{
  ScrollEvent event;
  event.scrollDir = dir;
  event.action = ScrollEvent::STOP;

  for(auto callback : m_scrollCallbacks)
  {
    callback.second(event);
  }
}

  }
}
