#ifndef FAKEFILE_YSW08I51
#define FAKEFILE_YSW08I51

#include <cw/core/InputFile.hpp>

class FakeFile : public cw::core::InputFile
{
  public:
    FakeFile(const std::string & name)
      : cw::core::InputFile(name)
      , m_doOpenCalled(false)
      , m_doCloseCalled(false)
    {}

    bool doOpen() override
    {
      m_doOpenCalled = true;
      return true;
    }

    void doClose() override
    {
      m_doCloseCalled = true;
    }

    std::string readAll() override
    {
      return "";
    }

    char readChar() override
    {
      return ' ';
    }

    bool isEndOfFile() const override
    {
      return false;
    }

    bool m_doOpenCalled;
    bool m_doCloseCalled;
};

#endif


