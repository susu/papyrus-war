#include <cw/opengl/ProjectionView.hpp>

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
}

  }
}
