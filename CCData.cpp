#include <CCData.h>

CCData::CCData() {
    this->year = 0;
    this->cc = 0; 
}

CCData::CCData(int c, int y) {
    this->year = y;
    this->cc = c;
}