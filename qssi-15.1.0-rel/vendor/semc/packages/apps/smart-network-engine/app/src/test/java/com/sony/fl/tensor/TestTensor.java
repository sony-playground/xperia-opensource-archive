package com.sony.fl.tensor;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class TestTensor {

    @Test
    public void testToDoubleArrayFrom() {
        float[][] floatMatrix = new float[][] {
            { 1.1F, 1.2F, 1.3F },
            { 2.1F, 2.2F, 2.3F },
        };
        Double[] doubleArray = Tensor.toDoubleArrayFrom(floatMatrix);

        assertEquals(1.1F, doubleArray[0].doubleValue(), 0.0);
        assertEquals(1.2F, doubleArray[1].doubleValue(), 0.0);
        assertEquals(1.3F, doubleArray[2].doubleValue(), 0.0);
        assertEquals(2.1F, doubleArray[3].doubleValue(), 0.0);
        assertEquals(2.2F, doubleArray[4].doubleValue(), 0.0);
        assertEquals(2.3F, doubleArray[5].doubleValue(), 0.0);

        assertEquals(floatMatrix[0][0], doubleArray[0].doubleValue(), 0.0);
        assertEquals(floatMatrix[0][1], doubleArray[1].doubleValue(), 0.0);
        assertEquals(floatMatrix[0][2], doubleArray[2].doubleValue(), 0.0);
        assertEquals(floatMatrix[1][0], doubleArray[3].doubleValue(), 0.0);
        assertEquals(floatMatrix[1][1], doubleArray[4].doubleValue(), 0.0);
        assertEquals(floatMatrix[1][2], doubleArray[5].doubleValue(), 0.0);

        Tensor tensor = Tensor.newTensor(TensorShape.createShape(2, 3), doubleArray);
        assertNotNull(tensor);
    }

    @Test
    public void testNewTensor_Vector_Integer() {
        TensorShape shape = TensorShape.createShape(5);

        Tensor tensor = Tensor.newTensor(shape, new Integer[] { 1, 2, 3, 4, 5 });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(5, tensor.getDim(0));
        assertEquals(5, tensor.size());

        Integer[] vector = (Integer[])tensor.getValue();
        assertEquals(5, vector.length);

        assertEquals(1, vector[0].intValue());
        assertEquals(2, vector[1].intValue());
        assertEquals(3, vector[2].intValue());
        assertEquals(4, vector[3].intValue());
        assertEquals(5, vector[4].intValue());
    }

    @Test
    public void testNewTensor_Vector_Long() {
        TensorShape shape = TensorShape.createShape(7);

        Tensor tensor = Tensor.newTensor(shape, new Long[] { 1L, 2L, 3L, 4L, 5L, 6L, 7L });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(7, tensor.getDim(0));
        assertEquals(7, tensor.size());

        Long[] vector = (Long[])tensor.getValue();
        assertEquals(7, vector.length);

        assertEquals(1L, vector[0].longValue());
        assertEquals(2L, vector[1].longValue());
        assertEquals(3L, vector[2].longValue());
        assertEquals(4L, vector[3].longValue());
        assertEquals(5L, vector[4].longValue());
        assertEquals(6L, vector[5].longValue());
        assertEquals(7L, vector[6].longValue());
    }

    @Test
    public void testNewTensor_Vector_Double() {
        TensorShape shape = TensorShape.createShape(2);

        Tensor tensor = Tensor.newTensor(shape, new Double[] { 1.1, 2.2 });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(2, tensor.getDim(0));
        assertEquals(2, tensor.size());

        Double[] vector = (Double[])tensor.getValue();
        assertEquals(2, vector.length);

        assertEquals(1.1, vector[0].doubleValue(), 0.0);
        assertEquals(2.2, vector[1].doubleValue(), 0.0);
    }

    @Test
    public void testNewTensor_Vector_String() {
        TensorShape shape = TensorShape.createShape(3);

        Tensor tensor = Tensor.newTensor(shape, new String[] { "V1", "V2", "V3" });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(3, tensor.getDim(0));
        assertEquals(3, tensor.size());

        String[] vector = (String[])tensor.getValue();
        assertEquals(3, vector.length);

        assertEquals("V1", vector[0]);
        assertEquals("V2", vector[1]);
        assertEquals("V3", vector[2]);
    }

    @Test
    public void testNewTensor_2D_Integer() {
        TensorShape shape = TensorShape.createShape(2, 3);
        Tensor tensor = Tensor.newTensor(shape, new Integer[] { 11, 12, 13, 21, 22, 23 });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(2, tensor.dims());
        assertEquals(2, tensor.getDim(0));
        assertEquals(3, tensor.getDim(1));
        assertEquals(6, tensor.size());

        Integer[] vector = (Integer[])tensor.getValue();
        assertEquals(6, vector.length);

        assertEquals(11, vector[0].intValue());
        assertEquals(12, vector[1].intValue());
        assertEquals(13, vector[2].intValue());
        assertEquals(21, vector[3].intValue());
        assertEquals(22, vector[4].intValue());
        assertEquals(23, vector[5].intValue());
    }

    @Test
    public void testNewTensor_2D_Long() {
        TensorShape shape = TensorShape.createShape(3, 2);
        Tensor tensor = Tensor.newTensor(shape, new Long[] { 11L, 12L, 21L, 22L, 31L, 32L });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(2, tensor.dims());
        assertEquals(3, tensor.getDim(0));
        assertEquals(2, tensor.getDim(1));
        assertEquals(6, tensor.size());

        Long[] vector = (Long[])tensor.getValue();
        assertEquals(6, vector.length);

        assertEquals(11L, vector[0].longValue());
        assertEquals(12L, vector[1].longValue());
        assertEquals(21L, vector[2].longValue());
        assertEquals(22L, vector[3].longValue());
        assertEquals(31L, vector[4].longValue());
        assertEquals(32L, vector[5].longValue());
    }

    @Test
    public void testNewTensor_2D_Double() {
        TensorShape shape = TensorShape.createShape(2, 3);
        Tensor tensor = Tensor.newTensor(shape, new Double[] { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(2, tensor.dims());
        assertEquals(2, tensor.getDim(0));
        assertEquals(3, tensor.getDim(1));
        assertEquals(6, tensor.size());

        Double[] vector = (Double[])tensor.getValue();
        assertEquals(6, vector.length);

        assertEquals(1.1, vector[0].doubleValue(), 0.0);
        assertEquals(1.2, vector[1].doubleValue(), 0.0);
        assertEquals(1.3, vector[2].doubleValue(), 0.0);
        assertEquals(2.1, vector[3].doubleValue(), 0.0);
        assertEquals(2.2, vector[4].doubleValue(), 0.0);
        assertEquals(2.3, vector[5].doubleValue(), 0.0);
    }

    @Test
    public void testNewTensor_2D_String() {
        TensorShape shape = TensorShape.createShape(3, 2);
        Tensor tensor = Tensor.newTensor(shape, new String[] { "C1R1", "C2R1", "C1R2", "C2R2", "C1R3", "C2R3" });
        assertNotNull(tensor);
        assertFalse(tensor.isScalar());

        assertEquals(2, tensor.dims());
        assertEquals(3, tensor.getDim(0));
        assertEquals(2, tensor.getDim(1));
        assertEquals(6, tensor.size());

        String[] vector = (String[])tensor.getValue();
        assertEquals(6, vector.length);

        assertEquals("C1R1", vector[0]);
        assertEquals("C2R1", vector[1]);
        assertEquals("C1R2", vector[2]);
        assertEquals("C2R2", vector[3]);
        assertEquals("C1R3", vector[4]);
        assertEquals("C2R3", vector[5]);
    }

    @Test
    public void testNewTensor_Scalar_Integer() {
        Tensor tensor = Tensor.newTensor(Integer.MAX_VALUE);
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(1, tensor.getDim(0));
        assertEquals(1, tensor.size());

        Integer scalar = (Integer)tensor.getValue();
        assertEquals(Integer.MAX_VALUE, scalar.intValue());
    }

    @Test
    public void testNewTensor_Scalar_Long() {
        Tensor tensor = Tensor.newTensor(Long.MAX_VALUE);
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(1, tensor.getDim(0));
        assertEquals(1, tensor.size());

        Long scalar = (Long)tensor.getValue();
        assertEquals(Long.MAX_VALUE, scalar.longValue());
    }

    @Test
    public void testNewTensor_Scalar_Double() {
        Tensor tensor = Tensor.newTensor(Double.MAX_VALUE);
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(1, tensor.getDim(0));
        assertEquals(1, tensor.size());

        Double scalar = (Double)tensor.getValue();
        assertEquals(Double.MAX_VALUE, scalar.doubleValue(), 0.0);
    }

    @Test
    public void testNewTensor_Scalar_String() {
        Tensor tensor = Tensor.newTensor("Hello");
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());

        assertEquals(1, tensor.dims());
        assertEquals(1, tensor.getDim(0));
        assertEquals(1, tensor.size());

        String scalar = (String)tensor.getValue();
        assertEquals("Hello", scalar);
    }

    @Test
    public void testIsSameSize_Vector() {
        TensorShape shapeA = TensorShape.createShape(5);
        Tensor tensorA = Tensor.newTensor(shapeA, new Integer[] { 1, 2, 3, 4, 5 });

        TensorShape shapeB = TensorShape.createShape(5);
        Tensor tensorB = Tensor.newTensor(shapeB, new Integer[] { 9, 8, 7, 6, 5 });

        assertTrue(tensorA.isSameSize(shapeB));
        assertTrue(tensorA.isSameSize(tensorB));
    }

    @Test
    public void testIsSameSize_2D() {
        TensorShape shapeA = TensorShape.createShape(2, 3);
        Tensor tensorA = Tensor.newTensor(shapeA, new Double[] { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 });

        TensorShape shapeB = TensorShape.createShape(2, 3);
        Tensor tensorB = Tensor.newTensor(shapeB, new Double[] { 9.1, 9.2, 9.3, 8.1, 8.2, 8.3 });

        assertTrue(tensorA.isSameSize(shapeB));
        assertTrue(tensorA.isSameSize(tensorB));
    }

    //--------------------------------------------------------------------------
    @Test
    public void testToDoubleArrayFrom_InvalidDims() {
        float[][] floatMatrix = new float[][] {
            { 1.1F, 1.2F, 1.3F },
            { 2.1F, 2.2F, 2.3F, 9.9F },
        };
        Double[] doubleArray = Tensor.toDoubleArrayFrom(floatMatrix);
        assertNull(doubleArray);
    }

    @Test
    public void testNewTensor_Vector_UnmatchShape() {
        TensorShape shape = TensorShape.createShape(1);
        Tensor tensor = Tensor.newTensor(shape, new Integer[] { 1, 2 });
        assertNull(tensor);
    }

    @Test
    public void testNewTensor_2D_UnmatchShape() {
        TensorShape shape = TensorShape.createShape(2, 3);
        Tensor tensor = Tensor.newTensor(shape, new Integer[] { 11, 12, 13, 21, 22, 23, 99 });
        assertNull(tensor);
    }

    @Test(expected = java.lang.NullPointerException.class)
    public void testToDoubleArrayFrom_arg_null() {
        Tensor.toDoubleArrayFrom(null);
    }

    @Test
    public void testNewTensor_Scalar_arg_null() {
        Tensor tensor = Tensor.newTensor(null);
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());
        assertEquals(1, tensor.dims());
        assertEquals(1, tensor.getDim(0));
        assertEquals(1, tensor.size());
        Object scalar = tensor.getValue();
        assertNull(scalar);
    }

    @Test(expected = java.lang.NullPointerException.class)
    public void testNewTensor_Tensor_arg1_null() {
        TensorShape shape = TensorShape.createShape(2, 3);
        Tensor.newTensor(shape, null);
    }

    @Test(expected = java.lang.NullPointerException.class)
    public void testNewTensor_Tensor_arg2_null() {
        Tensor.newTensor(null, new Integer[] { 11, 12, 13, 21, 22, 23, 99 });
    }

    @Test(expected = java.lang.NullPointerException.class)
    public void testIsSameSize_arg_null() {
        TensorShape shapeA = TensorShape.createShape(5);
        Tensor tensorA = Tensor.newTensor(shapeA, new Integer[] { 1, 2, 3, 4, 5 });
        Tensor tensorB = null;
        tensorA.isSameSize(tensorB);
    }

    @Test
    public void testGetDim_dim_negative() {
        TensorShape shape = TensorShape.createShape(1, 1);
        Tensor tensor = Tensor.newTensor(shape, new Double[] { 1.1 });
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());
        assertEquals(-1, tensor.getDim(-1));
    }

    @Test
    public void testGetDim_dim_tooBig() {
        TensorShape shape = TensorShape.createShape(1, 1);
        Tensor tensor = Tensor.newTensor(shape, new Double[] { 1.1 });
        assertNotNull(tensor);
        assertTrue(tensor.isScalar());
        assertEquals(-1, tensor.getDim(1));
    }
}
