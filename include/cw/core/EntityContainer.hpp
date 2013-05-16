#ifndef CW_CORE_ENTITY_CONTAINER_HPP_INC
#define CW_CORE_ENTITY_CONTAINER_HPP_INC

#include <memory>
#include <vector>

namespace cw
{
  namespace core
  {
    template<typename T>
    class EntityContainer
    {
      public:
        EntityContainer() = default;
        ~EntityContainer() = default;

        EntityContainer(EntityContainer<T>&) = delete;
        EntityContainer(EntityContainer<T>&&) = delete;
        void operator=(EntityContainer<T>) = delete;

        typedef std::shared_ptr<T> TRef;
        void add( TRef x )
        {
          m_entities.push_back( x );
        }
        template<typename Func>
        void each(Func func)
        {
          for ( auto & i : m_entities )
          {
            func(i);
          }
        }
      private:
        std::vector< TRef > m_entities;
    };
  }
}

#undef CALL_MEMBER_FN

#endif
