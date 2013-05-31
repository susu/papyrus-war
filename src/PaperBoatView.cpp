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
  float height = 1.0f;
  // TODO load from file!
  // Winding order: Counter clockwise
  setModelVertices(
  {
    // Front Base Plane
    -1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,

     // Right upper plane
     0.0f,  1.0f, 0.0f,
     0.0f, -1.0f, -height,
     1.0f, -1.0f, 0.0f,

     // Left upper plane
     0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     0.0f, -1.0f, -height,

     // Right lower plane
     0.0f, -1.0f, -height,
    -1.0f, -1.0f, 0.0f,
     0.0f, -3.0f, 0.0f,

     // Left lower plane
     1.0f, -1.0f, 0.0f,
     0.0f, -1.0f, -height,
     0.0f, -3.0f, 0.0f,
  });

  computeNormals();
}

void PaperBoatView::show()
{
  setUpDraw();

  core::Pos modelPos = m_model->getPos();
  double x = modelPos.x;
  double y = modelPos.y;
  glm::mat4 modelMatrix = glm::translate( glm::mat4(1.0f), glm::vec3( x,y, -0.1f ) );
  sendMVP( modelMatrix );
  sendColor( 1.0, 1.0, 1.0 );

  glEnableVertexAttribArray( AttrIndex::POSITION );
  glEnableVertexAttribArray( AttrIndex::NORMAL );

  glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices() );

  glDisableVertexAttribArray( POSITION );
  glDisableVertexAttribArray( NORMAL );
}

  }
}
