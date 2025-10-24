package com.sony.fl.tensor;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.nio.file.Files;
import java.nio.file.Paths;

public class TestTensorMap {
    private static final String VALID_JSON = "src/test/resources/NNHLCR/tensor/valid.json";
    private static final String INVALID_JSON = "src/test/resources/NNHLCR/tensor/invalid.json";
    private static final String PARSE_ERROR_JSON = "src/test/resources/NNHLCR/tensor/parse_error.json";
    private static final String SAMPLE_JSON = "src/test/resources/NNHLCR/tensor/sample.json";

    @Before
    public void setUp() {
        System.err.println("ENTER TestTensorMap#setUp");
    }

    @After
    public void tearDown() {
        System.err.println("ENTER TestTensorMap#tearDown");
    }

    @Test
    public void testNewInstance() {
        TensorMap tensorMap = TensorMap.newInstance();
        assertNotNull(tensorMap);
        assertEquals("{}", tensorMap.toJsonString());
    }

    @Test
    public void testFromJsonString() throws FileNotFoundException, IOException {
        StringBuffer jsonString = new StringBuffer();
        try (BufferedReader br = Files.newBufferedReader(Paths.get(TestTensorMap.VALID_JSON))) {
            br.lines().forEach(line -> {
                jsonString.append(line.trim());
            });
        }
        System.out.println(jsonString);

        TensorMap tensorMap = TensorMap.fromJsonString(jsonString.toString());
        assertNotNull(tensorMap);

        Tensor<Integer> integerScalar = tensorMap.get("integerScalar");
        assertNotNull(integerScalar);
        assertTrue(integerScalar.isScalar());
        Integer integerScalarValue = integerScalar.getValue();
        assertEquals(7, integerScalarValue.intValue());

        Tensor<Long> longScalar = tensorMap.get("longScalar");
        assertNotNull(longScalar);
        assertTrue(longScalar.isScalar());
        Long longScalarValue = longScalar.getValue();
        assertEquals(9223372036854775807L, longScalarValue.longValue());

        Tensor<Double> actualScalar = tensorMap.get("actualScalar");
        assertNotNull(actualScalar);
        assertTrue(actualScalar.isScalar());
        Double actualScalarValue = actualScalar.getValue();
        assertEquals(1.234567, actualScalarValue.doubleValue(), 0.0);

        Tensor<String> stringScalar = tensorMap.get("stringScalar");
        assertNotNull(stringScalar);
        assertTrue(stringScalar.isScalar());
        String stringScalarValue = stringScalar.getValue();
        assertEquals("ABC", stringScalarValue);

        Tensor<Integer[]> integerTensor = tensorMap.get("integerTensor");
        assertNotNull(integerTensor);
        assertFalse(integerTensor.isScalar());
        assertEquals(2, integerTensor.dims());
        assertEquals(2, integerTensor.getDim(0));
        assertEquals(3, integerTensor.getDim(1));
        assertEquals(6, integerTensor.size());
        Integer[] integerTensorValue = integerTensor.getValue();
        assertEquals(11, integerTensorValue[0].intValue());
        assertEquals(12, integerTensorValue[1].intValue());
        assertEquals(13, integerTensorValue[2].intValue());
        assertEquals(21, integerTensorValue[3].intValue());
        assertEquals(22, integerTensorValue[4].intValue());
        assertEquals(23, integerTensorValue[5].intValue());

        Tensor<Long[]> longTensor = tensorMap.get("longTensor");
        assertNotNull(longTensor);
        assertFalse(longTensor.isScalar());
        assertEquals(2, longTensor.dims());
        assertEquals(3, longTensor.getDim(0));
        assertEquals(2, longTensor.getDim(1));
        assertEquals(6, longTensor.size());
        Long[] longTensorValue = longTensor.getValue();
        assertEquals(9223372036854775802L, longTensorValue[0].longValue());
        assertEquals(9223372036854775803L, longTensorValue[1].longValue());
        assertEquals(9223372036854775804L, longTensorValue[2].longValue());
        assertEquals(9223372036854775805L, longTensorValue[3].longValue());
        assertEquals(9223372036854775806L, longTensorValue[4].longValue());
        assertEquals(9223372036854775807L, longTensorValue[5].longValue());

        Tensor<Double[]> actualTensor = tensorMap.get("actualTensor");
        assertNotNull(actualTensor);
        assertFalse(actualTensor.isScalar());
        assertEquals(2, actualTensor.dims());
        assertEquals(16, actualTensor.getDim(0));
        assertEquals(13, actualTensor.getDim(1));
        assertEquals(208, actualTensor.size());
        Double[] actualTensorValue = actualTensor.getValue();
        assertEquals(0.857794, actualTensorValue[0].doubleValue(), 0.0);
        assertEquals(0.000000, actualTensorValue[12].doubleValue(), 0.0);
        assertEquals(1.053484, actualTensorValue[13].doubleValue(), 0.0);
        assertEquals(0.000000, actualTensorValue[194].doubleValue(), 0.0);
        assertEquals(1.927778, actualTensorValue[195].doubleValue(), 0.0);
        assertEquals(0.000000, actualTensorValue[207].doubleValue(), 0.0);

        Tensor<String[]> stringTensor = tensorMap.get("stringTensor");
        assertNotNull(stringTensor);
        assertFalse(stringTensor.isScalar());
        assertEquals(2, stringTensor.dims());
        assertEquals(2, stringTensor.getDim(0));
        assertEquals(3, stringTensor.getDim(1));
        assertEquals(6, stringTensor.size());
        String[] stringTensorValue = stringTensor.getValue();
        assertEquals("C1R1", stringTensorValue[0]);
        assertEquals("C2R1", stringTensorValue[1]);
        assertEquals("C3R1", stringTensorValue[2]);
        assertEquals("C1R2", stringTensorValue[3]);
        assertEquals("C2R2", stringTensorValue[4]);
        assertEquals("C3R2", stringTensorValue[5]);
    }

