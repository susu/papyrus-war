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
  : m_paperBoatModel(m)
  , m_projView(projView)
{
  m_model.assign(
  {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  });
  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER,
               m_model.size() * sizeof(m_model[0]),
               &m_model[0],
               GL_STATIC_DRAW );

  int attrLoc = glGetAttribLocation(m_projView.getProgramId(), "vertexPos_modelspace");
  if (attrLoc == -1) throw GlException( "vertexPos_modelspace is not a valid attrib!" );
  m_vertexPositionModelSpaceId = attrLoc;
}

void PaperBoatView::show()
{
  core::Pos modelPos = m_paperBoatModel->getPos();
  double x = modelPos.x;
  double y = modelPos.y;
  glm::mat4 modelMatrix = glm::translate( glm::mat4(1.0f), glm::vec3( x,y, 0.0f ) );
  m_projView.sendMVP( modelMatrix );

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(m_vertexPositionModelSpaceId,3,GL_FLOAT,GL_FALSE,0,nullptr);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}

  }
}
