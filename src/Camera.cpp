#include <cw/opengl/Camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <cw/core/Logger.hpp>

#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/GlException.hpp>

namespace
{
  cw::core::Logger logger("opengl");
}

namespace cw
{
  namespace opengl
  {
Camera::Camera( ProjectionView & projView )
  : m_projView(projView)
  , m_pos(0,0,0)
  , m_lookAt(0,0,1)
  , m_orientation(HEADS_UP)
{
}

void Camera::setPos( float x, float y, float z )
{
  m_pos = glm::vec3( x, y, z );
  sendViewMatrix();
}

void Camera::lookAt( float x, float y, float z )
{
  m_lookAt = glm::vec3( x, y, z );
  sendViewMatrix();
}

void Camera::orientation( Orientation orient )
{
  if (HEADS_UP == orient)
  {
    m_orientation = glm::vec3(0,1,0);
  }
  else
  {
    LOG_ERROR("Orientation not supported: ", orient);
    throw GlException( "Orientation not supported!" );
  }
  sendViewMatrix();
}

void Camera::sendViewMatrix()
{
  m_projView.setViewMatrix( glm::lookAt( m_pos, m_lookAt, m_orientation ) );
  m_projView.sendMVP();
}

  }
}
