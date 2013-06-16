#ifndef CW_OPENGL_GLFW_WINDOW_HPP_INC
#define CW_OPENGL_GLFW_WINDOW_HPP_INC

#include <GLFW/glfw3.h>

#include <memory>
#include <functional>

#include <cw/graph/ScreenSize.hpp>

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
        void waitEvents();
        int getKeyStatus(int key) const;
        int shouldBeClosed() const;

        // @{callback types
        typedef std::function<void(int,int)> KeyPressedCallback;
        typedef std::function<void(int,int)> MouseButtonPressedCallback;
        typedef std::function<void(double,double)> MouseScrolledCallback;
        typedef std::function<void(double,double)> CursorMovedCallback;
        // @}

        // @{ callback setters, one can register callbacks here
        // NOTE: call setter again will overwrite the previous callback
        //       for each callbacktype
        void setKeyCallback( KeyPressedCallback );
        void setMouseButtonCallback( MouseButtonPressedCallback );
        void setScrollCallback( MouseScrolledCallback );
        void setCursorMovedCallback( CursorMovedCallback );
        // @}

        // @{ actual callbacks, in production code you should not call them
        void keyPressed(int key, int action);
        void mouseButtonPressed(int button, int action);
        void mouseScrolled(double xOffset, double yOffset);
        void cursorMoved(double xPos, double yPos);
        // @}
      private:
        typedef std::function<void(GLFWwindow*)> DeleterFunction;
        typedef std::unique_ptr<GLFWwindow, DeleterFunction> WindowRef;

        void registerInternalCallbacks();

        //@{ user registrable callbacks
        KeyPressedCallback m_keyPressed;
        MouseButtonPressedCallback m_mouseButtonPressed;
        MouseScrolledCallback m_mouseScrolled;
        CursorMovedCallback m_cursorMoved;
        //@}

        WindowRef m_window;
    };
  }
}

#endif
