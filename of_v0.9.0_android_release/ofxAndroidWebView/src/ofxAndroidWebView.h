/*
 *  ofxAndroidWebView.h
 *
 *  Created by Pelayo Méndez on 22/07/15
 *
 */


#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"

class ofxAndroidWebView {

 	public:

 		void showWebView(string url);
 		void hideWebView();

 	private:

 		string getClassName();

 		jclass javaClass;
		jobject javaObject;

 };