    @Test
    public void testMaxValue() throws FileNotFoundException, IOException {
        StringBuffer jsonString = new StringBuffer();
        try (BufferedReader br = Files.newBufferedReader(Paths.get(TestTensorMap.SAMPLE_JSON))) {
            br.lines().forEach(line -> {
                jsonString.append(line.trim());
            });
        }
        System.out.println("Read from ...");
        System.out.println(jsonString);

        TensorMap tensorMap;
        Tensor<Integer> integerScalar;
        Tensor<Long> longScalar;
        Tensor<Double> floatScalar;
        Tensor<Double> doubleScalar;
        Tensor<String> stringScalar;

        tensorMap = TensorMap.fromJsonString(jsonString.toString());
        assertNotNull(tensorMap);

        integerScalar = tensorMap.get("integerScalar");
        assertNotNull(integerScalar);
        assertTrue(integerScalar.isScalar());
        Integer integerScalarValue = integerScalar.getValue();
        assertEquals(Integer.MAX_VALUE, integerScalarValue.intValue());

        longScalar = tensorMap.get("longScalar");
        assertNotNull(longScalar);
        assertTrue(longScalar.isScalar());
        Long longScalarValue = longScalar.getValue();
        assertEquals(Long.MAX_VALUE, longScalarValue.longValue());

        floatScalar = tensorMap.get("floatScalar");
        assertNotNull(floatScalar);
        assertTrue(floatScalar.isScalar());
        // Float floatScalarValue = floatScalar.getValue();  // DO NOT USE Float
        Double floatScalarValue = floatScalar.getValue();
        assertEquals(Float.MAX_VALUE, floatScalarValue.floatValue(), 0.0);

        doubleScalar = tensorMap.get("doubleScalar");
        assertNotNull(doubleScalar);
        assertTrue(doubleScalar.isScalar());
        Double doubleScalarValue = doubleScalar.getValue();
        assertEquals(Double.MAX_VALUE, doubleScalarValue.doubleValue(), 0.0);

        stringScalar = tensorMap.get("stringScalar");
        assertNotNull(stringScalar);
        assertTrue(stringScalar.isScalar());
        String stringScalarValue = stringScalar.getValue();
        assertEquals("Hello, Goodbye", stringScalarValue);

        //
        tensorMap = TensorMap.newInstance();
        assertNotNull(tensorMap);

        integerScalar = Tensor.newTensor(Integer.MAX_VALUE);
        tensorMap.set("integerScalar", integerScalar);
        longScalar = Tensor.newTensor(Long.MAX_VALUE);
        tensorMap.set("longScalar", longScalar);
        floatScalar = Tensor.newTensor(Float.MAX_VALUE);
        tensorMap.set("floatScalar", floatScalar);
        doubleScalar = Tensor.newTensor(Double.MAX_VALUE);
        tensorMap.set("doubleScalar", doubleScalar);
        stringScalar = Tensor.newTensor("Goodbye, Hello");
        tensorMap.set("stringScalar", stringScalar);

        System.out.println("Write to ...");
        System.out.println(tensorMap.toJsonString());
    }

