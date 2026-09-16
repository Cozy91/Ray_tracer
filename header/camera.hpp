#ifndef CAMERAH
#define CAMERAH

#include "ray.hpp"
// taking a whole ahh disk around origin to project rays from
vec3 random_in_unit_disk()  {
    vec3 p;
    do{
      p = 2.0*vec3(drand48(),drand48(),0) - vec3(1,1,0);
    } while(dot(p,p) >= 1.0);

    return p;
}

class camera{
  public:
    vec3 u,v,w; //different vectors for 3 axis
    camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist){ // making a view port or a like a window through light rays will be thrown out
      lens_radius=aperture/2;
      float theta=vfov*M_PI/180;  //degrees to radians 
      float half_height=tan(theta/2);      //half the viewport height 
      float half_width=aspect*half_height;
      origin = lookfrom; //where the camera at 
      w=unit_vector(lookfrom - lookat);
      u=unit_vector(cross(vup,w));
      v=cross(w,u);
      lower_left_corner = origin
                  - half_width * focus_dist * u
                  - half_height * focus_dist * v
                  - focus_dist * w;

      horizontal = 2 * half_width * focus_dist * u;
      vertical = 2 * half_height * focus_dist * v;
    }
    ray get_ray(float s,float t){
      vec3 rd = lens_radius*random_in_unit_disk();//random point on the circular cam 
      vec3 offset = u * rd.x() + v * rd.y();  //shifting the origin 
      return ray(
           origin+offset, //shifted origin
          lower_left_corner + s*horizontal + t*vertical-origin-offset);} //direction of the ray ----- creating rays that leaves the camera
                                                                                          
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    float lens_radius;
};
#endif

