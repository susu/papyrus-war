#include <cw/opengl/SurfaceView.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <cw/core/Logger.hpp>

namespace
{
  cw::core::Logger logger("opengl");
}

namespace cw
{
  namespace opengl
  {

SurfaceView::SurfaceView( Ref< core::Surface> surface, ProjectionView& projView )
  : BaseType( surface, projView )
  , m_camera( projView )
{
  m_camera.setPos( 0, 0, -13 );
  m_camera.lookAt( 0, 0, 0 );
  m_camera.orientation( Camera::HEADS_UP );

  setModelVertices(
  {
    -1.0,  1.0, 0.0,
    -1.0, -1.0, 0.0,
     1.0, -1.0, 0.0,

    -1.0,  1.0, 0.0,
     1.0, -1.0, 0.0,
     1.0,  1.0, 0.0
  });
  computeNormals();
}

void SurfaceView::show()
{
  setUpDraw();

  glm::mat4 modelMatrix = glm::scale( glm::mat4(1.0f), glm::vec3( 5.0f, 5.0f, 1.0f ) );

  sendMVP( modelMatrix );
  sendColor( 0.145f, 0.427f, 0.782f );

  glEnableVertexAttribArray( POSITION );
  glEnableVertexAttribArray( NORMAL );

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableVertexAttribArray( POSITION );
  glDisableVertexAttribArray( NORMAL );
}

  }
}
