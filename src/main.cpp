#include<iostream>
#include "../header/vec3.hpp"
#include "../header/ray.hpp"
#include "../header/camera.hpp"
#include "../header/sphere.hpp"
#include "../header/hitable.hpp"
#include "../header/hitablelist.hpp"
#include "../header/material.hpp"
#include "../header/random_scene.hpp"
// so now we want to find if a ray falls on a sphere or not(we are creating a sphere).A point on a ray or a line falls on the sphere if its coordiates satisfy the equation of the sphere. The point being p(t) as we mentioned earlier, so after substituting those values we get a quadratic equation with only t being the variable. THe solition of a quadratic equation is simple

bool hit_sphere(const vec3& center,float radius,const ray& r){
  vec3 oc=r.origin()-center; // centre of the sphere 
  float a = dot(r.direction(),r.direction()); //squared lenght of the rays direction vector accorfing to quadratic equation
  float b = 2.0 * dot(oc,r.direction()); // the 2ab part
  float c = dot(oc,oc)-radius*radius; //  + c ; a*a + 2ab + c
  
  float discriminant= b*b - 4*a*c;
  if(discriminant < 0){
    return -1.0;
  } //no solution if discriminant is less than 0 
  else{
    return (-b - sqrt(discriminant) / 2.0 *a); // finding roots formula 
  }
}
vec3 color(const ray& r,hitable *world,int depth){  // if ray hits the object, bounce it back to a random direction
   if(depth >= 50)
     return vec3(0,0,0);
  hit_record rec;
  if(world->hit(r,0.0,MAXFLOAT,rec)){
// (not needed, we dont assume that every surface is lambertian anymore)    vec3 target = rec.p + rec.normal +random_in_unit_sphere();  // R=p+n+e, the random bounce's direction 

  //  return 0.5*color(ray(rec.p,target-rec.p),world); // recurssion for the new bounced ray
  ray scattered;
  vec3 attenuation;
  if(rec.mat_ptr->scatter(r, rec, attenuation, scattered)) // we askin the material if the ray is hit or not 
            return attenuation * color(scattered, world,depth+1); // like how many sphere hit in the world and the scattered rays
        else
            return vec3(0, 0, 0);       // ray dies so return black color 
  }                                                                 
  
   // vec3 unit_direction=unit_vector(r.direction());
   // float t=0.5*(unit_direction.y()+1.0);

   // return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
  
  // we make the image/background like this- top-blue;middle - bluish white; bottom-white 
   float t =  hit_sphere(vec3(0,0,-1),0.5,r);// centre,radius and the ray ; t is the hitpoint 
   if(t > 0.0){
   vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1)); // normal for sphere at which the ray hits; making it a unit vector cuz we only care about its direction 
     return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1); // squashing the values between 0 to 1;
   } // if the ray hits the sphere, it returns red at vec(1,0,0);
  
  vec3 unit_direction = unit_vector(r.direction()); // direction of the unit vector defined in vec3 
   t = 0.5*(unit_direction.y() + 1.0); // to make the range of t = 0 to 1, t is like a blend factor; to make the calculations easier 
   return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0); // gives a combinaation of blue and white  depending on t,red is alway 1 so it doesnt matter muchj
}

int main(){

  vec3 lookfrom(3,3,2);
  vec3 lookat(0,0,-1);
  float dist_to_focus = (lookfrom - lookat).length();
  float aperture=0.0;
  int nx =800; //length of the screen
  int ny=400; // breadth of the screen
  int ns=100; // number of pixels          
  camera cam(lookfrom,lookat,vec3(0,1,0),20,float(nx)/float(ny),aperture,dist_to_focus);
  std::cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
  hitable* world = random_scene();
  vec3 lower_left_corner(-2.0,-1.0,-1.0);
  vec3 horizontal(4.0,0.0,0.0);
  vec3 vertical(0.0,2.0,0.0);
  vec3 origin(0.0,0.0,0.0);
  for(int j=ny-1;j>=0;j--){ //loop through rows
   for(int i=0;i<nx;i++){ //loop through columns in each row
     //vec3 col(float(i)/float(nx),float(j)/float(ny),0.2); //red,green and blue(always 0.2)
     vec3 col(0,0,0);
     for(int s=0;s<ns;s++){
       float u=float(i+drand48()) / float(nx);
       float v=float(j+drand48()) / float(ny);
       ray r=cam.get_ray(u,v); // one ray for one pixel, hence no of rays for no of pixelse 
       col += color(r,world,0);
     }    
     col /= float(ns);
     col = vec3(
         sqrt(col[0]),
         sqrt(col[1]),
         sqrt(col[2])
         ); 
     int ir = int(255.99*col[0]);
     int ig = int(255.99*col[1]);
     int ib = int(255.99*col[2]);
     std::cout<<ir<<" "<<ig<<" "<<ib<<"\n";
   }
  }
}
