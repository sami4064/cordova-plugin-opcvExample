ofxAndroidWebView
================

OpenFrameworks addon to use webviews with ofxAndroid

How to use the addon in your project
--------

Download the addon and place it in your openFrameworks addon's folder. Add "ofxAndroidWebView" to 'addons.make' file inside your project to include the addon.

After that you'll have to modify 'main_layout.xml' inside your res/layout folder and add after the "add here other views' layouts" comment this lines:

		<WebView
        android:id="@+id/webView1"
        android:layout_width="fill_parent"
        android:layout_height="fill_parent"
        android:layout_gravity="center" 
        android:visibility="gone" />


Check 'OFActivity.java' file inside the androidWebView example project and copy all the ofxAndroidWebView methods there into your project 'ofActvity.java' Look also for all the missing imports you need on top of the file.

OF Version
--------

Tested with OF 0.8.4 in OSX