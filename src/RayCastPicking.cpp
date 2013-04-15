#include <glm/gtc/matrix_transform.hpp>

#include <cw/core/Logger.hpp>
#include <cw/core/Line.hpp>

#include <cw/opengl/RayCastPicking.hpp>
#include <cw/opengl/ProjectionView.hpp>

namespace
{
  cw::core::Logger logger("opengl");
}

namespace cw
{
  namespace opengl
  {

const double NEAR_END = 0.1;
const double FAR_END = 0.99;

RayCastPicking::RayCastPicking( ProjectionView & projView,
                                const graph::ScreenSize & scr)
  : m_projView(projView)
  , m_screenSize(scr)
  , m_viewPort( 0.0f, 0.0f, scr.x, scr.y )
{}

RayCastPicking::~RayCastPicking()
{}

core::Pos3d RayCastPicking::unProject( core::Pos p )
{
  core::Pos shifted = transformClickToBottomLeftCorner( p );

  core::Pos3d nearEnd = unProjectScreenPos( glm::vec3( shifted.x, shifted.y, NEAR_END ) );
  core::Pos3d farEnd = unProjectScreenPos( glm::vec3( shifted.x, shifted.y, FAR_END ) );

  auto line = core::Line::createFromPoints( nearEnd, farEnd );
  return line.getPointAtZ( 0.0 );
}

core::Pos RayCastPicking::transformClickToBottomLeftCorner( core::Pos p ) const
{
  return core::Pos( p.x, m_screenSize.y - p.y );
}

core::Pos3d RayCastPicking::unProjectScreenPos( const glm::vec3 & screenPos ) const
{
  glm::vec3 unproj = glm::unProject( screenPos, m_projView.getViewMatrix(),
                                     m_projView.getProjectionMatrix(),m_viewPort );
  return core::Pos3d( unproj.x, unproj.y, unproj.z );
}

  }
}
