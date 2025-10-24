package com.sony.fl.jni;

public class NNHLCRNativeJNI {
    static {
	    // lib***.so
        System.loadLibrary("NNHLCRNative");
    }

    // native method
    public native long Initialize(String modelInfo);
    public native String Training(long mlObj, String metaDataString, String trainInfo);
    public native String Evaluation(long mlObj, String metaDataString, String evaluationInfo);
    public native String Prediction(long mlObj, String tensorMapString);
    public native void Finalize(long mlObj);
    public native String UpdateInfo(long mlObj, String metaDataString,
            String updateClusterMapInfo);
}
