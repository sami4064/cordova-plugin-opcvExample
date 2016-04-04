//
//  detector.h
//  cvCrimp
//
//  Created by Gabi Greenhorn on 15.02.16.
//
//

#ifndef detector_h
#define detector_h
#include "ofxAndroid.h"

#include "ofxOpenCv.h"
#include "ofxCv.h"

//#include "ofxAndroidWebView.h"

class Detector {

#define SIZE 200

public:
    Detector(){

    };

    void add(float val){

        // this is a ringbuffer for the samples
        // each sample is one frames detected colorcount
        // maybe you have a better implementation

        for (int i = SIZE-1; i > 0; i--) {
            buffer[i] = buffer[i-1];
            bin[i] = bin[i-1];
        }

        buffer[0] = val;
        bin[0] = val > threshold; // if the colorcount is higher than val we say it is on

        now++;
        if(now == SIZE) now = 0;
    };

    void update(){
        int now = 0;
        int last = 0;

        ups = 0;
        downs = 0;
        uptime = 0;
        downtime = 0;

        for (int i = 0; i < SIZE; i++) {
            now = bin[i];
            if(now != last){
                if(now == 1){
                    ups++;
                }
                if(now == 0){
                    downs++;
                }
            }
            if(now == 1){
                uptime++;
            }
            if(now == 0){
                downtime++;
            }
            last = now;
        }

        // this is a filter on the counts of on/offs of the color

        upsFilter += (ups-upsFilter)*interpolator;
        downsFilter += (downs-downsFilter)*interpolator;
        uptimeFilter += (uptime-uptimeFilter)*interpolator;
        downtimeFilter += (downtime-downtimeFilter)*interpolator;

    }

    void draw(){

        // this is for debugging only
        // generating a little graph
        // showing on/off the detected color

        ofPushMatrix();


        ofBeginShape();
        ofVertex(0,0);
        for (int i = 0; i < SIZE; i++) {
            ofVertex(i, buffer[i]);
        }
        ofVertex(SIZE,0);
        ofEndShape();

        ofBeginShape();
        ofVertex(0,-2);
        for (int i = 0; i < SIZE; i++) {
            ofVertex(i, -2 -20 * bin[i]);
        }
        ofVertex(SIZE,-2);
        ofEndShape();


        ofDrawBitmapString(ofToString(upsFilter,2) + " - " + ofToString(uptimeFilter,2), SIZE + 20, 0);
        ofDrawBitmapString(ofToString(downsFilter,2) + " - " + ofToString(downtimeFilter,2), SIZE + 20, 20);


        ofPopMatrix();
    }

    int now = 0;
    float buffer[SIZE] = { 0 };
    float bin[SIZE] = { 0 };

    float threshold;

    int ups = 0;
    int downs = 0;
    int uptime = 0;
    int downtime = 0;

    float upsFilter = 0;
    float downsFilter = 0;
    float uptimeFilter = 0;
    float downtimeFilter = 0;

    float interpolator = 0.1;

};

#endif /* detector_h */
