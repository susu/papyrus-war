#include <algorithm>

#include <cw/core/Logger.hpp>
#include <cw/core/InputDistributor.hpp>
#include <cw/core/Unit.hpp>

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

void InputDistributor::registerUnit(UnitRef unit)
{
  m_units.insert(unit);
}

void InputDistributor::clickedAt(int x, int y)
{
  for ( const UnitRef & unit : m_units )
  {
    if ( unit->isOver(x,y) )
    {
      if ( !unit->hasFocus() )
      {
        unit->setFocus(true);
      }
    }
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
