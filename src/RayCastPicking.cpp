#include <glm/gtc/matrix_transform.hpp>

#include <cw/core/Logger.hpp>

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
  // TODO refactor this function
  core::Pos shifted( p.x, m_screenSize.y - p.y );

  glm::vec3 screenPos( shifted.x, shifted.y, NEAR_END );
  glm::vec3 nearEnd = glm::unProject( screenPos,
                                      m_projView.getViewMatrix(),
                                      m_projView.getProjectionMatrix(),
                                      m_viewPort );

  screenPos = glm::vec3( shifted.x, shifted.y, FAR_END );
  glm::vec3 farEnd = glm::unProject( screenPos,
                                      m_projView.getViewMatrix(),
                                      m_projView.getProjectionMatrix(),
                                      m_viewPort );
  core::Pos3d n( nearEnd.x, nearEnd.y, nearEnd.z );
  core::Pos3d f( farEnd.x, farEnd.y, farEnd.z );

  core::Pos3d dirVec = n - f;
  LOG(DEBUG) << "Found points: " << n << ", " << f;
  LOG(DEBUG) << "Direction vector: " << dirVec;

  // x = x1 + at
  // y = y1 + bt
  // z = z1 + ct

  // 0 = z1 + ct
  // z1 = -ct
  // -z1/c = t

  // find the point, where z == 0
  double t = - farEnd.z / dirVec.z;

  double x = farEnd.x + dirVec.x * t;
  double y = farEnd.y + dirVec.y * t;
  double z = farEnd.z + dirVec.z * t;

  return core::Pos3d( x, y, z );
}

  }
}
