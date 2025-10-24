package com.sony.fl.tensor;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;
import com.fasterxml.jackson.databind.node.ArrayNode;

import com.sony.fl.logger.FLLogger;

/**
 * TensorMapクラスはテンソルをマップ(キー・バリューの形式)に保持します。
 * <p>マップからJSON文字列にシリアライズしたり、JSON文字列からマップにデシリアライズすることができます。
 * シリアライズしたJSON文字列は {@link com.sony.fl.tensor.DataSerializer } クラスを利用することでテンソルマップ・ファイルに保存することができます。
 */
public class TensorMap
{
    @SuppressWarnings("rawtypes")
    private final Map<String, Tensor> tensorMap;

    @SuppressWarnings("unused")
    private TensorMap()
    {
        this.tensorMap = new HashMap<>();
    }

    @SuppressWarnings("rawtypes")
    private TensorMap(Map<String, Tensor> tensorMap)
    {
        this.tensorMap = tensorMap;
    }

    /**
     * Tensorオブジェクトを格納します。
     *
     * <p>すでに同じテンソル名(キー名)のテンソルが格納されていたら上書きします。
     *
     * <pre>{@code
     *   Tensor x = Tensor.newTensor(TensorShape.createShape(16, 13), new Double[] {0.01, ..., 1, 1, 0});
     *
     *   TensorMap tensorMap = TensorMap.newInstance();
     *   tensorMap.set("x", x);
     * }</pre>
     *
     * @param key テンソル名です。すでに同じテンソル名(キー名)のテンソルが格納されていたら上書きします。
     * @param tensor Tensorオブジェクトを返します。
     */
    @SuppressWarnings("rawtypes")
    public void set(String key, Tensor tensor)
    {
        if (key == null) {
            throw new IllegalArgumentException("argument \"key\" is null");
        }
        if (tensor == null) {
            throw new IllegalArgumentException("argument \"tensor\" is null");
        }
        this.tensorMap.put(key, tensor);
    }

    /**
     * Tensorオブジェクトを取得します。マップにテンソルが含まれていない場合はnullを返します。
     *
     * <pre>{@code
     *   TensorMap tensorMap;
     *   try (BufferedReader br = new BufferedReader(new FileReader("sample.json"))) {
     *       tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
     *   } catch (Exception ex) {
     *     // (snip)
     *   }
     *
     *   Tensor<Double[]> x = tensorMap.get("x");
     *   Double[] arr = x.getValue();
     * }</pre>
     *
     * @param key テンソル名です。
     * @return Tensorオブジェクトを返します。マップにテンソルが含まれていない場合はnullを返します。
     */
    @SuppressWarnings("rawtypes")
    public Tensor get(String key)
    {
        if (key == null) {
            throw new IllegalArgumentException("argument \"key\" is null");
        }
        return this.tensorMap.get(key);
    }

