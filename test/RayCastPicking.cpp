#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Types.hpp>

#include <cw/opengl/RayCastPicking.hpp>
#include <cw/opengl/Program.hpp>
#include <cw/opengl/ProjectionView.hpp>

#include <cw/graph/ScreenSize.hpp>

#include "OpenGlStubs.hpp"

using namespace igloo;

namespace
{
  const cw::graph::ScreenSize g_screenSize(1024,768);
}

Describe(ARayCastPicking)
{
  Ref<cw::opengl::Program>::R prog;
  Ref<cw::opengl::ProjectionView>::R projView;
  Ref<cw::opengl::RayCastPicking>::R picking;

  void SetUp()
  {
    prog.reset( new cw::opengl::Program );
    glstub::programRepo.getProgram(prog->getId()).addUniform(cw::opengl::ProjectionView::MVP_MATRIX_NAME);
    projView.reset( new cw::opengl::ProjectionView(*prog,g_screenSize) );
    picking.reset( new cw::opengl::RayCastPicking(
        *projView, g_screenSize) );
  }

  It(can_return_the_shifted_coords_if_matrices_are_identities)
  {
    projView->setViewMatrix( glm::mat4(1) );
    projView->setProjectionMatrix( glm::mat4(1) );

    cw::core::Pos click(0, 0);

    auto result = picking->unProject( click );

    double shiftedX = click.x - 1024/2;
    double shiftedY = 768/2 - click.y;

    shiftedX /= 512;
    shiftedY /= 384;
    AssertThat( result, Equals( cw::core::Pos3d( shiftedX, shiftedY, 0.0 ) ) );
  }

};
