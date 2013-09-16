#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/MeasureUnits.hpp>
#include <cw/opengl/VertexBuffer.hpp>

#include "openglstub/OpenGlMemoryStub.hpp"

using namespace igloo;

Describe(AVertexBuffer)
{
  It(can_be_instantiated_with_data_amount_to_be_allocated)
  {
    cw::opengl::VertexBuffer buffer(cw::MegaByte(10));
    auto index = buffer.getIndex();

    AssertThat(buffer.getAllocatedSize(), Equals(cw::MegaByte(10)));
    AssertThat(OpenGlMemoryStub::instance().getVBO(index).size, Equals(cw::MegaByte(10)));
  }

};
