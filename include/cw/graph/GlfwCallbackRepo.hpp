#ifndef CW_GRAPH_GLFW_CALLBACK_REPO_HPP_INC
#define CW_GRAPH_GLFW_CALLBACK_REPO_HPP_INC

#include <vector>
#include <array>
#include <functional>

namespace cw
{
  namespace graph
  {
    class GlfwCallbackRepo
    {
      public:
        enum EventType
        {
          MOUSE_BUTTON,
          MOUSE_WHEEL,
          MOUSE_POS,
          KEY_CALLBACK,

          MAX
        };
        typedef std::function< void(int,int) > CallbackFunctionType;
        // Singleton related functions
        static void initialize();
        static void terminate();

        static GlfwCallbackRepo& instance()
        { return *m_instance; }

        // actual glfw callbacks
        static void GLFWCALL mouseButton( int button, int action );
        static void GLFWCALL keyCallback( int key, int action );
        static void GLFWCALL mousePosCallback( int x, int y );
        static void GLFWCALL mouseWheelCallback( int x );

        // methods
        void notify( EventType event, int arg1, int arg2 ) const;
        void registerCallback( EventType e, CallbackFunctionType cb );
      private:
        GlfwCallbackRepo();
        GlfwCallbackRepo(GlfwCallbackRepo&) = delete;
        void operator=(GlfwCallbackRepo&) = delete;
        void initGlfwCallbacks() const;

        static GlfwCallbackRepo * m_instance;

        typedef std::vector< CallbackFunctionType > Callbacks;
        typedef std::vector< Callbacks > CallbackTypes;

        CallbackTypes m_registeredCallbacks;
    };
  }
}

#endif
