#include <cw/core/PaperBoat.hpp>

namespace cw
{
  namespace core
  {

PaperBoatRef PaperBoat::create(double x, double y)
{
  return PaperBoatRef( new PaperBoat );
}

PaperBoat::PaperBoat()
  : RectangleUnit(Pos{0,0}, Pos{0,0})
{}

PaperBoat::~PaperBoat()
{}

void PaperBoat::moveTo(double x, double y)
{
}

void PaperBoat::tick()
{
}

  }
}
