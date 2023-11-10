#ifndef CCDATA_H
#define CCDATA_H

class CCData {
 public:
    //constructors
    CCData(double cc, double year);
    CCData();

    //destructor
    ~CCData();

    double year;
    double cc;

 private:

};

#endif