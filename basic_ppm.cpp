#include<iostream>

int main(){
  int nx=200;
  int ny=100; // image size 100*200 
  std::cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
  for(int j=ny-1;j>=0;j--){  //loops for visiting every pixel
    for(int i=0;i<nx;i++){
      float r=float(i)/float(nx); //moving right, red increases
      float g=float(j)/float(ny); //moving up,green increases 
      float b=0.2;
      int ir=int(255.99*r);
      int ig=int(255.99*g);
      int ib=int(255.99*b);
      std::cout<<ir<<" "<<ig<<" "<<ib<<"\n";
    }
  }
}
