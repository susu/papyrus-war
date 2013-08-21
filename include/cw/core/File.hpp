#ifndef CW_CORE_FILE_HPP_INC
#define CW_CORE_FILE_HPP_INC

#include <string>

namespace cw
{
  namespace core
  {
    /**
     *  Common base for all kind of files.
     *  Assuming all kind of file has name and can be opened/closed
     */
    class File
    {
      public:
        // The ctor will NOT open the file!
        File(const std::string & fileName);

        // The dtor will NOT close the file!
        virtual ~File();

        std::string getName() const;
        bool isOpen() const;

        bool open(); // calls doOpen
        void close(); // calls doClose
      private:
        virtual bool doOpen() = 0;
        virtual void doClose() = 0;

        std::string m_fileName;
        bool m_opened;
    };
  }
}

#endif
