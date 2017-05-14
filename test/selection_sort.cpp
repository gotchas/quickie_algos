// http://en.cppreference.com/w/cpp/algorithm/iter_swap

#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

#include "lest.hpp"

#include "rld/quickie_algos/selection_sort.h"



namespace rld { namespace algos {

const lest::test specification[] = {

{CASE("proposition: unsorted range of integers") {
   SETUP("context: ") {
      using V = std::vector<int>;
      SECTION("proposition: empty range of integers") {
         V v{};
         selection_sort(v.begin(), v.end());
         EXPECT(v == (V{}));
      }
      SECTION("proposition: singleton range") {
         V v{7};
         selection_sort(v.begin(), v.end());
         EXPECT(v == (V{7}));
      }
      SECTION("proposition: Non empty range positive of integers") {
         V v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1};
         selection_sort(v.begin(), v.end());
         EXPECT(v == (V{ 0, 1, 2, 2, 3, 4, 5, 7, 7, 10, }));
      }
      SECTION("proposition: generate in range with mt19937") {
         //std::random_device rd;
         std::mt19937 gen(785);//std::mt19937 gen(rd());
         std::uniform_int_distribution<> dist(-10, 10);
         V v;
         generate_n(back_inserter(v), 20, bind(dist, gen));
         rld::algos::selection_sort(v.begin(), v.end());
         EXPECT(v == (V{-10, -9, -9, -7, -7, -6, -6, -4, -4, -4, -3, -2, -1, 0, 0, 2, 2, 4, 4, 7,}));
      }
   }
}},
{CASE("proposition: unsorted range of chars - string") {
   SETUP("context: ") {
      using S = std::string;
      SECTION("proposition: empty range of chars") {
         S s{};
         selection_sort(s.begin(), s.end());
         EXPECT(s == (S{}));
      }
      SECTION("proposition: singleton chars") {
         S s{"x"};
         selection_sort(s.begin(), s.end());
         EXPECT(s == (S{"x"}));
      }
      SECTION("proposition: Non empty range of chars") {
         S s{"ala ma asa"};
         selection_sort(s.begin(), s.end());
         EXPECT(s == (S{"  aaaaalms"}));
      }
      SECTION("proposition: Non empty range of chars with codes outside of ASCII range") {
         S s{"ala""\x81"" ma ""\xF1""asa"};
         selection_sort(s.begin(), s.end());
         EXPECT(s == (S{"\x81""\xF1""  aaaaalms"})); // if c>127 conversion is: c - 128
      }
   }
}},
};

}}

int main( int argc, char * argv[] )
{
    return lest::run( rld::algos::specification, argc, argv );
}


