#include "displayMoves.h"

using namespace std;

void DisplayMoves::print(const map<Pos,vector<Pos>> & moves) {
        for (const auto & i:moves) {
            if(!i.second.empty()) {
                cout << c.posToString(i.first) << ":"; 
                for(const auto & j:i.second) {
                    cout << " " << c.posToString(j); 
                }
                cout << endl;
            }
        }
}
