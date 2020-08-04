// http://en.cppreference.com/w/cpp/algorithm/iter_swap

#include "rld/algos/insertion_sort.h"
#include "rld/algos/merge_sort.h"
#include "rld/algos/quicksort.h"
#include "rld/algos/selection_sort.h"

#include "lest.hpp"

#include <forward_list>
#include <list>
#include <vector>

#include <algorithm>

#include <functional>
#include <iterator>

#include <random>

// TODO
#define XALGOS_SECTIONS()                   \
   SECTION("selection sort") {              \
      selection_sort(fl.begin(), fl.end()); \
      EXPECT(fl == expected);               \
   }                                        \
   SECTION("insertion sort") {              \
      insertion_sort(fl.begin(), fl.end()); \
      EXPECT(fl == expected);               \
   }

#define ALGOS_SECTIONS() XALGOS_SECTIONS()

namespace rld {
namespace algos {
   // clang-format off
const lest::test specification[] = {
///////////////FORWARD IT ENABLED ALGOS ////////////////////////////////
{CASE("proposition: proper sorting of ForwardIter range of integers") {
   using FL = std::forward_list<int>;//TODO rename - use eclipse
   SETUP("context: empty range") {
      FL fl{};
      FL expected{};
      SECTION("selection sort") {
         selection_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("quicksort") {
         quicksort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
   SETUP("context: singleton range") {
      FL fl{7};
      selection_sort(fl.begin(), fl.end());
      FL expected{ 7, };
      SECTION("selection sort") {
         selection_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("quicksort") {
         quicksort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
   SETUP("context: Non empty range positive of integers") {
      FL fl{2, 4, 2, 0, 5, 10, 7, 3, 7, 1};
      FL expected{ 0, 1, 2, 2, 3, 4, 5, 7, 7, 10, };
      SECTION("selection sort") {
         selection_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("quicksort") {
         quicksort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
   SETUP("context: generate in range with mt19937") {
      //std::random_device rd;
      std::mt19937 gen(785);//std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(-10, 10);
      FL fl;
      generate_n(front_inserter(fl), 20, bind(dist, gen));
      FL expected{-10, -9, -9, -7, -7, -6, -6, -4, -4, -4, -3, -2, -1, 0, 0, 2, 2, 4, 4, 7,};
      SECTION("selection sort") {
         selection_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
      SECTION("quicksort") {
         quicksort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
}},
///////////////BIDIR IT ENABLED ALGOS //////////////////////////////////
{CASE("proposition: proper sorting of ForwardIter range of integers") {
   using FL = std::list<int>;//TODO rename - use eclipse
   SETUP("context: empty range") {
      FL fl{};
      FL expected{};
      SECTION("merge sort") {
         merge_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
   SETUP("context: singleton range") {
      FL fl{7};
      selection_sort(fl.begin(), fl.end());
      FL expected{ 7, };
      SECTION("merge sort") {
         merge_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
   SETUP("context: Non empty range positive of integers") {
      FL fl{2, 4, 2, 0, 5, 10, 7, 3, 7, 1};
      FL expected{ 0, 1, 2, 2, 3, 4, 5, 7, 7, 10, };
      SECTION("merge sort") {
         merge_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
   SETUP("context: generate in range with mt19937") {
      //std::random_device rd;
      std::mt19937 gen(785);//std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(-10, 10);
      FL fl;
      generate_n(front_inserter(fl), 20, bind(dist, gen));
      FL expected{-10, -9, -9, -7, -7, -6, -6, -4, -4, -4, -3, -2, -1, 0, 0, 2, 2, 4, 4, 7,};
      SECTION("merge sort") {
         merge_sort(fl.begin(), fl.end());
         EXPECT(fl == expected);
      }
   }
}},
////////////////TESTS WITH RANDOM IN: not necessarily require RandIT ///
{CASE("proposition: proper sorting of RandomIt range of chars/strings") {
   using S = std::string;
   SETUP("context: empty string") {
      S s{};
      S expected{};
      SECTION("selection sort") {
         selection_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("quicksort") {
         quicksort(s.begin(), s.end());
         EXPECT(s == expected);
      }
   }
   SETUP("context: singleton char") {
      S s{"x"};
      S expected{"x"};
      SECTION("selection sort") {
         selection_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("quicksort") {
         quicksort(s.begin(), s.end());
         EXPECT(s == expected);
      }
   }
   SETUP("context: Non empty range of chars") {
      S s{"ala ma asa"};
      S expected{"  aaaaalms"};
      SECTION("selection sort") {
         selection_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("quicksort") {
         quicksort(s.begin(), s.end());
         EXPECT(s == expected);
      }
   }
   SETUP("context: Non empty range of chars with codes outside of ASCII range") {
      S s{"ala""\x81"" ma ""\xF1""asa"};
      S expected {"\x81""\xF1""  aaaaalms"};// if code(c)>127 conversion to int is: => code(c) - 128
      SECTION("selection sort") {
         selection_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("insertion sort") {
         insertion_sort(s.begin(), s.end());
         EXPECT(s == expected);
      }
      SECTION("quicksort") {
         quicksort(s.begin(), s.end());
         EXPECT(s == expected);
      }
   }
}},
};
// clang-format on
}
}

auto
fibonaci_generator() {
   return [ i = 0LL, j = 1LL ]() mutable { return std::exchange(j, i + j); };
}

int
main(int argc, char* argv[]) {
   return fibonaci_generator()(), lest::run(rld::algos::specification, argc, argv);
}
