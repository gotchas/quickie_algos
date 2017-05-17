// http://stackoverflow.com/questions/29145520/how-is-nth-element-implemented

#include <vector>
#include <algorithm>
#include <vector>

#include "rld/qalgos/insertion_sort.h"

template <class Iter, class T>
void
nth_element(Iter first, Iter nth, Iter last) {
   while (last - first > 3) {
      Iter cut =
          // unguarded_partition(first, last,
          std::partition(first, last, T(median(*first, *(first + (last - first) / 2), *(last - 1))));
      if (cut <= nth)
         first = cut;
      else
         last = cut;
   }
   // last - first <= 3
   insertion_sort(first, last);
}


int
main() {
   std::vector<int> v{
       1, 3, 5, 77, 91, 22, 92, 22, 92,
   };
   nth_element(v.begin(), v.begin() + 4, v.end());
   return 0;
}
