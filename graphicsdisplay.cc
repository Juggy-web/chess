#include <iostream>
#include <sstream>
#include "graphicsdisplay.h"
#include "window.h"
using namespace std;
// draw white pawn 
void drawWhitePawn(Xwindow& w, int x, int y) {
  w.drawString(x+17,y+16,"  _");
  w.drawString(x+17,y+28," ( )");
  w.drawString(x+25,y+38,"|");
  w.drawString(x+33,y+38,"|");
  w.drawString(x+21,y+48,"/");
  w.drawString(x+37,y+48,"\\");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw black pawn 
void drawBlackPawn(Xwindow& w, int x, int y) {
  w.drawString(x+17,y+16,"  _");
  w.drawString(x+17,y+28," ( )");
  w.drawString(x+26,y+25, "##");
  w.drawString(x+26,y+31, "##");
  w.drawString(x+25,y+38,"|");
  w.drawString(x+33,y+38,"|"); 
  w.drawString(x+29,y+38, "#");
  w.drawString(x+21,y+48,"/");
  w.drawString(x+37,y+48,"\\");
  w.drawString(x+26,y+45, "##");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw white rook
void drawWhiteRook(Xwindow& w, int x, int y) {
  w.drawString(x+18,y+11,"_ _ _");
  w.drawString(x+14,y+20,"|''''|");
  w.drawString(x+18,y+20," - -");
  w.drawString(x+11,y+26," -   -");
  w.drawString(x+20,y+31,"|");
  w.drawString(x+38,y+31,"|");
  w.drawString(x+20,y+38,"|");
  w.drawString(x+38,y+38,"|");
  w.drawString(x+18,y+48,"|");
  w.drawString(x+40,y+48,"|");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw black rook
void drawBlackRook(Xwindow& w, int x, int y) {
  w.drawString(x+18,y+11,"_ _ _");
  w.drawString(x+14,y+20,"|''''|");
  w.drawString(x+17,y+21, "# # #");
  w.drawString(x+18,y+20," - -");
  w.drawString(x+23,y+24, "###");
  w.drawString(x+11,y+26," -   -");
  w.drawString(x+20,y+31,"|");
  w.drawString(x+38,y+31,"|");
  w.drawString(x+23,y+31, "###");
  w.drawString(x+20,y+38,"|");
  w.drawString(x+38,y+38,"|");
  w.drawString(x+23,y+38, "###");
  w.drawString(x+18,y+48,"|");
  w.drawString(x+40,y+48,"|");
  w.drawString(x+23,y+45, "###");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw white knight
void drawWhiteKnight(Xwindow& w, int x, int y) {
  w.drawString(x+14,y+11,"  __");
  w.drawString(x+20,y+20,"/  \\");
  w.drawString(x+17,y+30,"(");
  w.drawString(x+20,y+31,"_");
  w.drawString(x+20,y+32," /");
  w.drawString(x+40,y+30,"|");
  w.drawString(x+26,y+38,"/");
  w.drawString(x+40,y+38,"|");
  w.drawString(x+21,y+48,"/");
  w.drawString(x+40,y+48,"|");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw black knight
void drawBlackKnight(Xwindow& w, int x, int y) {
  w.drawString(x+14,y+11,"  __");
  w.drawString(x+20,y+20,"/  \\");
  w.drawString(x+23,y+22, "###");
  w.drawString(x+17,y+30,"(");
  w.drawString(x+21,y+29, "#");
  w.drawString(x+20,y+31,"_");
  w.drawString(x+20,y+32," /");
  w.drawString(x+40,y+30,"|");
  w.drawString(x+25,y+29, " ##");
  w.drawString(x+26,y+38,"/");
  w.drawString(x+40,y+38,"|");
  w.drawString(x+25,y+37, " ##");
  w.drawString(x+21,y+48,"/");
  w.drawString(x+40,y+48,"|");
  w.drawString(x+25,y+45, "###");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw white bishop
void drawWhiteBishop(Xwindow& w, int x, int y) {
  w.drawString(x+17,y+16,"  o");
  w.drawString(x+17,y+24," / \\ ");
  w.drawString(x+17,y+28," (+)");
  w.drawString(x+25,y+38,"|");
  w.drawString(x+33,y+38,"|");
  w.drawString(x+21,y+48,"/");
  w.drawString(x+37,y+48,"\\");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw black bishop
void drawBlackBishop(Xwindow& w, int x, int y) {
  w.drawString(x+17,y+16,"  o");
  w.drawString(x+17,y+24," / \\ ");
  w.drawString(x+17,y+28," (+)");
  w.drawString(x+26,y+25, "##");
  w.drawString(x+26,y+31, "##");
  w.drawString(x+25,y+38,"|");
  w.drawString(x+33,y+38,"|");
  w.drawString(x+29,y+38, "#");
  w.drawString(x+21,y+48,"/");
  w.drawString(x+37,y+48,"\\");
  w.drawString(x+26,y+45, "##");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw white queen
void drawWhiteQueen(Xwindow& w, int x, int y) {
  w.drawString(x+5,y+16,"  o o o");
  w.drawString(x+8,y+18,"o      o");
  w.drawString(x+8,y+28,"\\\\\\||///");
  w.drawString(x+14,y+38,"\\");
  w.drawString(x+44,y+38,"/");
  w.drawString(x+18,y+48,"|");
  w.drawString(x+40,y+48,"|");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw black queen
void drawBlackQueen(Xwindow& w, int x, int y) {
  w.drawString(x+5,y+16,"  o o o");
  w.drawString(x+8,y+18,"o      o");
  w.drawString(x+8,y+28,"\\\\\\||///");
  w.drawString(x+17,y+29, "# # #");
  w.drawString(x+14,y+38,"\\");
  w.drawString(x+44,y+38,"/");
  w.drawString(x+17,y+37, "#####");
  w.drawString(x+18,y+48,"|");
  w.drawString(x+40,y+48,"|");
  w.drawString(x+23,y+45, "###");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw white king
void drawWhiteKing(Xwindow& w, int x, int y) {
  w.drawString(x+5,y+16," __ + __");
  w.drawString(x+8,y+28,"(__\\/__)");
  w.drawString(x+14,y+38,"\\");
  w.drawString(x+44,y+38,"/");
  w.drawString(x+18,y+48,")");
  w.drawString(x+40,y+48,"(");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// draw black king
void drawBlackKing(Xwindow& w, int x, int y) {
  w.drawString(x+5,y+16," __ + __");
  w.drawString(x+8,y+28,"(__\\/__)");
  w.drawString(x+11,y+27, "### ###");
  w.drawString(x+14,y+38,"\\");
  w.drawString(x+44,y+38,"/");
  w.drawString(x+17,y+36, "#####");
  w.drawString(x+18,y+48,")");
  w.drawString(x+40,y+48,"(");
  w.drawString(x+23,y+45, "###");
  w.drawString(x+23,y+45,"___");
  w.drawString(x+23,y+48, "___");
}
// ctor
GraphicsDisplay::GraphicsDisplay(Xwindow& w, bool pieces):size{62.5}, window{w} {
  for (float i = 0; i < 500; i += size) {
    for (float j = 0; j < 500; j += size) {
        if (static_cast<int>(i + j) % 125 == 0) {
            window.fillRectangle(i, j, size, size, 3);
        } else {
            window.fillRectangle(i, j, size, size, 4);
        }
    }
  }
  window.drawString(5,12,"8");
  window.drawString(5,74.5,"7");
  window.drawString(5,137,"6");
  window.drawString(5,199.5,"5");
  window.drawString(5,262,"4");
  window.drawString(5,324.5,"3");
  window.drawString(5,387,"2");
  window.drawString(5,449.5,"1");

  window.drawString(51,492,"a");
  window.drawString(113.5,492,"b");
  window.drawString(176,492,"c");
  window.drawString(238.5,492,"d");
  window.drawString(301,492,"e");
  window.drawString(363.5,492,"f");
  window.drawString(426,492,"g");
  window.drawString(488.5,492,"h");

  if (pieces) {
    for (float i = 0; i < 500; i += size) {
      drawWhitePawn(window,i,375);
    }
    drawWhiteRook(window,0,437.5);
    drawWhiteKnight(window,62.5,437.5);
    drawWhiteBishop(window,125,437.5);
    drawWhiteQueen(window,187.5,437.5);
    drawWhiteKing(window,250,437.5);
    drawWhiteBishop(window,312.5,437.5);
    drawWhiteKnight(window,375,437.5);
    drawWhiteRook(window,437.5,437.5);

    for (float i = 0; i < 500; i += size) {
      drawBlackPawn(window,i,62.5);
    }
    drawBlackRook(window,0,0);
    drawBlackKnight(window,62.5,0);
    drawBlackBishop(window,125,0);
    drawBlackQueen(window,187.5,0);
    drawBlackKing(window,250,0);
    drawBlackBishop(window,312.5,0);
    drawBlackKnight(window,375,0);
    drawBlackRook(window,437.5,0);
    }
}

// update display
void GraphicsDisplay::notify(const Pos& start, const Pos& end, char symbol) {
  if (static_cast<int>(start.r*size + start.c*size) % 125 == 0) {
    window.fillRectangle(start.c*size, start.r*size, size, size, 3);
    if (start.c == 0) {
      if (start.r == 0) {window.drawString(5,12,"8");}
      if (start.r == 1) {window.drawString(5,74.5,"7");}
      if (start.r == 2) {window.drawString(5,137,"6");}
      if (start.r == 3) {window.drawString(5,199.5,"5");}
      if (start.r == 4) {window.drawString(5,262,"4");}
      if (start.r == 5) {window.drawString(5,324.5,"3");}
      if (start.r == 6) {window.drawString(5,387,"2");}
      if (start.r == 7) { window.drawString(5,449.5,"1");}
    }

    if (start.r == 7) {
      if (start.c == 0) {window.drawString(51,492,"a");}
      if (start.c == 1) {window.drawString(113.5,492,"b");}
      if (start.c == 2) {window.drawString(176,492,"c");}
      if (start.c == 3) {window.drawString(238.5,492,"d");}
      if (start.c == 4) {window.drawString(301,492,"e");}
      if (start.c == 5) {window.drawString(363.5,492,"f");}
      if (start.c == 6) {window.drawString(426,492,"g");}
      if (start.c == 7) {window.drawString(488.5,492,"h");}
    }
  } else {
    window.fillRectangle(start.c*size, start.r*size, size, size, 4);
    if (start.c == 0) {
      if (start.r == 0) {window.drawString(5,12,"8");}
      if (start.r == 1) {window.drawString(5,74.5,"7");}
      if (start.r == 2) {window.drawString(5,137,"6");}
      if (start.r == 3) {window.drawString(5,199.5,"5");}
      if (start.r == 4) {window.drawString(5,262,"4");}
      if (start.r == 5) {window.drawString(5,324.5,"3");}
      if (start.r == 6) {window.drawString(5,387,"2");}
      if (start.r == 7) { window.drawString(5,449.5,"1");}
    }

    if (start.r == 7) {
      if (start.c == 0) {window.drawString(51,492,"a");}
      if (start.c == 1) {window.drawString(113.5,492,"b");}
      if (start.c == 2) {window.drawString(176,492,"c");}
      if (start.c == 3) {window.drawString(238.5,492,"d");}
      if (start.c == 4) {window.drawString(301,492,"e");}
      if (start.c == 5) {window.drawString(363.5,492,"f");}
      if (start.c == 6) {window.drawString(426,492,"g");}
      if (start.c == 7) {window.drawString(488.5,492,"h");}
    }
  }
  if (static_cast<int>(end.r*size + end.c*size) % 125 == 0) {
    window.fillRectangle(end.c*size, end.r*size, size, size, 3);
    if (end.c == 0) {
      if (end.r == 0) {window.drawString(5,12,"8");}
      if (end.r == 1) {window.drawString(5,74.5,"7");}
      if (end.r == 2) {window.drawString(5,137,"6");}
      if (end.r == 3) {window.drawString(5,199.5,"5");}
      if (end.r == 4) {window.drawString(5,262,"4");}
      if (end.r == 5) {window.drawString(5,324.5,"3");}
      if (end.r == 6) {window.drawString(5,387,"2");}
      if (end.r == 7) { window.drawString(5,449.5,"1");}
    }

    if (end.r == 7) {
      if (end.c == 0) {window.drawString(51,492,"a");}
      if (end.c == 1) {window.drawString(113.5,492,"b");}
      if (end.c == 2) {window.drawString(176,492,"c");}
      if (end.c == 3) {window.drawString(238.5,492,"d");}
      if (end.c == 4) {window.drawString(301,492,"e");}
      if (end.c == 5) {window.drawString(363.5,492,"f");}
      if (end.c == 6) {window.drawString(426,492,"g");}
      if (end.c == 7) {window.drawString(488.5,492,"h");}
    }
  } else {
    window.fillRectangle(end.c*size, end.r*size, size, size, 4);
    if (end.c == 0) {
      if (end.r == 0) {window.drawString(5,12,"8");}
      if (end.r == 1) {window.drawString(5,74.5,"7");}
      if (end.r == 2) {window.drawString(5,137,"6");}
      if (end.r == 3) {window.drawString(5,199.5,"5");}
      if (end.r == 4) {window.drawString(5,262,"4");}
      if (end.r == 5) {window.drawString(5,324.5,"3");}
      if (end.r == 6) {window.drawString(5,387,"2");}
      if (end.r == 7) { window.drawString(5,449.5,"1");}
    }

    if (end.r == 7) {
      if (end.c == 0) {window.drawString(51,492,"a");}
      if (end.c == 1) {window.drawString(113.5,492,"b");}
      if (end.c == 2) {window.drawString(176,492,"c");}
      if (end.c == 3) {window.drawString(238.5,492,"d");}
      if (end.c == 4) {window.drawString(301,492,"e");}
      if (end.c == 5) {window.drawString(363.5,492,"f");}
      if (end.c == 6) {window.drawString(426,492,"g");}
      if (end.c == 7) {window.drawString(488.5,492,"h");}
    }
  }
  
  if (symbol == 'R') {drawWhiteRook(window,end.c*size,end.r*size);}
  if (symbol == 'N') {drawWhiteKnight(window,end.c*size,end.r*size);}
  if (symbol == 'B') {drawWhiteBishop(window,end.c*size,end.r*size);}
  if (symbol == 'Q') {drawWhiteQueen(window,end.c*size,end.r*size);}
  if (symbol == 'K') {drawWhiteKing(window,end.c*size,end.r*size);}
  if (symbol == 'P') {drawWhitePawn(window,end.c*size,end.r*size);}
  if (symbol == 'r') {drawBlackRook(window,end.c*size,end.r*size);}
  if (symbol == 'n') {drawBlackKnight(window,end.c*size,end.r*size);}
  if (symbol == 'b') {drawBlackBishop(window,end.c*size,end.r*size);}
  if (symbol == 'q') {drawBlackQueen(window,end.c*size,end.r*size);}
  if (symbol == 'k') {drawBlackKing(window,end.c*size,end.r*size);}
  if (symbol == 'p') {drawBlackPawn(window,end.c*size,end.r*size);}
}

// dtor
GraphicsDisplay::~GraphicsDisplay() {}
