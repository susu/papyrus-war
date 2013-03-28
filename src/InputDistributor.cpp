#include <algorithm>

#include <cw/core/Logger.hpp>
#include <cw/core/InputDistributor.hpp>
#include <cw/core/Model.hpp>

namespace
{
  cw::core::Logger logger("core");
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
    std::function< void(ClickEvent) > callback )
{
  CallbackId max = getNextKey();
  m_clickedOnCallbacks[ max ] = callback;
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

InputDistributor::CallbackId InputDistributor::getNextKey() const
{
  if (m_clickedOnCallbacks.empty())
  {
    return 0;
  }
  return m_clickedOnCallbacks.rbegin()->first + 1;
}

void InputDistributor::clickedAt(int x, int y)
{
  ClickEvent event;
  event.pos.x = x;
  event.pos.y = y;
  for( auto callback : m_clickedOnCallbacks )
  {
    callback.second( event );
  }
}

void InputDistributor::zoom(ZoomDir dir)
{}

void InputDistributor::startScroll(ScrollDir dir)
{}

void InputDistributor::stopScroll()
{}

  }
}
