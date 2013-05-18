#ifndef CW_CORE_GUARD_HPP_INC
#define CW_CORE_GUARD_HPP_INC

#include <tuple>

namespace cw
{
  namespace core
  {
    /**
     * Universal guard with delayed function call.
     * Example:
     *   auto guard = CreateGuard( @function, @params... );
     *
     * It will call the @function with parameters @params
     * when 'guard' leaves the scope.
     *
     * TODO:
     * It's noncopyable, but moveable (MoveConstructible,MoveAssignable).
     * It implies it can be used inside containers.
     */
    template<typename DestroyerCallback, typename... Args>
    class Guard
    {
        // not needed elsewhere, defined in private
        template<int ...>
        struct seq {};

        template<int N, int ...S>
        struct gens : gens< N-1, N-1, S...> {};

        template<int ...S>
        struct gens<0,S...>
        {
          typedef seq<S...> type;
        };
        template<int ...S>
        void callDestroyer(seq<S...>)
        {
          m_destroyerCallback(std::get<S>(m_tuple) ...);
        }

      public:
        Guard(DestroyerCallback cb, Args&&...args)
          : m_tuple(args...)
          , m_destroyerCallback(cb)
        {}

        ~Guard()
        {
          callDestroyer(typename gens< sizeof...(Args) >::type());
        }

        // noncopyable
        Guard(Guard&) = delete;
        Guard& operator=(Guard) = delete;

        // TODO only moveable
        Guard(Guard&&) = default;
        Guard& operator=(Guard&&) = default;
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
