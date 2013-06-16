#include <cw/opengl/GlfwWindow.hpp>

#include <mutex>
#include <cw/core/Logger.hpp>
#include <cw/opengl/GlException.hpp>


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

GlfwWindow* getGlfwWindow(GLFWwindow * win)
{
  return static_cast<GlfwWindow*>(glfwGetWindowUserPointer(win));
}

extern "C"
{
  static void keyCallback(GLFWwindow * win, int key, int scancode, int action, int mods)
  {
    getGlfwWindow(win)->keyPressed(key,action);
  }

  static void mouseButtonCallback(GLFWwindow * win, int button, int action, int mods)
  {
    getGlfwWindow(win)->mouseButtonPressed(button,action);
  }

  static void scrollCallback(GLFWwindow * win, double xOffset, double yOffset)
  {
    getGlfwWindow(win)->mouseScrolled(xOffset,yOffset);
  }

  static void cursorPosCallback(GLFWwindow * win, double xPos, double yPos)
  {
    getGlfwWindow(win)->cursorMoved(xPos,yPos);
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

  // store the class inside the window for callbacks
  glfwSetWindowUserPointer(m_window.get(), this);

  registerInternalCallbacks();

  glfwMakeContextCurrent(m_window.get());
}

GlfwWindow::~GlfwWindow()
{}

void GlfwWindow::registerInternalCallbacks()
{
  LOG_DEBUG("Registering GLFW callbacks...");
  glfwSetCursorPosCallback( m_window.get(), &cursorPosCallback );
  glfwSetKeyCallback( m_window.get(), &keyCallback );
  glfwSetMouseButtonCallback( m_window.get(), &mouseButtonCallback );
  glfwSetScrollCallback( m_window.get(), &scrollCallback );
}

int GlfwWindow::getKeyStatus(int key) const
{
  return glfwGetKey(m_window.get(), key);
}

int GlfwWindow::shouldBeClosed() const
{
  return glfwWindowShouldClose(m_window.get());
}

void GlfwWindow::swapBuffers()
{
  glfwSwapBuffers(m_window.get());
}

void GlfwWindow::setKeyCallback(KeyPressedCallback cb)
{
  m_keyPressed = std::move(cb);
}

void GlfwWindow::setCursorMovedCallback(CursorMovedCallback cb)
{
  m_cursorMoved = std::move(cb);
}

void GlfwWindow::setMouseButtonCallback(MouseButtonPressedCallback cb)
{
  m_mouseButtonPressed = std::move(cb);
}

void GlfwWindow::setScrollCallback(MouseScrolledCallback cb)
{
  m_mouseScrolled = std::move(cb);
}

void GlfwWindow::keyPressed(int key, int action)
{
  if (m_keyPressed)
    m_keyPressed(key,action);
}

void GlfwWindow::mouseButtonPressed(int button, int action)
{
  if (m_mouseButtonPressed)
    m_mouseButtonPressed(button,action);
}

void GlfwWindow::mouseScrolled(double xOffset, double yOffset)
{
  if (m_mouseScrolled)
    m_mouseScrolled(xOffset,yOffset);
}

void GlfwWindow::cursorMoved(double xPos, double yPos)
{
  if (m_cursorMoved)
    m_cursorMoved(xPos,yPos);
}


void GlfwWindow::setInputMode(int id, int value)
{
  glfwSetInputMode(m_window.get(), id, value);
}
  }
}
