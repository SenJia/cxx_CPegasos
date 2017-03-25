/* 
 * File:   Pegasos.h
 * Author: sj12405
 *
 * Created on 25 August 2015, 10:05
 */

#ifndef PEGASOS_H
#define	PEGASOS_H

#include <armadillo>
#include "Sample.h"

using namespace arma;
using namespace std;

class Pegasos {
public:
    Pegasos(int,double,string);
    
    vec getWeights();
    void reset();
    double getPosAccuracy();
    double getNegAccuracy();
    double getAccuracy();
    double predict(Sample&);
    void train(vector<Sample>&);
    void validate(vector<Sample>&);
    double test(vector<Sample>&);
    void save();
    void load(string);
    virtual ~Pegasos();
protected:
    virtual void update(Sample&,double);
    vec weights;
    int number;
    double O;
    double FP;
    double FN;
    double TP;
    double TN;
    int FEATURELENGTH;
    string classifierPath;
    double bestAcc[2];
};

#endif	/* PEGASOS_H */

