#include <igloo/igloo_alt.h>

#include <cw/core/CommandDispatcher.hpp>
#include <cw/core/InputDistributor.hpp>

#include "fake/PickingStub.hpp"

using namespace igloo;
using namespace cw;

namespace fake
{
  class InputDistributorFake : public core::InputDistributor
  {
    public:
      InputDistributorFake(const fake::PickingStub & pickingStub)
        : core::InputDistributor(pickingStub)
      {}
  };
}

Describe(ACommandDispatcher)
{
  fake::PickingStub m_pickingStub;
  fake::InputDistributorFake m_inputDistributor;
  core::CommandDispatcher::ModelContainer m_models;

  ACommandDispatcher()
    : m_inputDistributor(m_pickingStub)
  {}

  It(can_be_instantiated)
  {
    core::CommandDispatcher dispatcher(m_inputDistributor, m_models);
  }
};
