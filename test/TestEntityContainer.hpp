#ifndef TEST_ENTITY_CONTAINER_HPP_INC
#define TEST_ENTITY_CONTAINER_HPP_INC

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/EntityContainer.hpp>

class Dummy;
typedef std::shared_ptr<Dummy> DummyRef;
class Dummy
{
  public:
    static DummyRef create()
    {
      return DummyRef( new Dummy );
    }
    void method()
    {
      m_called = true;
    }
    bool isCalled() const
    {
      return m_called;
    }
  private:
    bool m_called = false;
};

using namespace igloo;

Describe(the_EntityContainer)
{
  It(can_store_stuff)
  {
    cw::core::EntityContainer<Dummy, &Dummy::method> container;
    container.add( Dummy::create() );
  }

  It(can_call_method_specified_in_template_arg)
  {
    cw::core::EntityContainer<Dummy, &Dummy::method> container;
    auto dummy = Dummy::create();
    container.add( dummy );
    container.doIt();
    AssertThat( dummy->isCalled(), Equals(true) );
  }
};

#endif
