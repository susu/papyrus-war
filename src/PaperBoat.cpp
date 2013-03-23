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

void PaperBoat::moveTo(double x, double y)
{
}

void PaperBoat::tick()
{
}

  }
}
