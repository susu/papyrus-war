#include <cw/opengl/ProjectionView.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <cw/opengl/Program.hpp>
#include <cw/opengl/GlException.hpp>

namespace cw
{
  namespace opengl
  {
const std::string MVP_MATRIX_NAME = "MVP";

ProjectionView::ProjectionView( const Program & program )
{
  int mvpId = glGetUniformLocation(program.getId(), MVP_MATRIX_NAME.c_str() );
  if ( -1 == mvpId )
  {
    throw GlException( "Uniform location '" + MVP_MATRIX_NAME +
        "': does not exist. It may can be optimized out!");
  }
  m_programId = program.getId();
  m_mvpMatrixId = mvpId;

  // TODO do not hardcode
  m_projectionMatrix = glm::perspective(
      35.0f, // degree: FoV
      4.0f / 3.0f, // ratio
      0.1f, 100.0f ); // draw depth
}

void ProjectionView::setViewMatrix( const glm::mat4& view )
{
  m_viewMatrix = view;
}

void ProjectionView::setProjectionMatrix( const glm::mat4 & projection )
{
  m_projectionMatrix = projection;
}

void ProjectionView::sendMVP( const glm::mat4 & model )
{
  glm::mat4 mvp = m_projectionMatrix * m_viewMatrix * model; // model is identity by default

  glUseProgram( m_programId );
  glUniformMatrix4fv(m_mvpMatrixId, 1, GL_FALSE, &mvp[0][0]);
}

  }
}
