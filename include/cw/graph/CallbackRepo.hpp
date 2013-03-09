#ifndef CW_GRAPH_CALLBACK_REPO_INTERFACE_HPP_INC
#define CW_GRAPH_CALLBACK_REPO_INTERFACE_HPP_INC

namespace cw
{
  namespace graph
  {
    /**
     * Common interface for mouse and keyboard callbacks
     */
    class CallbackRepo
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

        virtual ~CallbackRepo() {}
        virtual void registerCallback( EventType e, CallbackFunctionType cb ) = 0;
    };
  }
}

#endif
