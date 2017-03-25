/* 
 * File:   Sample.cpp
 * Author: sj12405
 * 
 * Created on 25 August 2015, 10:41
 */

#include "Sample.h"

Sample::Sample(vec &feat,int label):feat(feat),label(label) {
}

void Sample::setFeature(vec &feat){
    this->feat=feat;
}

void Sample::setLabel(int label){
    this->label=label;
}

vec& Sample::getFeature(){
   return this->feat; 
}

int Sample::getLabel(){
    return this->label;
}

Sample::~Sample() {
}

