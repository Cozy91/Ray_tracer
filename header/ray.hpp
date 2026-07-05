#ifndef RAYH // if RAYH is not defined  
#define RAYH // then define it; empty macro, header gaurd,will define vec3 only if its not already defined  
#include "../header/vec3.hpp"

class ray{
     public:
       vec3 A;
       vec3 B;
       ray(){}
       ray(const vec3& a,const vec3& b){A = a; B=b; }
       vec3 origin () const  {return A;} // p(t) = A+B(t) ; B is the direction
       vec3 direction() const {return B;}
       vec3 point_at_parameter(float t) const {return A + t*B; }
};

#endif //ends the definition if its not defined; ends ifndef 
