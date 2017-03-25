/* 
 * File:   Sample.h
 * Author: sj12405
 *
 * Created on 25 August 2015, 10:41
 */

#ifndef SAMPLE_H
#define	SAMPLE_H
#include<armadillo>

using namespace arma;
using namespace std;

class Sample {
public:
    Sample(vec&,int);
    vec& getFeature();
    int getLabel();
    void setFeature(vec&);
    void setLabel(int);
    virtual ~Sample();
private:
    int label;
    vec feat;
};

#endif	/* SAMPLE_H */

