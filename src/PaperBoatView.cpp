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
  m_vertexBuffer.assign(
  {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  });
  glGenBuffers(1, &m_vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER,
               m_vertexBuffer.size() * sizeof(m_vertexBuffer[0]),
               &m_vertexBuffer[0],
               GL_STATIC_DRAW );

}

void PaperBoatView::show()
{
  core::Pos modelPos = m_model->getPos();
  double x = modelPos.x;
  double y = modelPos.y;
  glm::mat4 modelMatrix = glm::translate( glm::mat4(1.0f), glm::vec3( x,y, 0.0f ) );
  sendMVP( modelMatrix );

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  glVertexAttribPointer(getVertexPosModelSpaceId(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}

  }
}
