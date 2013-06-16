#ifndef CW_OPENGL_GLFW_WINDOW_HPP_INC
#define CW_OPENGL_GLFW_WINDOW_HPP_INC

#include <memory>
#include <functional>

#include <cw/graph/ScreenSize.hpp>

struct GLFWwindow;

namespace cw
{
  namespace opengl
  {
    /**
     *  Wrapper around GLFWwindow
     */
    class GlfwWindow
    {
      public:
        GlfwWindow(graph::ScreenSize scrSize, const std::string & title);
        ~GlfwWindow();

        GlfwWindow(GlfwWindow&) = delete;
        GlfwWindow& operator=(GlfwWindow&) = delete;

        GlfwWindow(GlfwWindow&&) = default;
        GlfwWindow& operator=(GlfwWindow&&) = default;

        graph::ScreenSize getSize() const;
        void setTitle(const std::string & newTitle);

        void setInputMode(int flag, int value);
        void swapBuffers();
        int getKeyStatus(int key) const;
        void waitEvents();

        void setMouseButtonCallback( std::function<void(int,int)> );
        void setCursorPosCallback( std::function<void(int,int)> );
        void setKeyCallback( std::function<void(int,int)> );
        void setScrollCallback( std::function<void(int)> );

      private:
        typedef std::function<void(GLFWwindow*)> DeleterFunction;
        typedef std::unique_ptr<GLFWwindow, DeleterFunction> WindowRef;

        WindowRef m_window;
    };
  }
}

#endif
