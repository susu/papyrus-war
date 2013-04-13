#ifndef CW_CORE_POS3D_HPP_INC
#define CW_CORE_POS3D_HPP_INC

namespace cw
{
  namespace core
  {
    struct Pos3d
    {
      double x,y,z;

      Pos3d(double px, double py, double pz)
        : x(px), y(py), z(pz)
      {}
    };

    inline bool operator==(Pos3d const & l, Pos3d const & r)
    {
      return equals(l.x, r.x) && equals(l.y,r.y) && equals(l.z,r.z);
    }

    inline std::ostream& operator<<(std::ostream & o, Pos3d const & pos)
    {
      o << "Pos3d(" << pos.x << "," << pos.y << "," << pos.z << ")";
      return o;
    }
  }
}

#endif