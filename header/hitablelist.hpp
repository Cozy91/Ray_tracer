#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.hpp"

class hitable_list:public hitable {
  public:
    hitable_list(){}
    // need to make a pointer to a pointer cuz we want a pointer to point to an array of pointers, pointer points to the first pointer in an array of pointers; lol
    hitable_list(hitable **l,int n)
}
