/*  The MIT License (MIT)
\/
/!  Copyright (c) 2016 Konstantin Konyakhin <konstantin.konyakhin@gmail.com>
\/
/\  Permission is hereby granted, free of charge, to any person obtaining a copy
\/  of this software and associated documentation files (the "Software"), to deal
/\  in the Software without restriction, including without limitation the rights
\/  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/\  copies of the Software, and to permit persons to whom the Software is
\/  furnished to do so, subject to the following conditions:
/\
\/  The above copyright notice and this permission notice shall be included in
/\  all copies or substantial portions of the Software.
\/
/\ THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
\/ IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/\ FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
\/  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/\  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
\/  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/\  THE SOFTWARE.
*/

#ifndef _KONVERT_H_
#define _KONVERT_H_

#include <math.h>
#include <inttypes.h>

namespace konvert {

  /** Parse a double from char array. */
  inline double atof(const char *input){
    unsigned char rbuf[4];
    uint32_t *buf_ptr = (uint32_t *)rbuf;

    double frac = 1.0;
    if(*input == '-'){ frac = -1.0; input++; }

    unsigned long int_res = 0;
    unsigned long frac_res = 0;

    double sign = frac;
    uint32_t *input_ptr = (uint32_t *)(input + 1);

    if((int_res = (*input - '0')) <= 9) {
      while(true) {
        *buf_ptr = *input_ptr++ - 0x30303030;

        if( rbuf[0] <= 9 ) int_res = int_res*10 + rbuf[0];
        else if(rbuf[0] == 254) {input = ((char *)input_ptr - 3); break;}
        else return frac * int_res;

        if( rbuf[1] <= 9 ) int_res = int_res*10 + rbuf[1];
        else if(rbuf[1] == 254) {input = ((char *)input_ptr - 2); break;}
        else return frac * int_res;

        if( rbuf[2] <= 9 ) int_res = int_res*10 + rbuf[2];
        else if(rbuf[2] == 254) {input = ((char *)input_ptr - 1); break;}
        else return frac * int_res;

        if( rbuf[3] <= 9 ) int_res = int_res*10 + rbuf[3];
        else if(rbuf[3] == 254) {input = ((char *)input_ptr - 0); break;}
        else return frac * int_res;
      }
    }
    else if(int_res == (unsigned long)-2){ input++; int_res = 0; }
    else return nan("nan");


    input_ptr = (uint32_t *)(input);
    while(true){
      *buf_ptr = *input_ptr++ - 0x30303030;
      if( rbuf[0] <= 9 ) frac_res = frac_res*10 + rbuf[0]; else return (frac     * frac_res + int_res * sign);
      if( rbuf[1] <= 9 ) frac_res = frac_res*10 + rbuf[1]; else return (frac * .1 * frac_res + int_res * sign);
      if( rbuf[2] <= 9 ) frac_res = frac_res*10 + rbuf[2]; else return (frac * .01 * frac_res + int_res * sign);
      if( rbuf[3] <= 9 ) frac_res = frac_res*10 + rbuf[3]; else return (frac * .001 * frac_res + int_res * sign);
      frac *= .0001;
    }
  }

  /** Parse an int from char array. */
  inline int atoi(const char *ch){
    unsigned char cx[4];
    uint32_t *xcx  = (uint32_t *)cx;
    unsigned res;
    int sign = (*ch == '-') ? -1 : 1;
    if(sign<0) ch++;

    if((res = (unsigned)(*ch++ - 0x30)) >= 10) return 0;

    uint32_t *xc = (uint32_t *)ch;

    while(true){
      *xcx = (*xc++) - 0x30303030;
      if( cx[0] <= 9 ) res = res*10 + cx[0]; else return res * sign;
      if( cx[1] <= 9 ) res = res*10 + cx[1]; else return res * sign;
      if( cx[2] <= 9 ) res = res*10 + cx[2]; else return res * sign;
      if( cx[3] <= 9 ) res = res*10 + cx[3]; else return res * sign;
    }
  }
}

#endif