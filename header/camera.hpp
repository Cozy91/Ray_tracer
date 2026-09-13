#ifndef CAMERAH
#define CAMERAH

#include "ray.hpp"
// taking a while ahh disk around origin to project rays from
vec3 random_in_unit_disk()  {
    vec3 p;
    do{
      p = 2.0*vec3(drand(48),drand48(),0) - vec3(1,1,0);
    } while(dot(p,p) >= 1.0);

    return p;
}

class camera{
  public:
    camera(vec3 lookform,vec3 lookat,vec3 vup,float ufov,float aspect,float aperture,float focus_dist){ // making a view port or a like a window through light rays will be thrown out
                                                                          lens_radius=aperture/2;
      vec3 u,v,w; //different vectors for 3 axis 

      float theta=vfov*M_PI/180;  //degrees to radians 
      float half_height=tan(theta/2);      //half the viewport height 
      float half_width=aspect*half_height;
      origint = lookform; //where the camera at 
      w=unit_vector(lookfrom - lookat);
      u=unit_vector(cross(vup,w));
      v=cross(w,u);
      lower_left_corner=vec3(-half_width,-half_height,-1.0);
      horizontal=vec3(2*half_width,0.0,0.0);
      vertical=vec3(0.0,2*half_height,0.0);
    
    }
    ray get_ray(float u,float v){
      vec3 rd = lens_radius*random_in_unit_disk();
      vec3 offset = u * rd.x() + v * rd.y();
      return ray(origin+offset,lower_left_corner + u*horizontal + v*vertical-origin-offset);} // creating rays that go through evey pixel of the viewport
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    float lens_radius;
};
#endif

