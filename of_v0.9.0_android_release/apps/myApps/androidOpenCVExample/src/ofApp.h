#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"

#include "ofxOpenCv.h"
#include "ofxCv.h"

//#include "ofxAndroidWebView.h"

#include "detectorManager.h"

class ofApp : public ofxAndroidApp{
	
	public:
	//Detection result sender to java
	void sendDetectionResultStringtoJava(std::string message);
	void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

		void touchDown(int x, int y, int id);
		void touchMoved(int x, int y, int id);
		void touchUp(int x, int y, int id);
		void touchDoubleTap(int x, int y, int id);
		void touchCancelled(int x, int y, int id);
		void swipe(ofxAndroidSwipeDir swipeDir, int id);

		void pause();
		void stop();
		void resume();
		void reloadTextures();

		bool backPressed();
		void okPressed();
		void cancelPressed();

		ofVideoGrabber video;

		int w,h;

        DetectorManager detector;

     //   ofxAndroidWebView webView;
};
