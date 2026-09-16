#ifndef HITABLEH
#define HITABLEH 

#include "ray.hpp"
class material;

struct hit_record{
  float t;
  vec3 p;
  vec3 normal;
  material *mat_ptr; // to tell us how rays will react to different material,if a RAY hits the surface this pointer will be set to point to that point on the material 
};

class hitable{
  public:
    virtual bool hit(const ray& r,float t_min,float t_max,hit_record& rec) const =0;
};
// hit only counts if tmin<t<tmax
#endif
