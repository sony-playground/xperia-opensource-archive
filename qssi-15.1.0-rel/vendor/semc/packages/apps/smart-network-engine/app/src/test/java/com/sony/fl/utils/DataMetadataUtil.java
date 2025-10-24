package com.sony.fl.utils;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.sony.fl.tensor.DataMetadata;

public class DataMetadataUtil {
    public static DataMetadata newInstance() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Constructor<?> constructor = DataMetadata.class.getDeclaredConstructor();
        constructor.setAccessible(true);
        return (DataMetadata)constructor.newInstance();
    }
    public static void set(DataMetadata metaData, String key, String value) throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
        Method method = DataMetadata.class.getDeclaredMethod("set", String.class, String.class);
        method.setAccessible(true);
        method.invoke(metaData, key, value);
    }
}
