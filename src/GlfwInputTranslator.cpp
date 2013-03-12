#include <cw/graph/GlfwInputTranslator.hpp>

#include <cw/core/UnifiedInputHandler.hpp>

namespace cw
{
  namespace graph
  {

GlfwInputTranslator::GlfwInputTranslator(cw::core::UnifiedInputHandler & inputHandler)
  : m_inputHandler(inputHandler)
{}

GlfwInputTranslator::~GlfwInputTranslator()
{}

  }
}
