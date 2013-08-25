#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/IFStreamFile.hpp>

using namespace igloo;

// NOTE: it is not really a unit test , because using real files
// (rather an integration one)
Describe(AnIFStreamFile)
{
  typedef cw::core::IFStreamFile IFStreamFile;

  It(can_be_instantiated)
  {
    IFStreamFile ifs("whatever");
  }

  It(can_open_an_existing_file)
  {
    IFStreamFile ifs("data/testfile.txt");
    ifs.open();

    AssertThat(ifs.isOpen(), Equals(true));
  }

  It(cannot_open_a_not_existing_file)
  {
    IFStreamFile ifs("data/hahahahahahhaaaaxasdflkjashdfl");
    ifs.open();

    AssertThat(ifs.isOpen(), Equals(false));
  }

  It(can_read_all_available_data_from_a_file)
  {
    IFStreamFile ifs("data/testfile.txt");
    ifs.open();

    auto data = ifs.readAll();

    AssertThat(data,
               EqualsContainer(std::string(
                 "testdata in testfile\n"
                 "lol\n"
                 "more line\n"
                 "-\n")));
    AssertThat(ifs.isEndOfFile(), Equals(true));
  }

  It(can_read_one_char_from_file)
  {
    IFStreamFile ifs("data/testfile.txt");
    ifs.open();

    auto first = ifs.readChar();
    auto second = ifs.readChar();

    AssertThat(first, Equals('t'));
    AssertThat(second, Equals('e'));

    AssertThat(ifs.isEndOfFile(), Equals(false));
  }

};
