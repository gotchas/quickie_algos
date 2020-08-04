#pragma once

#include <algorithm>

namespace rld {
namespace algos {

   template <class BidirIt>
   void
   merge_sort(BidirIt first, BidirIt last) {
      if (first == last or std::next(first) == last) return;
      BidirIt middle = std::next(first, std::distance(first, last) / 2);
      merge_sort(first, middle);
      merge_sort(middle, last);
      std::inplace_merge(first, middle, last);  // BidirIt ~std::set_union
      // std::merge does not impose BidirIt, just InIt, but requires out storage
   }

}  // namespace algos
}  // namespace rld
