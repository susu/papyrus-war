#include <cw/opengl/PaperBoatView.hpp>

#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cw/core/Logger.hpp>
#include <cw/core/Pos.hpp>
#include <cw/core/PaperBoat.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/Shader.hpp>
#include <cw/opengl/ProjectionView.hpp>

namespace
{
  cw::core::Logger logger("view");
}

namespace cw
{
  namespace opengl
  {

PaperBoatView::PaperBoatView( core::PaperBoatRef m, ProjectionView & projView )
  : BaseType(m,projView)
{
  setModelVertices(
  {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,

     0.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f, -1.0f, -0.5f,

     0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     0.0f, -1.0f, -0.5f,
  });
}

void PaperBoatView::show()
{
  core::Pos modelPos = m_model->getPos();
  double x = modelPos.x;
  double y = modelPos.y;
  glm::mat4 modelMatrix = glm::translate( glm::mat4(1.0f), glm::vec3( x,y, -0.1f ) );
  sendMVP( modelMatrix );
  sendColor( 1.0, 1.0, 1.0 );

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  glVertexAttribPointer(getVertexPosModelSpaceId(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glDrawArrays(GL_TRIANGLES, 0, 9);
  glDisableVertexAttribArray(0);
}

  }
}
