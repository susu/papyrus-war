#include <iostream>

#include <cw/core/Logger.hpp>
#include <cw/opengl/GlException.hpp>
#include <cw/opengl/OpenGlLoop.hpp>

using namespace cw::opengl;

int main()
{
  // TODO logger initialization!
  std::cout << "Main started." << std::endl;
  try
  {
    LOG_DEBUG(" ----------- Logger started. ----------- ");
    OpenGlLoop mainloop;
    mainloop.run();
    std::cout << "Thanks for playing!" << std::endl;
  }
  catch(const GlException & ex)
  {
    LOG_EXCEPTION(ex);
  }
  catch(const cw::core::BaseException & ex)
  {
    LOG_EXCEPTION(ex);
  }
  // TODO logger teardown?
  LOG_DEBUG(" ----------- End of logging. ----------- ");
}
