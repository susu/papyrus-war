#include <cw/core/PaperBoat.hpp>

namespace cw
{
  namespace core
  {

PaperBoat::PaperBoat(double x, double y)
  : RectangleUnit(Pos{x,y}, Pos{10,10})
{}

PaperBoat::~PaperBoat()
{}

void PaperBoat::tick()
{
}

void PaperBoat::setPos( Pos p )
{
  m_pos = p;
}

  }
}
