/* 
 * File:   CPegasos.cpp
 * Author: sj12405
 * 
 * Created on 26 August 2015, 15:46
 */

#include "CPegasos.h"
#include "Pegasos.h"
#include <armadillo>
#include "Pegasos.h"

using namespace std;
using namespace arma;

CPegasos::CPegasos(int FEATURELENGTH,double O,string classifierPath,int start,double coefficient):
Pegasos(FEATURELENGTH,O,classifierPath),start(start),alpha_coefficient(coefficient){
    this->weights = vec(FEATURELENGTH).randu();
    string ending = "/";
    if(!equal(ending.rbegin(),ending.rend(),classifierPath.rbegin())){
        this->classifierPath+="/";
    }
 }

void CPegasos::update(Sample &sample,double prediction){
    vec normlised = normalise(sample.getFeature());
    mat inner = normlised.t()*normlised;
    //mat inner = sample.getFeature().t()*sample.getFeature();
    double alpha = O/(inner(0,0)*(1-sample.getLabel()*prediction));
    if(number%start==0){
        C=alpha_mean/number*alpha_coefficient;
    }
    if(alpha>=0){
        alpha_mean+=alpha;
    
    if(number>=start){
      
        if(alpha>C){
            alpha=C;
        }
    }
        
    vec delta = sample.getFeature()*(alpha*sample.getLabel());
    this->weights+=delta;
    }
}

CPegasos::~CPegasos() {
}

