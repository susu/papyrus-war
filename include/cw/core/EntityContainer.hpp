#ifndef CW_CORE_ENTITY_CONTAINER_HPP_INC
#define CW_CORE_ENTITY_CONTAINER_HPP_INC

#include <memory>

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

namespace cw
{
  namespace core
  {
    template<typename T, void (T::*Method)() >
    class EntityContainer
    {
      public:
        EntityContainer() = default;
        ~EntityContainer() = default;

        EntityContainer(EntityContainer<T,Method>&) = delete;
        EntityContainer(EntityContainer<T,Method>&&) = delete;
        void operator=(EntityContainer<T,Method>) = delete;

        typedef std::shared_ptr<T> TRef;
        void add( TRef x )
        {
          m_entities.push_back( x );
        }
        void doIt()
        {
          for ( auto & i : m_entities )
          {
            CALL_MEMBER_FN(*i,Method)();
          }
        }
      private:
        std::vector< TRef > m_entities;
    };
  }
}

#undef CALL_MEMBER_FN

#endif
