#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <glm/gtc/matrix_transform.hpp>

#include <cw/opengl/Program.hpp>
#include <cw/opengl/ProjectionView.hpp>

#include "OpenGlStubs.hpp"

using namespace igloo;

Describe(the_ProjectionView)
{
  It(can_be_instantiated)
  {
    cw::opengl::Program program;
    cw::opengl::ProjectionView projView(program);
  }

  Spec(view_matrix_can_be_set_and_gotten)
  {
    cw::opengl::Program program;
    cw::opengl::ProjectionView projView(program);
    glm::mat4 view = glm::mat4(1);

    projView.setViewMatrix( view );
    AssertThat( projView.getViewMatrix(), Equals(view) );
  }

  Spec(projection_matrix_can_be_set_and_gotten_back)
  {
    cw::opengl::Program program;
    cw::opengl::ProjectionView projView(program);
    glm::mat4 projection = glm::mat4(1);

    projView.setProjectionMatrix( projection );
    AssertThat( projView.getProjectionMatrix(), Equals( projection ) );
  }

  It(should_send_MVP_matrix)
  {
    cw::opengl::Program program;
    cw::opengl::ProjectionView projView(program);

    glm::mat4 viewMatrix = glm::lookAt(
        generateRandomVec3(),
        generateRandomVec3(),
        generateRandomVec3() );

    glm::mat4 projectionMatrix = glm::perspective(
      55.0f, // degree: FoV
      7.0f / 3.0f, // ratio
      1.1f, 150.0f ); // draw depth

    projView.setViewMatrix( viewMatrix );
    projView.setProjectionMatrix( projectionMatrix );

    projView.sendMVP();

    glm::mat4 sentMatrix =
      glstub::programRepo.getProgram( glstub::lastProgram ).getUnifMat();
    AssertThat( sentMatrix, Equals( projectionMatrix * viewMatrix ) );
  }

  std::mt19937 engine;

  float generateRandomFloat()
  {
    std::uniform_int_distribution<uint32_t> rng(1, 1000);
    double divider = 1000;
    return rng( engine ) / divider;
  }

  glm::vec3 generateRandomVec3()
  {
    return glm::vec3( generateRandomFloat(),
                      generateRandomFloat(),
                      generateRandomFloat());
  }
};
