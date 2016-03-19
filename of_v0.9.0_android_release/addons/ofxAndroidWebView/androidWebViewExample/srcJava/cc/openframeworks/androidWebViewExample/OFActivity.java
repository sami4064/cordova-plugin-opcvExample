package cc.openframeworks.androidWebViewExample;

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import cc.openframeworks.OFAndroid;


public class OFActivity extends cc.openframeworks.OFActivity{
	
	@Override
    public void onCreate(Bundle savedInstanceState)
    { 
        super.onCreate(savedInstanceState);
        String packageName = getPackageName();
 
        ofApp = new OFAndroid(packageName,this);
    }
	
	///////////////////////////////////////////////////////////////
	// ofxAndroidWebView methods - START
	///////////////////////////////////////////////////////////////
	
	WebView wb;
    private class HelloWebViewClient extends WebViewClient {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            return false;
        }
    }
	
	public void showWebView(final String url) {
		
		Log.i("OF", "Loading url: " + url);
		
		this.runOnUiThread(new Runnable() {
			public void run() {
				wb=(WebView)findViewById(R.id.webView1);        
		        //wb.getSettings().setJavaScriptEnabled(true);
		        wb.getSettings().setLoadWithOverviewMode(true);
		        wb.getSettings().setUseWideViewPort(true);
		        wb.getSettings().setBuiltInZoomControls(true);
		        wb.getSettings().setPluginState(WebSettings.PluginState.ON);      
		        wb.setWebViewClient(new HelloWebViewClient());
		        wb.loadUrl(url);  
		        wb.setVisibility(View.VISIBLE);
			}		
		});
		
	}
	
	public void hideWebView() {
		
		this.runOnUiThread(new Runnable() {
			public void run() {
				wb=(WebView)findViewById(R.id.webView1);
				wb.setVisibility(View.GONE);
			}		
		});
		
	}
	
	@Override
	public void onBackPressed() {
		hideWebView();
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



