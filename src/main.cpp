#include<iostream>
#include "../header/vec3.hpp"

int main(){
  int nx =200; //length of the screen
  int ny=100; // breadth of the screen
  std::cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
  for(int j=ny-1;j>=0;j--){ //loop through rows
   for(int i-0;i<nx;i++){ //loop through columns in each row
     vec3 col(float(i)/float(nx),float(j)/float(ny),0.2); //red,green and blue(always 0.2)
     int ir = int(255.99*col[0]);
     int ig = int(255.99*col[1]);
     int ib = int(255.99*col[2]);
     std::cout<<ir<<" "<<ig<<" "<<ib<<"\n";
   }
  }
}


