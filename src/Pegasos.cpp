/* 
 * File:   Pegasos.cpp
 * Author: sj12405
 * 
 * Created on 25 August 2015, 10:05
 */

#include "Pegasos.h"
#include "Sample.h"
#include <armadillo>

using namespace std;
using namespace arma;

Pegasos::Pegasos(int FEATURELENGTH,double O,string classifierPath):
FEATURELENGTH(FEATURELENGTH),O(O),classifierPath(classifierPath),
        FP(0),FN(0),TN(0),TP(0),number(0),bestAcc({0,0}){
    this->weights = vec(FEATURELENGTH).randu();
    string ending = "/";
    if(!equal(ending.rbegin(),ending.rend(),classifierPath.rbegin())){
        this->classifierPath+="/";
    }
 }

vec Pegasos::getWeights(){
    return this->weights;
}

void Pegasos::reset(){
    this->FN=0;
    this->FP=0;
    this->TN=0;
    this->TP=0;
}

double Pegasos::getAccuracy(){
    return (this->TP+this->TN+this->FP+this->FN == 0)?0:(this->TN+this->TP)/(this->TP+this->TN+this->FP+this->FN);
}
	
double Pegasos::getPosAccuracy(){
    return (this->TP+this->FN ==0)?0:this->TP/(this->TP+this->FN);
}
	
double Pegasos::getNegAccuracy(){
    return (this->TN+this->FP==0)?0:this->TN/(this->TN+this->FP);
}

double Pegasos::predict(Sample &input){
    mat ans = this->weights.t()*input.getFeature();
    return ans(0,0);
}

void Pegasos::train(vector<Sample> &trainingSet){
    for(vector<Sample>::iterator it=trainingSet.begin();it!=trainingSet.end();++it){
        double prediction = predict(*it);
        update(*it,prediction);
        this->number++;
    }
}

void Pegasos::update(Sample &sample,double prediction){
    vec normlised = normalise(sample.getFeature());
    mat inner = normlised.t()*normlised;
    //mat inner = sample.getFeature().t()*sample.getFeature();
    double alpha = O/(inner(0,0)*(1-sample.getLabel()*prediction));
    if(alpha>0){
        vec delta = sample.getFeature()*(alpha*sample.getLabel());
        this->weights+=delta;
    }
}

void Pegasos::validate(vector<Sample> &validationSet){
    double acc = test(validationSet);
    if(acc>=bestAcc[0]){
        bestAcc[0]=acc;
        bestAcc[1]=number;
    }
    cout<<number<<" samples, best acc on validation:"<<bestAcc[0]<<", the best snapshot is "<<bestAcc[1]<<endl;
}

double Pegasos::test(vector<Sample> &testSet){
    reset();
    for(vector<Sample>::iterator it=testSet.begin();it!=testSet.end();++it){
        double prediction = predict(*it);
        if(prediction* (*it).getLabel() > 0){
            if((*it).getLabel()>0)
                this->TP++;
            else
                this->TN++;
        }else{
            if((*it).getLabel()>0)
                this->FN++;
            else
                this->FP++;
        }
    }
    //save();
    return getAccuracy();
}

void Pegasos::save(){
    this->weights.save(this->classifierPath+to_string(this->number)+".model");
}

void Pegasos::load(string path){
    this->weights.load(path);
}


Pegasos::~Pegasos() {
}

