class material{
  public:
    virtual bool scatter(const ray& r_in,const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

};         // attenuation writes the color after hit, scattered creates a new bounded ray after the incident one

class lambertian: public material{ // for diffuse surfaces,diffuse surface that reflects the light a which is called albedo of the materil
        public:
          lambertian(const vec3& a):albedo(a);{}
          virtual bool scatter(const ray& r_in, const hit_record& rec,vec3& attenuation,ray& scattered) const {
            vec3 target=rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p,target-rec.p);
            attenuation = albedo; // albedo is like what kinda color the material will reflect
           return true;
          }

};

class metal:public material{
  public:
    metal(const vec3& a): albedo(a){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation, ray& scattered) const {
      vec3 reflected = reflect(unit_vector(r_in.direction())rec.normal); // PERFECT reflection calculating, dot product ans shit, defined in vec3.hpp
      scattered = ray(rec.p,reflected);
      attenuation=albedo;
      return(dot(scattered.direction(),rec.normal())>0); // error handling for rays going into  the surface
    }
    vec3 albedo;
};
