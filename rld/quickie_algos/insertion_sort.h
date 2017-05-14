#pragma once

#include <algorithm>

template <class It>
void
insertion_sort(It f, It e) {
    auto const s = f;
    for (; f != e; ++f) {
        std::rotate(std::upper_bound(s, f, *f), f, f+1);
    }
    // element wich is going to be inserted is at the past the end position
    // upper_bound returns destination for this element
    // insertion is done by rotate left
}

