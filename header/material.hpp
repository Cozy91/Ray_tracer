#include "vec3"
#includ  "ray.hpp"

class material{
  public:
    vec3 albedo;
    float fuzz;
    virtual bool scatter(const ray& r_in,const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

        // attenuation writes the color after hit, scattered creates a new bounded ray after the incident one

class lambertian: public material{ // for diffuse surfaces,diffuse surface that reflects the light a which is called albedo of the materil
        public:
          lambertian(const vec3& a):albedo(a){}
          virtual bool scatter(const ray& r_in, const hit_record& rec,vec3& attenuation,ray& scattered) const {
            vec3 target=rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p,target-rec.p);
            attenuation = albedo; // albedo is like what kinda color the material will reflect
           return true;
          }

};

class metal:public material{
  public:
    metal(const vec3& a,float f): albedo(a){ 
      if(f<1){
      fuzz = f; 
      } 
      else {fuzz=1;}
      }
  virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation, ray& scattered) const {
      vec3 reflected =reflect(unit_vector(r_in.direction()),rec.normal); // PERFECT reflection calculating, dot product ans shit, defined in vec3.hpp
      scattered = ray(rec.p,reflected);
      attenuation=albedo;
      return dot(scattered.direction(),rec.normal())>0; // error handling for rays going into  the surface
    }
  //  vec3 albedo;
   // float fuzz;
};
class dielectric:public material{
  public:
    dielectric(float ri) : ref_idx(ri){}  //ri is refractive index of material
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const{
      vec3 outward_normal; //dierection pointing out of the surface
      vec3 reflected = reflect(r_in.direction(),rec.normal); // direction of reflected ray
      float ni_over_nt;
      attenuation = vec3(1.0,1.0,0.0); //dielectric material dont absorb/change the color of the ray
      vec3 refracted; // refracted ray if it exist
      float reflect_prob;
      float cosine;     // cosine of the angel between the ray and surface normal
      if(dot(r_in.direction(),rec.normal) > 0){   // ray is travelling in the general direction as the normal,ray is leaving the material
        outward_normal = -rec.normal;
        ni_over_nt=ref_idx;
        cosine = ref_idx*dot(r_in.direction(),rec.normal)/r_in.direction().length(); // between the ray and the normal, multiplying by ref_idx because ray is going from material to air
      }
      else{
        // if the ray enters the material
        outward_normal = rec.normal;
        ni_over_nt=1.0/ref_idx;
   // Negative sign makes the cosine positive because
    // the incoming ray points toward the surface.
        cosine=-dot(r_in.direction(),rec.normal)/r_in.direction().length();
      }
      if(refract(r_in.direction(),outward_normal,ni_over_nt,refracted)){
          reflect_prob = schlick(cosine,ref_idx);
      }
      else{
        scattered=ray(rec.p,reflected);
        reflect_prob=1;
      }
      if(drand48() < reflect_prob){
        scattered=ray(rec.p,refracted);
      }
      else{
        scattered = ray(rec.p,refracted);
      }
      return true;
    }
    float ref_idx;
    float schlick(float cosine,float ref_idx) const{
      float r0=(1-ref_idx)/(1+ref_idx);
      r0=r0*r0;
      return r0 + (1-r0)*pow((1-cosine),5);
    }
};
};

