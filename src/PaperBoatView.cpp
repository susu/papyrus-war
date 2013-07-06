#include <cw/opengl/PaperBoatView.hpp>

#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <cw/core/Logger.hpp>
#include <cw/core/Pos.hpp>
#include <cw/core/PaperBoat.hpp>

#include <cw/opengl/ProjectionView.hpp>
#include <cw/opengl/Mesh.hpp>

namespace cw
{
  namespace opengl
  {

PaperBoatView::PaperBoatView( core::PaperBoatRef m, ProjectionView & projView )
  : BaseType(m,projView)
{
  Mesh mesh("objects/PaperBoat.dae", "PaperBoat");
  setModelVertices( mesh.getVertices() );

  // TODO load normals from Mesh
  computeNormals();
}

void PaperBoatView::doShow()
{
  core::Pos modelPos = m_model->getPos();
  double x = modelPos.x;
  double y = modelPos.y;
  glm::mat4 modelMatrix = glm::translate( glm::mat4(1.0f), glm::vec3( x,y, -0.1f ) );

  float orientation = float( (m_model->getCurrentOrientation()) * 180 / core::PI + 90 );

  modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(0.0f,0.0f,1.0f) );
  sendMVP( modelMatrix );
  sendColor( 1.0, 1.0, 1.0 );

  glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices() );
}

  }
}
