#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
class Xwindow;

class GraphicsDisplay: public Observer {
  Xwindow& window;
  const float size;
 public:
  // constructor
  GraphicsDisplay(Xwindow& w, bool pieces); 

  // changes the char in theDisplay corresponding to c
  void notify(const Pos& start, const Pos& end, char symbol) override;

  // destructor
  ~GraphicsDisplay();

};

#endif
