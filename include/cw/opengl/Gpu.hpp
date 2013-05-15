#ifndef CW_OPENGL_GPU_HPP_INC
#define CW_OPENGL_GPU_HPP_INC

namespace cw
{
  namespace opengl
  {
    /* GPU hardware info functions
     * @note: supports only nvidia on PC
     */
    namespace gpu
    {
      // returns the total GPU dedicated memory in kb
      int getDedicatedMemory();

      // returns the currently unused GPU dedicated memory in kb
      int getAvailabelDedicatedMemory();
    }
  }
}
#endif
