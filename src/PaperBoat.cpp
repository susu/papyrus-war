#include <cw/core/PaperBoat.hpp>

namespace cw
{
  namespace core
  {

const static Moving::Config s_paperBoatConfig =
{
  8.0, // rot.speed
  0.2  // travelspeed
};

PaperBoat::PaperBoat(double x, double y)
  : m_moving(s_paperBoatConfig,Pos(x,y),0.0_rad)
{}

PaperBoat::~PaperBoat()
{}

void PaperBoat::tick(double diffTime)
{
  m_moving.tick(diffTime);
}


const Pos & PaperBoat::getPos() const
{
  return m_moving.getCurrentPos();
}

void PaperBoat::setMoveTarget(const Pos & p)
{
  m_moving.setTarget(p);
}

  }
}
