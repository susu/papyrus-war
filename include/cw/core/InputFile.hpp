#ifndef CW_CORE_INPUT_FILE_HPP_INC
#define CW_CORE_INPUT_FILE_HPP_INC

#include <cw/core/File.hpp>

namespace cw
{
  namespace core
  {
    class InputFile : public File
    {
      public:
        InputFile(const std::string & fname)
          : File(fname)
        {}

        virtual ~InputFile() = default;

        /**
         *  Reads all available data from file
         */
        virtual std::string readAll() = 0;
        virtual char readChar() = 0;

        virtual bool isEndOfFile() const = 0;
    };
  }
}

#endif
