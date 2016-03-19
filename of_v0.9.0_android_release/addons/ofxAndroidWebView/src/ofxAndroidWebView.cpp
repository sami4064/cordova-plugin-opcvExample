/*
 *  ofxAndroidWebView.cpp
 *
 *  Created by Pelayo Méndez on 22/07/15
 *
 */

#include "ofxAndroidWebView.h"

void ofxAndroidWebView::showWebView(string url)
{

	JNIEnv *env = ofGetJNIEnv();

	ofLog() << getClassName();
	
	jclass localClass = env->FindClass(getClassName().c_str());
	javaClass = (jclass) env->NewGlobalRef(localClass);
	if (!javaClass) {
		ofLogError() << "javaClass not found!" << endl;
	}

	javaObject = ofGetOFActivityObject();
	javaObject = (jobject) env->NewGlobalRef(javaObject);
	if (!javaObject) {
		ofLogError() << "javaObject not found!" << endl;
	}

	jmethodID javaShowWebViewMethod = env->GetMethodID(javaClass,"showWebView","(Ljava/lang/String;)V");
	if(!javaShowWebViewMethod){
		ofLogError() << "javaShowWebViewMethod not found!" << endl;
	}

	jstring jMsg = env->NewStringUTF(url.c_str());
	env->CallVoidMethod(javaObject,javaShowWebViewMethod,jMsg);
	env->DeleteLocalRef((jobject)jMsg);

};
 		
 void ofxAndroidWebView::hideWebView() 
 {

 	JNIEnv *env = ofGetJNIEnv();

	jclass localClass = env->FindClass(getClassName().c_str());
	javaClass = (jclass) env->NewGlobalRef(localClass);
	if (!javaClass) {
		ofLogError() << "javaClass not found!" << endl;
	}

	javaObject = ofGetOFActivityObject();
	javaObject = (jobject) env->NewGlobalRef(javaObject);
	if (!javaObject) {
		ofLogError() << "javaObject not found!" << endl;
	}

	jmethodID javaHideWebViewMethod = env->GetMethodID(javaClass,"hideWebView","()V");
	if(!javaHideWebViewMethod){
		ofLogError() << "javaHideWebViewMethod not found!" << endl;
	}
	env->CallVoidMethod(javaObject,javaHideWebViewMethod);
 	
 };


string ofxAndroidWebView::getClassName()
{

	JNIEnv *env = ofGetJNIEnv();

	jobject activity = ofGetOFActivityObject();
	jclass android_content_Context =  env->GetObjectClass(activity);
	jmethodID midGetPackageName = env->GetMethodID(android_content_Context,"getPackageName", "()Ljava/lang/String;");
	jstring packageName= (jstring)env->CallObjectMethod(activity, midGetPackageName);
	jboolean isCopy;
	string className = env->GetStringUTFChars(packageName,&isCopy);
	ofStringReplace(className,".","/");
	className = className + "/OFActivity";
	return className;

};
