#include "position.h"
// overloaded == operator
bool Pos::operator==(const Pos& other) const {
    if (r != other.r) return false;
    if (c != other.c) return false;
    return true;
}
// overloaded < operator
bool Pos::operator<(const Pos& other) const {
    return (r < other.r) || ((r == other.r) && (c < other.c));
}
