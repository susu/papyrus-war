#include <iostream>

#include <cw/core/Logger.hpp>
#include <cw/opengl/GlException.hpp>
#include <cw/opengl/OpenGlLoop.hpp>

using namespace cw::opengl;

int main()
{
  // TODO logger initialization!
  try
  {
    OpenGlLoop mainloop;
    mainloop.run();
    std::cout << "Thanks for playing!" << std::endl;
  }
  catch(const GlException & ex)
  {
    LOG_EXCEPTION(ex);
  }
  // TODO logger teardown?
}
