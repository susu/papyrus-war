#ifndef CW_CORE_GUARD_HPP_INC
#define CW_CORE_GUARD_HPP_INC

#include <tuple>

namespace cw
{
  namespace core
  {
    template<typename DestroyerCallback, typename... Args>
    class Guard
    {
      public:
        Guard(DestroyerCallback cb, Args&&...args)
          : m_tuple(args...)
          , m_destroyerCallback(cb)
        {}
        ~Guard()
        {
          // TODO template black magic needed
          //   need to build a parameter pack of numbers, and unpack them
          //   http://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer
          //m_destroyerCallback( m_tuple );
        }
      private:
        std::tuple<Args...> m_tuple;
        DestroyerCallback m_destroyerCallback;
    };

    template<typename DestroyerCallback, typename... Args>
    Guard<DestroyerCallback, Args...> CreateGuard(DestroyerCallback cb, Args&&...args)
    {
      return Guard<DestroyerCallback,Args...>(cb,std::forward<Args>(args)...);
    }
  }
}

#endif
