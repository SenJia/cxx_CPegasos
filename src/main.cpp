/* 
 * File:   main.cpp
 * Author: sj12405
 *
 * Created on 25 August 2015, 09:56
 */

#include <cstdlib>
#include "mongo/client/dbclient.h"
#include <iostream>
#include <armadillo>
#include "Sample.h"
#include "Pegasos.h"
#include <algorithm>
#include "CPegasos.h"

using namespace std;
using namespace mongo;
using namespace arma;

const string TrainingDB = "LFW.Training";
const string TestDB = "LFW.Test";

vector<Sample> getDataSet(auto_ptr<DBClientCursor> &cursor){
    vector<Sample> dataSet;
    while(cursor->more()){
    BSONObj o = cursor->next();
    vector<int> tg;
    o.getObjectField("Tg").Vals(tg);
   
    int label;
    if(std::find(tg.begin(), tg.end(), 1) != tg.end())
        label=-1;
    else
        label=1;
    
    vector<int> feature;
    o.getObjectField("LBP_8_1_FACE").Vals(feature);
   
    vec feat = conv_to<vec>::from(feature);
    Sample data(feat,label);
    dataSet.push_back(data);
 }
    return dataSet;
}

int main(int argc, char** argv) {
 
 DBClientConnection c;
 c.connect("localhost");
 auto_ptr<DBClientCursor> cursor = c.query(TrainingDB, Query(),0,0,NULL,QueryOption_NoCursorTimeout);
 vector<Sample> trainingSet = getDataSet(cursor);
 cursor = c.query(TestDB, Query(),0,0,NULL,QueryOption_NoCursorTimeout);
 vector<Sample> testSet = getDataSet(cursor);
 //cout<<trainingSet[0].getFeature()(0)<<endl;
 //cout<<trainingSet[0].getFeature()(1)<<endl;
 
 //Pegasos classifier(trainingSet[0].getFeature().n_elem,0.1,"./models");
 CPegasos classifier(trainingSet[0].getFeature().n_elem,0.1,"./models",10000,1.5);
 
 for(int i=0;i<100;i++){
    
    classifier.train(trainingSet);
    random_shuffle ( trainingSet.begin(), trainingSet.end() );
    classifier.validate(testSet);
    //cout<<i<<":  "<<classifier.test(testSet)<<endl;
 }
 return 0;
}

