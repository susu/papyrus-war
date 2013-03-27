#include <cw/opengl/PaperBoatView.hpp>

#include <cw/core/Logger.hpp>
#include <cw/opengl/Shader.hpp>

namespace
{
  cw::core::Logger logger("view");
}

namespace cw
{
  namespace opengl
  {

PaperBoatViewRef PaperBoatView::create( core::PaperBoatRef model )
{
  return PaperBoatViewRef( new PaperBoatView(model) );
}

PaperBoatView::PaperBoatView( core::PaperBoatRef m )
{
  m_shaderProgramId = loadShaders( "shaders/vertex.glsl",
                                   "shaders/fragment.glsl" );
  m_model.assign(
  {
    -1.0,  1.0, 0.0,
     1.0,  1.0, 0.0,
    -1.0, -1.0, 0.0,
  });
  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER,
               m_model.size() * sizeof(m_model[0]),
               &m_model[0],
               GL_STATIC_DRAW );
  LOG(DEBUG) << "GL buffers set up.";
}

void PaperBoatView::show()
{
  glUseProgram( m_shaderProgramId );

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}

  }
}