    @Test
    public void testSet() {
        TensorMap tensorMap = TensorMap.newInstance();
        assertNotNull(tensorMap);

        Tensor integerScalarA = Tensor.newTensor(1);
        assertTrue(integerScalarA.isScalar());
        tensorMap.set("integerScalarA", integerScalarA);

        Tensor integerScalarB = Tensor.newTensor(TensorShape.createShape(1), new Integer[] {2});
        assertTrue(integerScalarB.isScalar());
        tensorMap.set("integerScalarB", integerScalarB);

        assertTrue(integerScalarA.isSameSize(integerScalarB));

        Tensor longScalarA = Tensor.newTensor(9223372036854775807L);
        assertTrue(longScalarA.isScalar());
        tensorMap.set("longScalarA", longScalarA);

        Tensor longScalarB = Tensor.newTensor(TensorShape.createShape(1), new Long[] {9223372036854775806L});
        assertTrue(longScalarB.isScalar());
        tensorMap.set("longScalarB", longScalarB);

        assertTrue(longScalarA.isSameSize(longScalarB));

        Tensor actualScalarA = Tensor.newTensor(1.1);
        assertTrue(actualScalarA.isScalar());
        tensorMap.set("actualScalarA", actualScalarA);

        Tensor actualScalarB = Tensor.newTensor(TensorShape.createShape(1), new Double[] {9.9});
        assertTrue(actualScalarB.isScalar());
        tensorMap.set("actualScalarB", actualScalarB);

        assertTrue(actualScalarA.isSameSize(actualScalarB));

        Tensor stringScalarA = Tensor.newTensor("AAA");
        assertTrue(stringScalarA.isScalar());
        tensorMap.set("stringScalarA", stringScalarA);

        Tensor stringScalarB = Tensor.newTensor(TensorShape.createShape(1), new String[] {"BBB"});
        assertTrue(stringScalarB.isScalar());
        tensorMap.set("stringScalarB", stringScalarB);

        assertTrue(stringScalarA.isSameSize(stringScalarB));

        Tensor integerTensor = Tensor.newTensor(
            TensorShape.createShape(3, 2),
            new Integer[] {
                11, 12,
                21, 22,
                31, 32,
            }
        );
        assertFalse(integerTensor.isScalar());
        tensorMap.set("integerTensor", integerTensor);

        Tensor longTensor = Tensor.newTensor(
            TensorShape.createShape(2, 3),
            new Long[] {
                9223372036854775802L, 9223372036854775803L, 9223372036854775804L,
                9223372036854775805L, 9223372036854775806L, 9223372036854775807L,
            }
        );
        assertFalse(longTensor.isScalar());
        tensorMap.set("longTensor", longTensor);

        Tensor actualTensor = Tensor.newTensor(
            TensorShape.createShape(2, 3),
            Tensor.toDoubleArrayFrom(
                new float[][] {
                    { 1.1F, 1.2F, 1.3F },
                    { 2.1F, 2.2F, 2.3F },
                }
            )
        );
        assertFalse(actualTensor.isScalar());
        tensorMap.set("actualTensor", actualTensor);

        Tensor stringTensor = Tensor.newTensor(
            TensorShape.createShape(3),
            new String[] { "C1R1", "C1R2", "C1R3", }
        );
        assertFalse(stringTensor.isScalar());
        tensorMap.set("stringTensor", stringTensor);

        System.out.println(tensorMap.toJsonString());
        System.out.println(Long.MAX_VALUE);
    }

    @Test
    public void testFromJsonString_ContainsInvalidData() throws FileNotFoundException, IOException {
        StringBuffer jsonString = new StringBuffer();
        try (BufferedReader br = Files.newBufferedReader(Paths.get(TestTensorMap.INVALID_JSON))) {
            br.lines().forEach(line -> {
                jsonString.append(line.trim());
            });
        }
        System.out.println(jsonString);

        TensorMap tensorMap = TensorMap.fromJsonString(jsonString.toString());
        assertNotNull(tensorMap);
    }

    @Test(expected = RuntimeException.class)
    public void testFromJsonString_InvalidJSON() throws FileNotFoundException, IOException {
        StringBuffer jsonString = new StringBuffer();
        try (BufferedReader br = Files.newBufferedReader(Paths.get(TestTensorMap.PARSE_ERROR_JSON))) {
            br.lines().forEach(line -> {
                jsonString.append(line.trim());
            });
        }
        System.out.println(jsonString);

        try {
            TensorMap tensorMap = TensorMap.fromJsonString(jsonString.toString());
        }
        catch (RuntimeException ex) {   // as expected
            ex.printStackTrace();
            throw ex;
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void testSet_arg1_null() {
        TensorMap tensorMap = TensorMap.newInstance();
        assertNotNull(tensorMap);

        Tensor tensor = Tensor.newTensor(1);
        try {
            tensorMap.set(null, tensor);
        }
        catch (IllegalArgumentException ex) {
            ex.printStackTrace();
            throw ex;
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void testSet_arg2_null() {
        TensorMap tensorMap = TensorMap.newInstance();
        assertNotNull(tensorMap);

        Tensor tensor = null;
        try {
            tensorMap.set("tensor", tensor);
        }
        catch (IllegalArgumentException ex) {
            ex.printStackTrace();
            throw ex;
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void testGet_arg_null() {
        TensorMap tensorMap = TensorMap.newInstance();
        assertNotNull(tensorMap);

        try {
            tensorMap.get(null);
        }
        catch (IllegalArgumentException ex) {
            ex.printStackTrace();
            throw ex;
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void testFromJsonString_arg_null() {
        try {
            TensorMap.fromJsonString(null);
        }
        catch (IllegalArgumentException ex) {
            ex.printStackTrace();
            throw ex;
        }
    }
}
