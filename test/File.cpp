#include <igloo/igloo_alt.h>

#include <cw/core/File.hpp>

#include "fake/FakeFile.hpp"

using namespace igloo;

Describe(AFile)
{
  It(can_be_instantiated)
  {
    FakeFile file("fakename");
  }

  It(has_a_name)
  {
    FakeFile file("ArthursQuestion.txt");
    AssertThat(file.getName(), Equals("ArthursQuestion.txt"));
  }

  It(can_be_opened)
  {
    FakeFile file("wtf");

    AssertThat(file.isOpen(), Equals(false));
    bool success = file.open();

    AssertThat(success, Equals(true));
    AssertThat(file.isOpen(), Equals(true));
  }

  It(cannot_be_opened_twice)
  {
    FakeFile file("wtf");

    AssertThat(file.open(), Equals(true));
    AssertThat(file.open(), Equals(false));
  }

  It(should_call_doOpen_if_opens)
  {
    FakeFile file("wtf");

    file.open();

    AssertThat(file.m_doOpenCalled, Equals(true));
  }

  It(can_be_closed)
  {
    FakeFile file("wtf");
    file.open();
    AssertThat(file.isOpen(), Equals(true));

    file.close();
    AssertThat(file.isOpen(), Equals(false));
  }

  It(should_call_doClose_if_close_called_on_an_opened_file)
  {
    FakeFile file("wtf");
    file.open();

    file.close();
    AssertThat(file.m_doCloseCalled, Equals(true));
  }

  It(should_not_call_doClose_if_the_file_is_closed)
  {
    FakeFile file("wtf");
    AssertThat(file.isOpen(), Equals(false));

    file.close();
    AssertThat(file.m_doCloseCalled, Equals(false));
  }

};
