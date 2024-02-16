#ifndef __CONVERTOR_H__
#define __CONVERTOR_H__
#include "position.h"
#include <string>
#include <stdexcept>

class Convertor final {

    public:
    // takes in string and returns corresponding Position struct 
    Pos stringToPos(const std::string& location) const;
    // takes in Position struct and returns corresponding string
    std::string posToString(const Pos& location) const;

};

#endif
