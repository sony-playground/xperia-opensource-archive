package com.sony.fl.json;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Json {

    private Json() {}

    /**
     * Java オブジェクトを JSON 文字列にシリアライズします。
     * <p>
     * <pre>{@code
     *   Initialize initialize = Initialize.newInstance();
     *   initialize.modelParams.server.globalWeight = "...";
     *   initialize.modelParams.server.graph.add("...");
     *   initialize.modelParams.server.graph.add("...");
     *   initialize.modelParams.server.weights.add("...");
     *   initialize.modelParams.server.weights.add("...");
     *   initialize.modelParams.client.clusterMap = "...";
     *
     *   String json = Json.serialize(initialize);
     * }</pre>
     * @param object JSON 文字列にシリアライズする Java オブジェクト
     * @return JSON 文字列
     * @param <T> (省略可)Java オブジェクトのクラス。省略しない場合の記述例 <code>String json = Json.&lt;Initialize&gt;serialize(initialize);</code>
     */
    public static <T> String serialize(T object) {
        ObjectMapper mapper = new ObjectMapper();
        try {
            return mapper.writeValueAsString(object);
        }
        catch (JsonProcessingException ex) {
            ex.printStackTrace();
            return null;
        }
    }

    /**
     * JSON 文字列を Java オブジェクトにデシリアライズします。
     * <p>
     * <pre>{@code
     *   String json = "{\"method\":\"Initialize\",\"modelParams\":{\"server\":{\"globalWeight\":\"aaa\",\"graph\":[\"bbb\",\"ccc\"],\"weights\":[\"ddd\",\"eee\"]},\"client\":{\"clusterMap\":\"fff\"}}}";
     *   Initialize initialize = Json.deserialize(json, Initialize.class);
     * }</pre>
     * @param json Java オブジェクトがシリアライズされた JSON 文字列
     * @param clazz デシリアライズする Java オブジェクトのクラス
     * @return Java オブジェクト
     * @param <T> (省略可)Java オブジェクトのクラス。省略しない場合の記述例 <code>Initialize initialize = Json.&lt;Initialize&gt;deserialize(json, Initialize.class);</code>
     */
    @SuppressWarnings({"rawtypes","unchecked"})
    public static <T> T deserialize(String json, Class clazz) {
        ObjectMapper mapper = new ObjectMapper();
        try {
            return (T)mapper.readValue(json, clazz);
        }
        catch (JsonProcessingException ex) {
            ex.printStackTrace();
            return null;
        }
    }
}
