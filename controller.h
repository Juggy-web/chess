#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Controller {
    float blackWins = 0;
    float whiteWins = 0;
    bool enhanceOn;
    public:
    float getBlackWins() const;
    float getWhiteWins() const;
    void setEnhancements(bool state);
    void gameFlow(); 

};

#endif
