
#include "konvert.h"

#include <iostream>
#include <iomanip>
#include "lbench.h"


using namespace bench;


int main() {

  std::cout << "Hello, World!" << std::endl;

  /**
   * Benchmark int to string conversion
   */

  int ints[] = { 42, -1, 1600066666, -666, 0, -502345535, 26026, 4, 1999999990 };

  const char *hint =
    "you should not see this output because (==43) is never true, "
    "it's just used to avoid compiler optimisation in the benchmark\n";

  char str[16]  = "";
  char cstr[16] = "";

  for(auto const value: ints){

    time_compare(
      1000000u, "int -> string: " +  std::to_string(value),

      func("sprintf",   [&]{ if( sprintf(str, "%d", value) == 43      ) printf("%s\n",hint); }),
      func("to_str",    [&]{ if( *std::to_string(value).c_str() == 43 ) printf("%s\n",hint); }),
      func("konvert",   [&]{ if( konvert::itoa(value, cstr) == 43     ) printf("%s\n",hint); })
    );

    { std::cout << "konvert   : " << konvert::itoa(value, cstr) << " = \"" << cstr << "\"\n"
                << "sprintf   : " << sprintf(str, "%d", value)  << " = \"" << str  << "\"\n"
                << "to_string : \"" << std::to_string(value) << "\"\n"; }
  }


  /**
   * Benchmark konvert::atoi vs system alternatives
   * - atoi
   * - sscanf("%d")
   */

  const char *str_ints =
    "42            -1            666666666666  -666          -23489535     "
    "0             1028455535    -502345535    202345535     1232348935    "
    "450234535     9999999999999 026026        4             502348965     ";

  unsigned long separation = 14;
  auto pos = str_ints;


  for(auto t=0; t<15; t++) {

    time_compare(
      1000000u, "string -> int: " +  std::string(pos,separation),

      func("konvert",   [&]{ if( konvert::atoi(pos) == 43 )       printf("%s\n",hint); }),
      func("atoi",      [&]{ if( atoi(pos) == 43 )                printf("%s\n",hint); }),
      func("strtol",    [&]{ if( strtol(pos, nullptr,10) == 43 )  printf("%s\n",hint); }),
      func("scanf",     [&]{
        int scanfint; sscanf(pos,"%d",&scanfint);
        if( scanfint == 43 ) printf("%s\n",hint); })
    );

    { int scanfres; sscanf(pos, "%d", &scanfres);
      std::cout << "konvert   : " << konvert::atoi(pos)      << std::endl
                << "konvert_l : " << konvert::atol(pos)      << std::endl
                << "atoi      : " << atoi(pos)               << std::endl
                << "strtol    : " << strtol(pos, nullptr,10) << std::endl
                << "sscanf    : " << scanfres                << std::endl; }

    pos += separation;
  }


  /**
   * Benchmark konvert::atof vs system alternatives
   * - atof
   * - sscanf("%lf")
   */

  const char *str_doubles =
    "42.4242       -1.           -66666.666666 42            -2348953.3345 "
    "59489.5535    10.28455535   -5023.45535   20.2345535    12323489.3343 "
    "45023.4535    99.9999999999 026026.000056 40.           50234896.3345 ";

  pos = str_doubles;
  for(auto t=0; t<15; t++){

    time_compare(
      1000000u, "string -> double: " + std::string(pos,separation),

      func("konvert", [&]{ if( konvert::atof(pos) == 43.0 )   printf("%s\n",hint); }),
      func("atof",    [&]{ if( atof(pos) == 43.0 )            printf("%s\n",hint); }),
      func("strtod",  [&]{ if( strtod(pos, nullptr) == 43.0 ) printf("%s\n",hint); }),
      func("scanf",   [&]{
        double scanfd; sscanf(pos,"%lf",&scanfd);
        if( scanfd == 43.0 ) printf("%s\n",hint); })
    );


    { double scanfd; sscanf(pos, "%lf", &scanfd);
      std::cout << std::setprecision(16)
                << "konvert : " << konvert::atof(pos)   << std::endl
                << "atof    : " << atof(pos)            << std::endl
                << "strtod  : " << strtod(pos, nullptr) << std::endl
                << "sscanf  : " << scanfd               << std::endl; }

    pos += separation;
  }
}

