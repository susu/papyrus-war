#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/opengl/Shader.hpp>

#include "OpenGlStubs.hpp"
#include "fake/FakeFile.hpp"

using namespace igloo;

Describe(the_Shader)
{
  void SetUp()
  {
    glstub::shaderRepo.clear();
  }

  It(can_be_instantiated)
  {
    FakeFile file("some_shader.glsl");
    cw::opengl::Shader shader(file, GL_VERTEX_SHADER);
    AssertThat( glstub::shaderRepo.shaders(), HasLength(1) );
  }

  It(can_compile_the_shader_source)
  {
    FakeFile file("some_shader.glsl");
    cw::opengl::Shader shader(file, GL_VERTEX_SHADER);
    shader.compile();
    AssertThat( glstub::shaderRepo.shaders().back().compiled, Equals(true) );
  }

  It(can_check_the_shader_state)
  {
    FakeFile file("some_shader.glsl");
    cw::opengl::Shader shader(file, GL_VERTEX_SHADER);
    shader.compile();
    shader.check();

    AssertThat( glstub::shaderRepo.shaders().back().checked, Equals(true) );
  }
};
