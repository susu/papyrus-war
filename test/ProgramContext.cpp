#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>
#include "OpenGlStubs.hpp"

#include <cw/opengl/ProgramContext.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace igloo;

Describe(AProgramContext)
{
  Spec(view_unform_matrix_can_be_sent)
  {
    GLuint id = glCreateProgram();
    glstub::programRepo.getProgram(id).addAttribute("uniform_42");
    cw::opengl::ProgramContext ctx(id);
    std::vector<float> vec = { 1,2,3,4,
                               5,6,7,8,
                               9,0,1,2,
                               3,4,5,6 };
    glm::mat4 matrix = glm::make_mat4(&vec[0]);
    ctx.setUniform("uniform_42", matrix);

    AssertThat(glstub::programRepo.getProgram(id).getUnifMat(), Equals(matrix));
  }
};
