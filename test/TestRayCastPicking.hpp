#ifndef TEST_RAY_CAST_PICKING_HPP_INC
#define TEST_RAY_CAST_PICKING_HPP_INC

#include <cw/opengl/RayCastPicking.hpp>
#include <cw/graph/ScreenSize.hpp>

Describe(ARayCastPicking)
{
  Ref<cw::opengl::Program> prog;
  Ref<cw::opengl::ProjectionView> projView;
  Ref<cw::opengl::RayCastPicking> picking;

  void SetUp()
  {
    prog.reset( new cw::opengl::Program );
    projView.reset( new cw::opengl::ProjectionView(*prog) );
    picking.reset( new cw::opengl::RayCastPicking(
        *projView, cw::graph::ScreenSize(1024,768) ) );
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

#endif
