#ifndef CW_OPENGL_PROGRAM_REPOSITORY_HPP_INC
#define CW_OPENGL_PROGRAM_REPOSITORY_HPP_INC

#include <vector>
#include <memory>

#include <unordered_map>

#include <cw/core/InputFile.hpp>
#include <cw/core/Logger.hpp>
#include <cw/opengl/Program.hpp>

namespace cw
{
  namespace opengl
  {
    class ShaderChain
    {
      public:
        ShaderChain(const std::string & chainId);

        const std::string& getId()
        { return m_chainId; }

        void addShader(GLuint shaderType, std::unique_ptr<core::InputFile> file);
        /**
         *  Adds stored shaders to @program
         *  NOTE: removes all shader from the chain!
         */
        void addShadersToProgram(Program & prog);
      private:
        ShaderChain(ShaderChain&);
        ShaderChain& operator=(ShaderChain&);

        std::string m_chainId;
        std::unordered_map< GLuint, std::unique_ptr<core::InputFile> > m_inputFiles;
    };

    class ProgramRepository
    {
      public:
        ProgramRepository();

        void addShaderChain(ShaderChain && chain);

        bool hasProgram(const std::string & chainId) const;
        void selectProgram(const std::string & chainId);
        std::string getSelectedProgramId() const;
      private:
        struct ProgramWithId
        {
          std::string id;
          opengl::Program program;
        };
        typedef std::vector<ProgramWithId> Programs;

        Programs::const_iterator findProgram(const std::string & id) const;
        Programs::iterator findProgram(const std::string & id);

        Programs m_programs;
        ProgramWithId * m_currentProgram;
    };
  }
}

#endif
