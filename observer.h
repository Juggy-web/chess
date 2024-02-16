#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "position.h"
// abstract class observer
class Observer {
 public:
  // figure out start and end, instead of notify all, pass in the struct there
  virtual void notify(const Pos& start, const Pos& end, char symbol) = 0;  
  // dtor
  virtual ~Observer() = default;
};

#endif
