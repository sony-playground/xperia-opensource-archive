package com.sony.fl.tensor;

import java.util.HashMap;
import java.util.Iterator;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

/**
 * DataMetadata クラスは key と value をマッピングします。
 * DataMetadata オブジェクトにマッピングされた key と value を JSON 文字列にシリアライズします。
 */
public class DataMetadata {
    HashMap<String, String> metadata = new HashMap<>();

    /**
     * DataMetadata オブジェクトを生成します。
     */
    protected DataMetadata() {
    }

    /**
     * 指定された key に関連付けられた value を返します。
     *
     * @param key  キー
     * @return  値を返します。キーが存在しない場合は null を返します。
     */
    public String get(String key) {
        return this.metadata.get(key);
    }

    /**
     * 指定された key と value をマッピングして保存します。key が存在していた場合、value が上書きされます。
     *
     * @param key  キー
     * @param value  値
     */
    protected void set(String key, String value) {
        this.metadata.put(key, value);
    }

    /**
     * DataMetadata オブジェクトに格納された key と value を JSON 文字列として返します。
     *
     * @return  DataMetadata オブジェクトに格納された key と value を JSON 文字列として返します。key と value が 1 つも存在しない場合は空の JSON 文字列 ("{}") を返します。
     */
    public String toJsonString() {
        JsonNode json;
        try
        {
            json = new ObjectMapper().readTree("{}");
        }
        catch (JsonProcessingException ex)
        {
            ex.printStackTrace();
            throw new RuntimeException("json string conversion error", ex);
        }
        for (HashMap.Entry<String, String> e : this.metadata.entrySet())
        {
            ((ObjectNode)json).put(e.getKey(), e.getValue());
        }

        try
        {
            return new ObjectMapper().writeValueAsString(json);
        }
        catch (JsonProcessingException ex)
        {
            ex.printStackTrace();
            throw new RuntimeException("json string conversion error", ex);
        }
    }

    /**
     *
     */
    public static DataMetadata fromJsonString(String jsonString) {
        JsonNode json;
        try
        {
            json = new ObjectMapper().readTree(jsonString);
        }
        catch (JsonProcessingException ex)
        {
            ex.printStackTrace();
            throw new RuntimeException("json string conversion error", ex);
        }

        DataMetadata me = new DataMetadata();

        Iterator<String> fieldNames = json.fieldNames();
        while (fieldNames.hasNext())
        {
            String fieldName = fieldNames.next();
            JsonNode node = json.get(fieldName);

            if (!(node.isTextual())) { continue; }

            me.set(fieldName, node.textValue());
        }

        return me;
    }
}
