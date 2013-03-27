#ifndef CW_OPENGL_GLFW_CALLBACK_REPO_HPP_INC
#define CW_OPENGL_GLFW_CALLBACK_REPO_HPP_INC

#include <vector>
#include <array>
#include <functional>

#include <cw/graph/CallbackRepo.hpp>

namespace cw
{
  namespace opengl
  {
    class GlfwCallbackRepo : public graph::CallbackRepo
    {
      public:
        // Singleton related functions
        static void initialize();
        static void terminate();

        static GlfwCallbackRepo& instance()
        { return *m_instance; }

        // methods
        GlfwCallbackRepo(GlfwCallbackRepo&) = delete;
        void operator=(GlfwCallbackRepo&) = delete;

        virtual void registerCallback( EventType e, CallbackFunctionType cb );
      private:
        typedef std::vector< CallbackFunctionType > Callbacks;
        typedef std::vector< Callbacks > CallbackTypes;

        GlfwCallbackRepo();

        static void GLFWCALL mouseButton( int button, int action );
        static void GLFWCALL keyCallback( int key, int action );
        static void GLFWCALL mousePosCallback( int x, int y );
        static void GLFWCALL mouseWheelCallback( int x );

        void initGlfwCallbacks() const;
        void notify( EventType event, int arg1, int arg2 ) const;

        static GlfwCallbackRepo * m_instance;
        CallbackTypes m_registeredCallbacks;
    };
  }
}

#endif
