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
    cw::core::EntityContainer<Dummy> container;
    container.add( Dummy::create() );
  }

  It(can_call_method_specified_in_template_arg)
  {
    // Arrange
    cw::core::EntityContainer<Dummy> container;
    auto dummy = Dummy::create();
    container.add( dummy );

    // Act
    container.each([](DummyRef & d)
    {
      d->method();
    });

    // Assert
    AssertThat( dummy->isCalled(), Equals(true) );
  }
};
