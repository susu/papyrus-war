#include <cw/opengl/Sun.hpp>

#include <cw/opengl/Program.hpp>

namespace
{
  /// uniform variable names in shader
  const char* SUN_COLOR_NAME = "sunLight.vColor";
  const char* AMBIENT_INTENSITY_NAME = "sunLight.fAmbientIntensity";
  const char* SUN_DIRECTION_NAME = "sunLight.vDirection";
}

namespace cw
{
  namespace opengl
  {

Sun::Sun( Program & program, core::Pos3d pos )
  : m_resLocator( program.getId() )
  , m_pos( pos )
{
  updateVariables();
}


void Sun::setPos( core::Pos3d pos )
{
  m_pos = pos;
}

void Sun::updateVariables()
{
  glm::vec3 vSunPos( m_pos.x, m_pos.y, m_pos.z );
  m_resLocator.setUniform( SUN_COLOR_NAME, glm::vec3(1.0f, 1.0f, 1.0f));
  m_resLocator.setUniform( AMBIENT_INTENSITY_NAME, 0.1f);
  m_resLocator.setUniform( SUN_DIRECTION_NAME, -glm::normalize(vSunPos));
}
  }
}
