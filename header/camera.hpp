#ifndef CAMERAH
#define CAMERAH

#include "ray.hpp"

class camera{
  public:
    camera(){ // making a view port or a like a window through light rays will be thrown out
      lower_left_corner=vec3(-2.0,-1.0,-1.0);
      horizontal=vec3(4.0,0.0,0.0);
      vertical=vec3(0.0,2.0,0.0);
      origin=vec3(0.0,0.0,0.0);
    }
    ray get_ray(float u,float v){
      return ray(origin,lower_left_corner + u*horizontal + v*vertical-origin);} // creating rays that go through evey pixel of the viewport
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif

