#include "position.h"
#include "convertor.h"
#include <string>
#include <iostream>
#include <sstream>

// takes in string and returns corresponding Position struct 
Pos Convertor::stringToPos(const std::string& location) const {

    Pos newPos; 

    char l = location[0];
    // check that column is valid
    if ((l >= 'a' && l <= 'h') || (l >= 'A' && l <= 'H')) {
        if (l >= 'a' && l <= 'h') {
            newPos.c = l - 97; 
        } else {
            newPos.c = l - 65; 
        }
    } else { // throw otherwise 
        while (std::cin.get() != '\n') {
            continue;
        }
        throw std::logic_error{"Please enter a valid board location"}; 
    }
    // check that row is valid 
    if (location[1] >= '1' && location[1] <= '8') {
        if(location[1] == '1') {
            newPos.r = 7;
        } else if (location[1] == '2') {
            newPos.r = 6;
        } else if (location[1] == '3') {
            newPos.r = 5;
        } else if (location[1] == '4') {
            newPos.r = 4;
        } else if (location[1] == '5') {
            newPos.r = 3;
        } else if (location[1] == '6') {
            newPos.r = 2;
        } else if (location[1] == '7') {
            newPos.r = 1;
        } else if (location[1] == '8') {
            newPos.r = 0;
        }
    } else { // throw otherwise
        throw std::logic_error{"Please enter a valid board location"}; 
    }
    // return struct
    return newPos; 
}

// takes in Position struct and returns corresponding string
std::string Convertor::posToString(const Pos& location) const {
    // convert pos struct column to string 
    std::ostringstream oss; 
    char colChar = static_cast<char>(location.c + 97);
    oss << colChar; 
    // add position row to oss
    if(location.r == 7) {
        oss << '1';
    } else if (location.r == 6) {
        oss << '2';
    } else if (location.r == 5) {
        oss << '3';
    } else if (location.r == 4) {
        oss << '4';
    } else if (location.r == 3) {
        oss << '5';
    } else if (location.r == 2) {
        oss << '6';
    } else if (location.r == 1) {
        oss << '7';
    } else if (location.r == 0) {
        oss << '8';
    }
    // return string
    return oss.str();

}
