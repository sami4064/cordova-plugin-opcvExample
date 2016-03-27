//
//  detectorManager.h
//  cvCrimp
//
//  Created by Gabi Greenhorn on 15.02.16.
//
//
class ofApp;
#include "detector.h"

#ifndef detectorManager_h
#define detectorManager_h


class DetectorManager {


public:
    ofApp * app;
    Detector detectorRed, detectorOrange, detectorGreen;
    float numRed, numOrange, numGreen;
    cv::Mat camMat, camHsv, redMat, greenMat, orangeMat, outMat;

    int hueFrom, hueTo, saturationFrom, saturationTo, volFrom, volTo, red, orange, green, thresh, threshDetect;

    int w,h;

    int detected = 0;
    ofTrueTypeFont myfont;

    int detectedCode = 0;
    int detectedCodeCount = 0;
    int maxDiff = 10;
    int detectionCountMax = 30;

    float code[11][6] = {
            { 0,        0,      16},
            { 200,      200,    200},
            { 200,      200,    0},
            { 0,        200,    0},
            { 0,        70,     0},
            { 70,       0,      70},
            { 32,       5,      32},
            { 200,      0,      0},
            { 100,      0,      0},
            { 70,      0,      0},
    };



    DetectorManager(){
        
        hueFrom = 50;
        hueTo = 113;
        saturationFrom = 181;
        saturationTo = 255;
        volFrom = 138;
        volTo = 271;
        red = 358;
        orange = 48;
        green = 167;
        thresh = 10;


    }

    void setup(ofApp* app){
        this->app = app;
        myfont.load("verdana.ttf", 150);
    }

    double lastTime = ofGetElapsedTimeMillis();
    int nbFrames = 0;
    int nbFramesOld = 0;
    float nbFramesFilter = 0;

    void loadFrame(cv::Mat _camMat){
        camMat = _camMat;
        cv::cvtColor(camMat, camHsv, cv::COLOR_RGB2HSV);


        cv::inRange(camHsv, cv::Scalar((red-thresh)/2, saturationFrom, volFrom),
                    cv::Scalar((red+thresh)/2, saturationTo, volTo), redMat);
        cv::inRange(camHsv, cv::Scalar((orange-thresh)/2, saturationFrom, volFrom),
                    cv::Scalar((orange+thresh)/2, saturationTo, volTo), orangeMat);
        cv::inRange(camHsv, cv::Scalar((green-thresh)/2, saturationFrom, volFrom),
                    cv::Scalar((green+thresh)/2, saturationTo, volTo), greenMat);

        numRed = cv::countNonZero(redMat == 255)* 1.0 / (w) ;
        numOrange = cv::countNonZero(orangeMat == 255)* 1.0 / (w);
        numGreen = cv::countNonZero(greenMat == 255)* 1.0 / (w);

        detectorRed.add(numRed);
        detectorOrange.add(numOrange);
        detectorGreen.add(numGreen);

        detectorRed.update();
        detectorOrange.update();
        detectorGreen.update();



        update();


    }

    void update(){
        int diff;
        detected = 0;

        for (int i = 0; i < 9; i++) {
            diff = 0;
            diff += abs(code[i][0]-detectorRed.uptimeFilter);
            diff += abs(code[i][1]-detectorOrange.uptimeFilter);
            diff += abs(code[i][2]-detectorGreen.uptimeFilter);
            
            // this is where the detection is made
            // if this statement is true, i want to have a callback
            // to my cordova app in javascript
            // returning the detected number (1-10)
            
            if(diff < maxDiff){
                //cout << "found:" << i << endl;
                detected = i+1;
            }

        }

        if(detected != 0){
            if(detectedCode != detected){
                detectedCodeCount = 0;
            } else {
                detectedCodeCount++;
            }
            detectedCode = detected;
        } else {
            detectedCode = 0;
            detectedCodeCount = 0;
        }


        if(detectedCodeCount > detectionCountMax){
            detectionCallback(detectedCode);
        }
    }

    void detectionCallback(int code);

    void draw() {

        // this stuff is just for debugging purposes
        // if you want, you can do something simmilar in
        // the plugin

        ofDrawBitmapString(ofToString(detected), 400, 400);

        ofPushMatrix();
        ofTranslate(0, 300);
        ofSetColor(255, 0, 0);
        detectorRed.draw();

        ofTranslate(0, 80);
        ofSetColor(255, 200, 0);
        detectorOrange.draw();

        ofTranslate(0, 80);
        ofSetColor(0, 255, 0);
        detectorGreen.draw();
        ofPopMatrix();

        ofPushMatrix();
        myfont.drawString(ofToString(detectedCode), 200, 200);
        myfont.drawString(ofToString(detectedCodeCount), 500, 200);
        ofPopMatrix();
    }
};


#endif /* detectorManager_h */
