#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/opengl/Plane.hpp>

#include <glm/ext.hpp>

using namespace igloo;
using namespace cw;

Describe(APlane)
{
  It(should_return_the_normal)
  {
    opengl::Plane plane( glm::vec3(1,1,0), glm::vec3(-1,1,0), glm::vec3(1,0,0) );

    auto orthoVec = glm::vec3(1,0,0);
    AssertThat( glm::dot( plane.getNormal(), orthoVec ), Equals( 0.0 ) );
  }
};
