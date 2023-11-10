#ifndef CCDATA_H
#define CCDATA_H

class CCData {
 public:
    //constructors
    CCData(double cc, int year);
    CCData();

    //destructor
    ~CCData();

    int year;
    double cc;
 
 private:

};

#endif