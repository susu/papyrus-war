#include <igloo/igloo_alt.h>
#include <igloo/igloo.h>

#include <utility>
#include <cpp11hacks.hpp>

#include <cw/opengl/ProgramRepository.hpp>

#include "OpenGlStubs.hpp"
#include "fake/FakeFile.hpp"

using namespace igloo;
using namespace cw;

Describe(AProgramRepository)
{
  It(can_be_instantiated)
  {
    opengl::ProgramRepository repo;
  }

  Spec(shader_chains_can_be_added)
  {
    opengl::ShaderChain chain("ChainID");
    chain.addShader(GL_VERTEX_SHADER, std::make_unique<FakeFile>("someshader.glsl"));
    chain.addShader(GL_FRAGMENT_SHADER, std::make_unique<FakeFile>("somefragmentstuff.glsl"));

    opengl::ProgramRepository repo;
    repo.addShaderChain(std::move(chain));

    AssertThat(repo.hasProgram("ChainID"), Equals(true));
  }

  Spec(programs_can_be_switched)
  {
    opengl::ProgramRepository repo;
    repo.addShaderChain(opengl::ShaderChain("one"));
    repo.addShaderChain(opengl::ShaderChain("two"));

    repo.selectProgram("one");
    AssertThat(repo.getSelectedProgramId(), Equals("one"));
  }

  Spec(nothing_selected_by_default)
  {
    opengl::ProgramRepository repo;

    AssertThat(repo.getSelectedProgramId().empty(), Equals(true));
  }
};
