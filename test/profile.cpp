#include <cstring>
#include <stdlib.h>
#include "profile_data.h"
#include "../include/konvert.h"


int main(){

  const char *xn;

  int n =  div((int)strlen(pf::ints),16).quot;
  printf("Ints: %i\n", n);

  for(int j = 0; j<1000; ++j){
    xn = pf::ints;
    for (int i = 0; i<n; i++){
      if(konvert::atoi(xn) == 16) printf(".");
      xn += 16;
    }
  }



  int q =  div((int)strlen(pf::doubles),16).quot;
  printf("Doubles: %i\n", q);

  for(int j = 0; j<1000; ++j){
    xn = pf::doubles;
    for(int i = 0; i<q; i++){
      if(konvert::atof(xn) == 16) printf(".");
      xn += 16;
    }
  }

  printf("Done\n");

  return 0;
}