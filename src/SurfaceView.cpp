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
{
  setModelVertices(
  {
    -1.0,  1.0, 0.0,
    -1.0, -1.0, 0.0,
     1.0, -1.0, 0.0,

    -1.0,  1.0, 0.0,
     1.0,  1.0, 0.0,
     1.0, -1.0, 0.0
  });
}

void SurfaceView::show()
{
  glm::mat4 modelMatrix = glm::scale( glm::mat4(1.0f), glm::vec3( 4.0f, 3.0f, 0.0f ) );

  sendMVP( modelMatrix );
  sendColor( 0.145f, 0.427f, 0.782f );

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  glVertexAttribPointer(getVertexAttribute( VERTEXPOS_ATTR ), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableVertexAttribArray(0);
}

  }
}
