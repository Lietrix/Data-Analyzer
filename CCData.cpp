#include "CCData.h"

CCData::CCData() {
    this->year = 0;
    this->cc = 0; 
}

CCData::CCData(double c, int y) {
    this->year = y;
    this->cc = c;
}

CCData::~CCData() {
    // destructor
}