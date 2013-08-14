#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/InputDistributor.hpp>

using namespace igloo;

Describe(AInputDistributor)
{
  typedef cw::core::InputDistributor::CallbackId CallbackId;
  typedef cw::core::ScrollDir ScrollDir;

  cw::core::InputDistributor dist;
  bool eventOccured;
  cw::core::ClickEvent lastEvent;

  int actualNumberOfCalls;
  int expectedNumberOfCalls;

  // It(should_be_registerable)
  void SetUp()
  {
    eventOccured = false;
    dist.registerClickedOn( [this](cw::core::ClickEvent ev)
    {
      lastEvent = ev;
      eventOccured = true;
    });
    actualNumberOfCalls = 0;
    expectedNumberOfCalls = 0;
  }

  CallbackId registerSelfCheckerCallback( cw::core::Pos expectedPos )
  {
    CallbackId id = dist.registerClickedOn( [this,expectedPos](cw::core::ClickEvent ev)
    {
      ++actualNumberOfCalls;
      AssertThat( ev.pos, Equals( expectedPos ) );
    });
    ++expectedNumberOfCalls;
    return id;
  }

  It(should_register_and_call_multiple_callbacks)
  {
    cw::core::Pos expectedPos( 100.0, 100.0 );
    registerSelfCheckerCallback( expectedPos );
    registerSelfCheckerCallback( expectedPos );
    registerSelfCheckerCallback( expectedPos );
    registerSelfCheckerCallback( expectedPos );

    dist.clickedAt( 100, 100 );
    AssertThat( actualNumberOfCalls, Equals( expectedNumberOfCalls ) );
  }

  It(should_call_the_callback_if_clickedAt_happened)
  {
    dist.clickedAt( 100, 100 );
    AssertThat( eventOccured, Equals(true) );
    AssertThat( lastEvent.pos, Equals( cw::core::Pos( 100.0, 100.0 ) ) );
  }

  It(should_return_its_callbackId)
  {
    CallbackId id;
    id = dist.registerClickedOn([](cw::core::ClickEvent){});
    if(id){}
  }

  It(should_deregister_callbacks)
  {
    cw::core::Pos expectedPos( 100.0, 100.0 );
    CallbackId id1, id2;
    id1 = registerSelfCheckerCallback( expectedPos );
    id2 = registerSelfCheckerCallback( expectedPos );

    dist.unregisterClickedOn( id2 );
    --expectedNumberOfCalls;
    dist.clickedAt( 100, 100 );

    AssertThat( actualNumberOfCalls, Equals( expectedNumberOfCalls ) );
    dist.unregisterClickedOn( id1 );
    dist.unregisterClickedOn( id2 );
  }

  It(can_register_scroll)
  {
    dist.registerScroll([](cw::core::ScrollEvent ev){});
  }

  It(should_call_scroll_callback)
  {
    bool isCalled = false;
    dist.registerScroll([&isCalled](cw::core::ScrollEvent ev)
    {
      isCalled = true;
    });
    dist.startScroll( ScrollDir::UP );
    AssertThat(isCalled,Equals(true));
  }

  It(should_call_scroll_callback_with_proper_values)
  {
    cw::core::ScrollEvent startEvent, stopEvent;
    auto cb = [&startEvent,&stopEvent](cw::core::ScrollEvent ev)
    {
      if (ev.action == cw::core::ScrollEvent::START)
        startEvent = ev;
      else
        stopEvent = ev;
    };

    dist.registerScroll(cb);

    dist.startScroll(ScrollDir::LEFT);
    AssertThat(startEvent.action, Equals(cw::core::ScrollEvent::START));
    AssertThat(startEvent.scrollDir, Equals(ScrollDir::LEFT));


    dist.stopScroll(ScrollDir::LEFT);
    AssertThat(stopEvent.action, Equals(cw::core::ScrollEvent::STOP));
    AssertThat(stopEvent.scrollDir, Equals(ScrollDir::LEFT));

    dist.startScroll(ScrollDir::RIGHT);
    dist.startScroll(ScrollDir::UP);
    dist.stopScroll(ScrollDir::RIGHT);

    AssertThat(stopEvent.action, Equals(cw::core::ScrollEvent::STOP));
    AssertThat(stopEvent.scrollDir, Equals(ScrollDir::RIGHT));
  }

  Context(if_condition_function_is_given)
  {
    typedef cw::core::ClickEvent ClickEvent;
    void SetUp()
    {
      m_called = false;
      m_callback = [this](ClickEvent)
      {
        m_called = true;
      };
    }

    It(should_not_call_clicked_callback_if_condition_is_false)
    {
      Parent().dist.registerClickedOn(m_callback,
      [](ClickEvent)
      {
        return false;
      });
      Parent().dist.clickedAt(100, 100);

      AssertThat(m_called, Equals(false));
    }

    std::function<void(ClickEvent)> m_callback;
    bool m_called;
  };
};
