#ifndef TEST_GLM_PICKING_HPP_INC
#define TEST_GLM_PICKING_HPP_INC

#include <cw/opengl/GlmPicking.hpp>

Describe(AGlmPicking)
{
  Ref<cw::opengl::Program> prog;
  Ref<cw::opengl::ProjectionView> projView;
  Ref<cw::opengl::GlmPicking> picking;
  void SetUp()
  {
    prog.reset( new cw::opengl::Program );
    projView.reset( new cw::opengl::ProjectionView(*prog) );
    picking.reset( new cw::opengl::GlmPicking );
  }

  It(can_respond_same_pixels_if_matrices_are_identities)
  {
    cw::core::Pos click( 230, 123 );
    auto worldCoord = picking->unProject( click );

    AssertThat( worldCoord, Equals( cw::core::Pos3d( 230.0, 123.0, 0.0 ) ) );
  }
};

#endif
