#pragma once

#include <algorithm>

namespace rld {
namespace algos {

/// 2nd recursive quicksort call is crucial to succeed: ensures that pivot
/// is at the final position: at that moment it is guaranteed only
/// that it is someweher after middle1 (inclusive)
template <class ForwardIt> void quicksort(ForwardIt first, ForwardIt last) {
  if (first == last) return;
  auto const pivot = *std::next(first, std::distance(first, last) / 2);
  ForwardIt middle1 = std::partition( // <pivot
      first, last, [pivot](const auto &em) { return em < pivot; });
  ForwardIt middle2 = std::partition( // <= pivot /could use == as well/
      middle1, last, [pivot](const auto &em) { return !(pivot < em); }); // make sure pivot elem is not in recursive ops
      //using basic operations !,< (<= may be not supported)
  quicksort(first, middle1);// el < pivot
  // pivot is already in final position
  quicksort(middle2, last);// el > pivot
}

} // namespace algos
} // namespace rld
