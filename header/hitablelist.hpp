#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.hpp"

class hitable_list:public hitable {
  public:
    hitable_list(){}
    // need to make a pointer to a pointer cuz we want a pointer to point to an array of pointers, pointer points to the first pointer in an array of pointers; lol
  hitable_list(hitable **l, int n)
        : list(l), list_size(n)
    {
    }
 
    virtual bool hit(
        const ray& r,
        float tmin,
        float tmax,
        hit_record& rec
    ) const
    {
    hit_record temp_rec;
        bool hit_anything = false;
        float closest_so_far = tmax;

        for (int i = 0; i < list_size; i++) {
            if (list[i]->hit(r, tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
    hitable** list;
    int list_size;
};
#endif
