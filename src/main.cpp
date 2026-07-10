#include<iostream>
#include "../header/vec3.hpp"
#include "../header/ray.hpp"


// so now we want to find if a ray falls on a sphere or not(we are creating a sphere).A point on a ray or a line falls on the sphere if its coordiates satisfy the equation of the sphere. The point being p(t) as we mentioned earlier, so after substituting those values we get a quadratic equation with only t being the variable. THe solition of a quadratic equation is simple

bool hit_sphere(const vec3& center,float radius,const ray& r){
  vec3 oc=r.origin()-center; // centre of the sphere 
  float a = dot(r.direction(),r.direction()); //squared lenght of the rays direction vector accorfing to quadratic equation
  float b = 2.0 * dot(oc,r.direction()); // the 2ab part
  float c = dot(oc,oc)-radius*radius; //  + c ; a*a + 2ab + c
  
  float discriminant= b*b - 4*a*c;
  return(discriminant > 0); //dont want tangent cases; when the ray is just tangent to the sphere 
}

vec3 color(const ray& r){
  // we make the image/background like this- top-blue;middle - bluish white; bottom-white 
  if(hit_sphere(vec3(0,0,-1),0.5,r)){ // centre,radius and the ray 
    return vec3(1,0,0); // if the ray hits the sphere, it returns red at vec(1,0,0);
  }
  vec3 unit_direction = unit_vector(r.direction()); // direction of the unit vector defined in vec3 
   float t = 0.5*(unit_direction.y() + 1.0); // to make the range of t = 0 to 1, t is like a blend factor; to make the calculations easier 
   return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0); // gives a combinaation of blue and white  depending on t,red is alway 1 so it doesnt matter muchj
}

int main(){
  int nx =200; //length of the screen
  int ny=100; // breadth of the screen
  std::cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
  vec3 lower_left_corner(-2.0,-1.0,-1.0);
  vec3 horizontal(4.0,0.0,0.0);
  vec3 vertical(0.0,2.0,0.0);
  vec3 origin(0.0,0.0,0.0);
  for(int j=ny-1;j>=0;j--){ //loop through rows
   for(int i=0;i<nx;i++){ //loop through columns in each row
     // vec3 col(float(i)/float(nx),float(j)/float(ny),0.2); //red,green and blue(always 0.2)
     float u=float(i)/float(nx);
     float v=float(j)/float(ny);
     ray r(origin,lower_left_corner+u*horizontal + v*vertical);
     vec3 col=color(r);
     int ir = int(255.99*col[0]);
     int ig = int(255.99*col[1]);
     int ib = int(255.99*col[2]);
     std::cout<<ir<<" "<<ig<<" "<<ib<<"\n";
   }
  }
}
