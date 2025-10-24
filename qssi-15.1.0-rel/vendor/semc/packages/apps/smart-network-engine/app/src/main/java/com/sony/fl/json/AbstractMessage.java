package com.sony.fl.json;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public abstract class AbstractMessage {
    public String method;

    protected abstract String myName();

    @SuppressWarnings({"rawtypes","unchecked"})
    protected static AbstractMessage newInstance(Class clazz) {
        try {
            Constructor constructor = clazz.getConstructor();
            AbstractMessage me = (AbstractMessage)constructor.newInstance();
            me.method = me.myName();
            return me;
        }
        catch (NoSuchMethodException|InstantiationException|IllegalAccessException|InvocationTargetException ex) {
            return null;
        }
    }
}
