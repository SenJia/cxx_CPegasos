/* 
 * File:   CPegasos.h
 * Author: sj12405
 *
 * Created on 26 August 2015, 15:46
 */

#ifndef CPEGASOS_H
#define	CPEGASOS_H
#include "Sample.h"
#include "Pegasos.h"
using namespace std;

class CPegasos:public Pegasos {
public:
    CPegasos(int,double,string,int,double);
    CPegasos(const CPegasos& orig);
   
    virtual ~CPegasos();
private:
    void update(Sample&,double);
    int start;
    double alpha_mean;
    double alpha_coefficient;
    double C;
};

#endif	/* CPEGASOS_H */