    /**
     * JSON文字列にシリアライズします。JSON Linesに適した1行の文字列として出力します。
     *
     * <p>いくつかのテンソルを含むテンソルマップを作成してシリアライズした例です。
     * <pre>{@code
     *   TensorMap tensorMap = TensorMap.newInstance();
     *   tensorMap.set("num_of_features", Tensor.newTensor(13));
     *   tensorMap.set("group_label", Tensor.newTensor("1"));
     *   tensorMap.set("y", Tensor.newTensor(0));
     *   tensorMap.set("x", Tensor.newTensor(TensorShape.createShape(16, 13), new Double[] {
     *       0.857794,...
     *       ...,1.0,1.0,0.0
     *   }));
     *  System.out.printf("%s%n", tensorMap.toJsonString());
     * }</pre>
     *
     * <p>出力されたJSON文字列は以下のとおり1行です。<br>
     * <code>
     *   {"num_of_features":{"shape":[1],"value":[13]},"x":{"shape":[16,13],"value":[0.857794,...,1.0,1.0,0.0]},"group_label":{"shape":[1],"value":["1"]},"y":{"shape":[1],"value":[0]}}
     * }</code>
     * <br>
     *
     * @return JSON文字列を返します。
     */
    @SuppressWarnings("rawtypes")
    public String toJsonString()
    {
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
        for (Map.Entry<String, Tensor> e : this.tensorMap.entrySet())
        {
            Tensor tensor = e.getValue();

            ArrayNode value = new ObjectMapper().createArrayNode();
            if (e.getValue().isScalar()) {
                Object obj = tensor.getValue();
                if (obj instanceof Integer) {
                    value.add(((Integer)obj).intValue());
                } else
                if (obj instanceof Long) {
                    value.add(((Long)obj).longValue());
                } else
                if (obj instanceof Float) {
                    value.add(((Float)obj).floatValue());
                } else
                if (obj instanceof Double) {
                    value.add(((Double)obj).doubleValue());
                } else
                if (obj instanceof String) {
                    value.add((String)obj);
                }
            } else {
                Object obj = tensor.getValue();
                if (obj instanceof Integer[]) {
                    Integer[] arr = (Integer[])obj;
                    for (Integer integer : arr) value.add(integer);
                } else
                if (obj instanceof Long[]) {
                    Long[] arr = (Long[])obj;
                    for (Long aLong : arr) value.add(aLong);
                } else
                if (obj instanceof Float[]) {
                    Float[] arr = (Float[])obj;
                    for (Float aFloat : arr) value.add(aFloat);
                } else
                if (obj instanceof Double[]) {
                    Double[] arr = (Double[])obj;
                    for (Double aDouble : arr) value.add(aDouble);
                } else
                if (obj instanceof String[]) {
                    String[] arr = (String[])obj;
                    for (String s : arr) value.add(s);
                }
            }

            ArrayNode shape = new ObjectMapper().createArrayNode();
            final int dims = tensor.dims();
            for (int d = 0; d < dims; d++) {
                int dim = tensor.getDim(d);
                shape.add(dim);
            }

            ObjectNode node = new ObjectMapper().createObjectNode();
            node.set("shape", shape);
            node.set("value", value);

            ((ObjectNode)json).set(e.getKey(), node);
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

    @SuppressWarnings("unused")
    private static char getType(String fieldName, JsonNode jsonValue)
    {
        int double_count = 0;
        int float_count = 0;
        int long_count = 0;
        int int_count = 0;
        int string_count = 0;
        int unknown_count = 0;

        for (JsonNode v : jsonValue) {
            if (v.isDouble()) double_count++;
            else if (v.isFloat()) float_count++;    // NOTE: Probably, it will never be judged as Float type.
            else if (v.isLong()) long_count++;
            else if (v.isInt()) int_count++;
            else if (v.isTextual()) string_count++;
            else
                unknown_count++;
        }

        char type = '_';

        if (unknown_count <= 0) {
            if (string_count > 0) {
                if (double_count + float_count + long_count + int_count <= 0)
                    type = 's';
                else
                    type = '?';
            } else
            if (double_count > 0) {
                type = 'd';
            } else
            if (float_count > 0) {                  // NOTE: Probably, it will never be judged as Float type.
                type = 'f';
            } else
            if (long_count > 0) {
                type = 'l';
            } else
            if (int_count > 0) {
                type = 'i';
            }
        } else {
            type = '?';
        }

        return type;
    }

    private static TensorShape generateTensorShape(JsonNode jsonShape)
    {
        int[] shape = new int[jsonShape.size()];
        int ii = 0;
        for (JsonNode v : jsonShape) shape[ii++] = v.intValue();
        return TensorShape.createShape(shape);
    }

    @SuppressWarnings("unused")
    private static Object[] generateFloatArray(JsonNode jsonValue)
    {
        Float[] dimensional_value = new Float[jsonValue.size()];
        int ii = 0;
        for (JsonNode v : jsonValue) dimensional_value[ii++] = v.floatValue();
        return dimensional_value;
    }

    private static Object[] generateDoubleArray(JsonNode jsonValue)
    {
        Double[] dimensional_value = new Double[jsonValue.size()];
        int ii = 0;
        for (JsonNode v : jsonValue) dimensional_value[ii++] = v.doubleValue();
        return dimensional_value;
    }

    private static Object[] generateLongArray(JsonNode jsonValue)
    {
        Long[] dimensional_value = new Long[jsonValue.size()];
        int ii = 0;
        for (JsonNode v : jsonValue) dimensional_value[ii++] = v.longValue();
        return dimensional_value;
    }

    private static Object[] generateIntegerArray(JsonNode jsonValue)
    {
        Integer[] dimensional_value = new Integer[jsonValue.size()];
        int ii = 0;
        for (JsonNode v : jsonValue) dimensional_value[ii++] = v.intValue();
        return dimensional_value;
    }

    private static Object[] generateStringArray(JsonNode jsonValue)
    {
        String[] dimensional_value = new String[jsonValue.size()];
        int ii = 0;
        for (JsonNode v : jsonValue) dimensional_value[ii++] = v.textValue();
        return dimensional_value;
    }

    @SuppressWarnings("rawtypes")
    private static Tensor generateTensor(TensorShape shape, Object[] value)
    {
        return Tensor.newTensor(shape, value);
    }

    /**
     * JSON文字列からデシリアライズします。
     *
     * <pre>{@code
     *   TensorMap tensorMap;
     *   try (BufferedReader br = new BufferedReader(new FileReader("sample.json"))) {
     *       tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
     *   } catch (Exception ex) {
     *     // (snip)
     *   }
     *
     *   Tensor<Double[]> x = tensorMap.get("x");
     *   Double[] arr = x.getValue();
     * }</pre>
     *
     * <p>JSONではない文字列が指定されると(非チェック)例外 <code>com.fasterxml.jackson.core.JsonParseException</code> をスローします。<br>
     * 空のJSON <code>{}</code> を指定した場合は {@link #newInstance()} を呼び出した場合と同じ意味になります。<br>
     * 下記仕様を満さないキーや値は読み捨てます。例外はスローされません。<br>
     *
     * <p>JSONの仕様
     * <ol>
     * <li>一階層目は任意のキー名です。これがテンソル名になります。<br>
     * <pre>{@code
     *   {
     *     "tensor_name_A": {...},
     *     "tensor_name_B": {...},
     *     ...
     *   }
     * }</pre></li>
     * <li>二階層目にシェイプ("shape")と値("value")をテンソルの情報として格納します。<br>
     * <ol>
     *   <li>"shape" は整数の配列です。</li>
     *   <li>"value" は整数、実数、文字列の一次元配列です。要素数は "shape" に格納した整数を乗算した数になります。<br>
     *       整数は java.lang.Long あるいは java.lang.Integer にデシリアライズされます。実数は java.lang.Double、文字列は java.lang.String にデシリアライズされます。
     *   <pre>{@code
     *     "tensor_name_A": {
     *       "shape": [2, 3],
     *       "value": [1.0, 1.1, 1.2, 2.1, 2.2, 2.3]
     *     },
     *   }</pre></li>
     * </ol>
     * </ol>
     *
     * @param jsonString JSON文字列です。
     * @return デシリアライズされたTensorMapオブジェクトを返します。JSONではない文字列が指定されると(非チェック)例外 <code>com.fasterxml.jackson.core.JsonParseException</code> をスローします。
     */
    @SuppressWarnings("rawtypes")
    public static TensorMap fromJsonString(String jsonString)
    {
        if (jsonString == null) {
            throw new IllegalArgumentException("argument \"jsonString\" is null");
        }
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

        Map<String, Tensor> tensorMap = new HashMap<>();

        Iterator<String> fieldNames = json.fieldNames();
        while (fieldNames.hasNext())
        {
            String fieldName = fieldNames.next();
            JsonNode node = json.get(fieldName);

            if (!(node.isObject())) {
                FLLogger.w(String.format("%s is invalid. skipped.", fieldName));
                FLLogger.d(jsonString);
                continue;
            }

            if (!(node.has("shape"))) {
                FLLogger.w(String.format("%s is invalid. 'shape' not defined. skipped.", fieldName));
                FLLogger.d(jsonString);
                continue;
            }
            if (!(node.has("value"))) {
                FLLogger.w(String.format("%s is invalid. 'value' not defined. skipped.", fieldName));
                FLLogger.d(jsonString);
                continue;
            }

            JsonNode jsonShape = node.get("shape");
            JsonNode jsonValue = node.get("value");

            // Get type from Json node
            char type = TensorMap.getType(fieldName, jsonValue);

            if (type == '_') {
                FLLogger.w(String.format("%s is empty array", fieldName));
                FLLogger.d(jsonString);
                continue;
            } else
            if (type == '?') {
                FLLogger.w(String.format("%s is invalid array", fieldName));
                FLLogger.d(jsonString);
                continue;
            }

            Object[] value = null;

            if (type == 'd') 
                value = TensorMap.generateDoubleArray(jsonValue);
            else
            if (type == 'l')
                value = TensorMap.generateLongArray(jsonValue);
            else
            if (type == 'i')
                value = TensorMap.generateIntegerArray(jsonValue);
            else
            if (type == 's')
                value = TensorMap.generateStringArray(jsonValue);

            if (value == null) {
                FLLogger.w(String.format("%s is unknown. skipped.", fieldName));
                FLLogger.d(jsonString);
                continue;
            }

            // Generate TensorShape object
            TensorShape shape = generateTensorShape(jsonShape);

            if (shape == null) {
                FLLogger.w(String.format("%s is invalid shape. skipped.", fieldName));
                FLLogger.d(jsonString);
                continue;
            }

            // Generate Tensor object
            Tensor tensor = TensorMap.generateTensor(shape, value);

            if (tensor == null) {
                FLLogger.w(String.format("%s is invalid tensor. skipped.", fieldName));
                FLLogger.d(jsonString);
                continue;
            }

            // Put Tensor object to TensorMap
            tensorMap.put(fieldName, tensor);
        }

        return new TensorMap(tensorMap);
    }

    /**
     * 空のTensorMapオブジェクトを生成します。
     *
     * <pre>{@code
     *   TensorMap tensorMap = TensorMap.newInstance();
     *
     *   Tensor x = Tensor.newTensor(TensorShape.createShape(16, 13), new Double[] {0.01, ..., 1, 1, 0});
     *   tensorMap.set("x", x);
     * }</pre>
     *
     * @return 空のTensorMapオブジェクトを返します。
     */
    public static TensorMap newInstance()
    {
        return TensorMap.fromJsonString("{}");
    }
}
