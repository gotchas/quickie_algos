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
  ForwardIt middle1 = std::partition(
      first, last, [pivot](const auto &em) { return em < pivot; });
  ForwardIt middle2 = std::partition(
      middle1, last, [pivot](const auto &em) { return !(pivot < em); });//? using basic operations < and ! (not derived <=)
  quicksort(first, middle1);// el < pivot
  quicksort(middle2, last);// el > pivot
}

} // namespace algos
} // namespace rld
