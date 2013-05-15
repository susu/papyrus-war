#include <cw/opengl/Gpu.hpp>

#include <GL/glew.h>

namespace
{
  const int NVIDIA_TOTAL_DEDICATED_MEM = 0x9047;
  const int NVIDIA_AVAILABLE_DEDICATED_MEM = 0x9049;
}

namespace cw
{
  namespace opengl
  {
    namespace gpu
    {
      int getDedicatedMemory()
      {
        int memory = 0;
        glGetIntegerv(NVIDIA_TOTAL_DEDICATED_MEM, &memory);
        return memory;
      }

      int getAvailabelDedicatedMemory()
      {
        int memory = 0;
        glGetIntegerv(NVIDIA_AVAILABLE_DEDICATED_MEM, &memory);
        return memory;
      }
    }
  }
}
