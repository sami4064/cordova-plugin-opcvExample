package cc.openframeworks.androidOpenCVExample;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import cc.openframeworks.OFAndroid;

import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;

import org.json.JSONException;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;


public class OFActivity extends cc.openframeworks.OFActivity {

    public static final int DETECTION_REQUEST_CODE = 1010;
    public static OFActivity ofActivity;
    public static void detectionCallback(final String code){
        ofActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Log.d("detected result", code);
                Toast.makeText(ofActivity.getApplicationContext(), "detected result" + code, Toast.LENGTH_LONG).show();
                ofActivity.finishActivity(DETECTION_REQUEST_CODE);
            }
        });
    }


	@Override
    public void onCreate(Bundle savedInstanceState)
    { 
        super.onCreate(savedInstanceState);
        String packageName = getPackageName();
        ofActivity=this;
        ofApp = new OFAndroid(packageName,this);


    }



    ///////////////////////////////////////////////////////////////
    // ofxAndroidWebView methods - END
    ///////////////////////////////////////////////////////////////


	@Override
	public void onDetachedFromWindow() {
	}
	
    @Override
    protected void onPause() {
        super.onPause();
        ofApp.pause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        ofApp.resume();
    }
    
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
	if (OFAndroid.keyDown(keyCode, event)) {
	    return true;
	} else {
	    return super.onKeyDown(keyCode, event);
	}
    }
    
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
	if (OFAndroid.keyUp(keyCode, event)) {
	    return true;
	} else {
	    return super.onKeyUp(keyCode, event);
	}
    }


	OFAndroid ofApp;
    
	
	
    // Menus
    // http://developer.android.com/guide/topics/ui/menus.html
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	// Create settings menu options from here, one by one or infalting an xml
        return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	// This passes the menu option string to OF
    	// you can add additional behavior from java modifying this method
    	// but keep the call to OFAndroid so OF is notified of menu events
    	if(OFAndroid.menuItemSelected(item.getItemId())){
    		
    		return true;
    	}
    	return super.onOptionsItemSelected(item);
    }
    

    @Override
    public boolean onPrepareOptionsMenu (Menu menu){
    	// This method is called every time the menu is opened
    	//  you can add or remove menu options from here
    	return  super.onPrepareOptionsMenu(menu);
    }
	
}



