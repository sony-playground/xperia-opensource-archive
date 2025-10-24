package com.sony.fl.jni;

public class LinearHLCRNativeJNI {
    static {
	    // lib***.so
        System.loadLibrary("LinearHLCRNative");
    }

    // native method
    public native long Initialize(String jsonParams);
    public native String Training(long mlObj, String jsonParams);
    public native String Evaluation(long mlObj, String jsonParams);
    public native String Prediction(long mlObj, String jsonParams);
    public native void Finalize(long mlObj);
    public native String UpdateInfo(long mlObj, String jsonParams);
}
