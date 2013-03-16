#include <cw/core/RectangleUnit.hpp>

namespace cw
{
  namespace core
  {

RectangleUnit::RectangleUnit(Pos pos, Pos size)
  : m_focus(false)
  , m_pos(pos)
  , m_size(size)
{}

bool RectangleUnit::hasFocus() const
{
  return m_focus;
}

void RectangleUnit::setFocus(bool focus)
{
  m_focus = focus;
}

bool RectangleUnit::isOver(double x, double y) const
{
  return ( m_pos.x < x && x < m_pos.x + m_size.x ) &&
         ( m_pos.y < y && y < m_pos.y + m_size.y );
}

Pos RectangleUnit::getPos() const
{
  return m_pos;
}

  }
}
