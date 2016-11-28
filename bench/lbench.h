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


#ifndef _BENCHLIB_H
#define _BENCHLIB_H

#include <functional>

#include <cstdio>
#include <algorithm>
#include <chrono>
#include <vector>
#include <string.h>


namespace bench {

  class console {
  public:
    static constexpr const char* bold   = "\033[1m";
    static constexpr const char* reset  = "\033[0m";

    static constexpr const char* red	  = "\033[0;31m";
    static constexpr const char* green  = "\033[0;32m";
    static constexpr const char* yellow = "\033[0;33m";
    static constexpr const char* blue   = "\033[0;34m";
    static constexpr const char* purple = "\033[0;35m";
    static constexpr const char* cyan	  = "\033[0;36m";
    static constexpr const char* white  = "\033[0;37m";
    static constexpr const char* lred	  = "\033[0;91m";
    static constexpr const char* gray   = "\033[0;97m";

    static void separator(){
      std::cout << "--------------------------------"
                << "--------------------------------"
                << std::endl;
    }
  };



  struct timer {
    /** Configure time metering function */
    using clock    = std::chrono::steady_clock;
    using duration = std::chrono::duration<double, std::micro>;

    clock::time_point start_time;
    timer(): start_time(clock::now()){}

    /** Time since struct creation point */
    double diff() { return duration(clock::now() - start_time) .count() / 1e6; };
  };


  /** Holder for a function with a description */
  template<typename T> struct func_holder{const char *desc; T func; };

  /** Builder for the above */
  template<typename T> static func_holder<typename std::decay<T>::type>
  func(const char *desc, T&& t){ return { desc, std::forward<T>(t) }; }


  /** helpers for working with varargs */
  auto max    = [](auto a, auto b)       { return (a < b) ? b : a ; };
  auto list   = [](auto ...xs)           { return    [=](auto access) { return access(xs...); }; };
  auto sort   = [](auto &cont, auto func){ return std::sort(cont.begin(),cont.end(),func); };
  auto lmap   = [](auto f){ return [f](auto lst) { return lst([f](auto... xs) { return list(f(xs)...); });};};


  /** Execute <f> a number of <times> and return time in seconds. */
  auto timed_exec = [](long times, auto f ) -> double {
    timer start;
    for(auto i = 0; i < times; i++) f();
    return start.diff();
  };


  /** Compare execution time of <nloops> of <functions> and show the rank. */
  auto time_compare = [](long nloops, std::string desc,  auto ...functions) {

    struct time_result{ double time; const char *desc; };

    auto longest_desc = 15u;
    std::vector<time_result> results;
    std::vector<time_result> ret;

    lmap([&](auto elem){
      results.emplace_back(time_result{ timed_exec(nloops, elem.func), elem.desc });
      ret.push_back(results.back());

      longest_desc = max(strlen(elem.desc),longest_desc);
      return elem;
    })(list(functions...));

    sort(results,[](auto x, auto y){ return x.time < y.time; });

    console::separator();

    printf("%s   run time :: %s %-10s %s x%li %s \n%*s\n",
      console::white, console::blue, desc.c_str(),
      console::purple, nloops,
      console::white, longest_desc + 42, "iterations/sec"
    );

    printf( "1.%s %-*s %s  · best ·  %s %6.4fs     %4.2f\n%s",
      console::green, longest_desc, results[0].desc, console::white,
      console::green, results[0].time, double(nloops)/results[0].time,
      console::reset
    );

    for(size_t i = 1; i < results.size(); i++ ){
      auto res = results[i];
      printf( "%s%zu. %-*s %s   x%-6.2f%*s%s%-6.4fs      %4.2f\n",
        console::white, i+1, longest_desc, res.desc,
        console::lred, res.time / results[0].time, (int)(i+1)*2, " ",
        console::reset, res.time, double(nloops)/res.time);
    }
    printf("\n\n");
    return ret;
  };


}

#endif
