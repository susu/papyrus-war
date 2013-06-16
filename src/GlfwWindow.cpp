#include <cw/opengl/GlfwWindow.hpp>

#include <GLFW/glfw3.h>
#include <cw/opengl/GlException.hpp>

#include <mutex>

namespace cw
{
  namespace opengl
  {

static int ANTIALIASING = 4;
static int GL_VERSION_MAJOR = 3;
static int GL_VERSION_MINOR = 2;

static std::once_flag s_flag;

static void initGlfw()
{
  if ( !glfwInit() )
  {
    THROW( GlException, "Failed to initialize GLFW!" );
  }
}

GlfwWindow::GlfwWindow(graph::ScreenSize scrSize, const std::string & title)
{
  std::call_once(s_flag,initGlfw);

  glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);

  m_window.get_deleter() = [](GLFWwindow * win){ glfwDestroyWindow(win); };
  m_window.reset(glfwCreateWindow(scrSize.x,
                                  scrSize.y,
                                  title.c_str(),
                                  nullptr,
                                  nullptr));
  if (!m_window)
  {
    THROW( GlException,"Failed to open GLFW window!");
  }
  glfwMakeContextCurrent(m_window.get());
}

GlfwWindow::~GlfwWindow()
{}

int GlfwWindow::getKeyStatus(int key) const
{
  return glfwGetKey(m_window.get(), key);
}

void GlfwWindow::swapBuffers()
{
  glfwSwapBuffers(m_window.get());
}

void GlfwWindow::setKeyCallback(std::function<void (int, int)>)
{}

void GlfwWindow::setCursorPosCallback(std::function<void (int, int)>)
{}

void GlfwWindow::setInputMode(int id, int value)
{
  glfwSetInputMode(m_window.get(), id, value);
}

void GlfwWindow::setMouseButtonCallback(std::function<void (int, int)>)
{}

void GlfwWindow::setScrollCallback(std::function<void (int)>)
{}

  }
}
