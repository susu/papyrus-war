#ifndef CW_CORE_IFSTREAM_FILE_HPP_INC
#define CW_CORE_IFSTREAM_FILE_HPP_INC

#include <fstream>
#include <cw/core/InputFile.hpp>

namespace cw
{
  namespace core
  {
    class IFStreamFile : public InputFile
    {
      public:
        IFStreamFile(const std::string & fname);
        virtual ~IFStreamFile();

        /**
         *  pre-req: opened file
         *  return value is undefined if eof reached
         */
        std::string readAll() override;

        /**
         *  pre-req: opened file
         *  return value is undefined if eof reached
         */
        char readChar() override;

        bool isEndOfFile() const override;
      private:
        bool doOpen() override;
        void doClose() override;

        std::ifstream m_ifs;
    };
  }
}

#endif
