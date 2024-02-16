#ifndef __POSITION_H__
#define __POSITION_H__

struct Pos {
  // row
  int r;
  // column
  int c;
  // overloaded == operator
  bool operator==(const Pos& other) const;
  // overloaded < operator
  bool operator<(const Pos& other) const;
};

#endif
