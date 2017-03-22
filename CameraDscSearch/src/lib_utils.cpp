#include "lib_utils.h"

std::ostream& operator<< (std::ostream& out, const SortedIndex& si) {
    out << si.toString();
    return out;
}
