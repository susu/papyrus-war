#include <cw/core/Line.hpp>


namespace cw
{
  namespace core
  {

Line::Line( Pos3d directionVec, Pos3d fixPoint )
  : m_dirVec(directionVec)
  , m_fixPoint(fixPoint)
{}

Line::~Line()
{}

Line Line::createFromPoints( Pos3d one, Pos3d two )
{
  Pos3d dirVec = one - two;
  return Line( dirVec, two );
}

Pos3d Line::getPointAtZ( double z ) const
{
  double t = ( z - m_fixPoint.z ) / m_dirVec.z;
  return m_fixPoint + m_dirVec * t;
}

  }
}
