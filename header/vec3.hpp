#include<math>
#include<stdlib.h>
#include<iostream>

class vec3{ //for storing geometric vectors and colors 
  public:
    float e[3];
    vec3() {}
    vec3(float e0,float e1, float e2){e[0]=e0;e[1]=e1;e[2]=e2}
    inline float x() const {
    return e[0];
    } //inline directly copies the function code 
    inline float y() const {
    return e[1];
    }
    inline float z() const {
    return e[2];
    }
    inline float r() const {
      return e[0];
    }
    inline float g() const{
    return e[1];
    } 
    inline float b() const{
    return e[2];
    }

    inline const vec3& operator+() const {return *this} //returns a const reference to vec3 object. just returns the vector as is 
    inline const vec3 operator-() const{return vec3(-e[0],-e[1],-e[2]);} //returns a copy of the vector but with negative values,dos not change the original object
    inline float operator[](int i)const{return e[i];}
    inline float& operator[](int i){return e[i];} //to enable both reading and writing with the same [] operator 

    inline vec3& operator +=(const vec3 &v2);
    inline vec3& operator -=(const vec3 &v2);
    inline vec3& operator *=(const vec3 &v2); // will define th4se later
    inline vec3& operator /=(const vec3 &v2;
    inline vec3& operator *=(const float t);
    inline vec3& operator /=(const float t);
}
