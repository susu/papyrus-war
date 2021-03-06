#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <glm/gtc/matrix_transform.hpp>

#include <cw/graph/ScreenSize.hpp>

#include <cw/opengl/Program.hpp>
#include <cw/opengl/ProjectionView.hpp>

#include "OpenGlStubs.hpp"

using namespace igloo;

namespace
{
  const cw::graph::ScreenSize g_screenSize(1024,768);
}
const static std::string MVP_NAME = cw::opengl::ProjectionView::MVP_MATRIX_NAME;

static void addUniformToProgram(GLuint programId, const std::string & name)
{
  glstub::programRepo.getProgram(programId).addUniform(name);
}

Describe(the_ProjectionView)
{
  It(can_be_instantiated)
  {
    cw::opengl::Program program;
    addUniformToProgram(program.getId(), MVP_NAME);
    cw::opengl::ProjectionView projView(program,g_screenSize);
  }

  Spec(view_matrix_can_be_set_and_gotten)
  {
    cw::opengl::Program program;
    addUniformToProgram(program.getId(), MVP_NAME);
    cw::opengl::ProjectionView projView(program,g_screenSize);
    glm::mat4 view = glm::mat4(1);

    projView.setViewMatrix( view );
    AssertThat( projView.getViewMatrix(), Equals(view) );
  }

  Spec(projection_matrix_can_be_set_and_gotten_back)
  {
    cw::opengl::Program program;
    addUniformToProgram(program.getId(), MVP_NAME);
    cw::opengl::ProjectionView projView(program,g_screenSize);
    glm::mat4 projection = glm::mat4(1);

    projView.setProjectionMatrix( projection );
    AssertThat( projView.getProjectionMatrix(), Equals( projection ) );
  }

  It(should_send_MVP_matrix)
  {
    // Arrange
    cw::opengl::Program program;
    addUniformToProgram(program.getId(), MVP_NAME);
    cw::opengl::ProjectionView projView(program,g_screenSize);

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

    // Act
    projView.sendMVP();

    // Assert
    GLint mvpIndex = glGetUniformLocation(program.getId(),
                                        cw::opengl::ProjectionView::MVP_MATRIX_NAME.c_str());
    AssertThat(mvpIndex, Is().Not().EqualTo(-1));

    glm::mat4 sentMatrix =
      glstub::programRepo.getProgram( program.getId() ).getUniformMatrix4fv(mvpIndex);
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
