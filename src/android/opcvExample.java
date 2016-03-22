package com.plugin.opcvExample;

import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaInterface;
import android.util.Log;
import android.provider.Settings;
import android.content.Intent;

import android.widget.Toast;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import cc.openframeworks.androidOpenCVExample.OFActivity;

public class opcvExample extends CordovaPlugin {
    
    public static final String TAG = "opcv Example";
    
    /**
     * Constructor.
     */
    public opcvExample() {}
    
    /**
     * Sets the context of the Command. This can then be used to do things like
     * get file paths associated with the Activity.
     *
     * @param cordova The context of the main Activity.
     * @param webView The CordovaWebView Cordova is running in.
     */
    
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        Log.v(TAG,"Init opcvExample");
    }
    
    public boolean execute(final String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        
        final int duration = Toast.LENGTH_SHORT;
        // Shows a toast
        Log.v(TAG,"opcvExample received:"+ action);
        
        
        cordova.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                Toast toast = Toast.makeText(cordova.getActivity().getApplicationContext(), action, duration);
                toast.show();
                Intent in = new Intent(cordova.getActivity().getApplicationContext(), OFActivity.class);
                cordova.getActivity().startActivity(in);
            }
        });
        
        return true;
    }
}