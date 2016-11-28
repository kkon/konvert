
#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/konvert.h"


bool compare_doubles(double a, double b){
  if(std::isnan(a) && std::isnan(b))
    return true;

  double precision = 1e10;
  long long int aval = (long long int)(a*precision), bval = (long long int)(b*precision);
  return aval == bval;
}


int main(){

  std::cout << "string to int test\n\n\n";

  auto tested = 0;
  const char *int_numbers[] = {
    "42", "1", "0", "-1", "-1987",
    "1917", "8", "666hello", "42.0002",
    "NAN", "1234567891111", "", "0x92929",
    "00000000"
  };

  for(auto const &number: int_numbers){
    std::cout << atoi(number) << " == " << konvert::atoi(number);

    if(konvert::atoi(number) != atoi(number)){
      std::cout << "..  KO" << std::endl;
      std::cerr << "Number " << number << " is not converted correctly: " << std::endl;
      std::cerr << "konvert result: " << konvert::atoi(number) << std::endl;
      std::cerr << "atoi    result: " << atoi(number) << std::endl;
      std::cout << "test failed\n";
      return 1;
    } else {
      std::cout << "..  OK" << std::endl;
      tested++;
    }
  }


  std::cout << "\n\n\nSUCCESS\n" << "Tested " << tested << " integers\n\n";



  std::cout << "string to double test\n\n\n";

  tested = 0;
  const char *double_numbers[] = {
    "42.424242", "1.", ".1", "0", "-1", "-1987",
    "1917", "8", "666hello", "42.0002",
    "NANval", "12345678911.11", "0.92929",
    "0000.0000", "0000.00009895959",
    "999999999999999999.9999999999999999999999999"
  };


  for(auto const &number: double_numbers){
    auto kf = konvert::atof(number);
    auto af = atof(number);

    std::cout << std::setprecision(16) << af << " == " << kf;

    if( !compare_doubles(kf,af)) {
      std::cout << "..  KO" << std::endl;
      std::cerr << "Number " << number << " is not converted correctly: " << std::endl;
      std::cerr << "konvert result: " << kf << std::endl;
      std::cerr << "atof    result: " << af << std::endl;
      std::cout << "test failed\n";
      return 1;
    } else {
      std::cout << "..  OK" << std::endl;
      tested++;
    }
  }

  std::cout << "\n\n\nSUCCESS\n" << "Tested " << tested << " doubles\n\n";

  std::cout << "test passed\n";
  return 0;
}