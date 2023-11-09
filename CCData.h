#ifndef CCDATA_H
#define CCDATA_H

class CCData {
 public:
    //constructors
    CCData(int cc, int year);
    CCData();

    //destructor
    ~CCData();

    int year;
    int cc;
 
 private:

};

#endif