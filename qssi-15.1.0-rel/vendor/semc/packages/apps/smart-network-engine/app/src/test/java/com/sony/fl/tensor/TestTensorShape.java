package com.sony.fl.tensor;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class TestTensorShape {
    @Test
    public void testCreateShape_Vector() {
        TensorShape tensorShape = TensorShape.createShape(3);
        assertNotNull(tensorShape);
    }

    @Test
    public void testCreateShape_2D() {
        TensorShape tensorShape = TensorShape.createShape(2, 3);
        assertNotNull(tensorShape);
    }

    @Test
    public void testCreateShape_3D() {
        TensorShape tensorShape = TensorShape.createShape(2, 3, 4);
        assertNotNull(tensorShape);
    }

    @Test
    public void testDims_Vector() {
        TensorShape tensorShape = TensorShape.createShape(3);
        assertNotNull(tensorShape);
        assertEquals(1, tensorShape.dims());
    }

    @Test
    public void testDims_2D() {
        TensorShape tensorShape = TensorShape.createShape(2, 3);
        assertNotNull(tensorShape);
        assertEquals(2, tensorShape.dims());
    }

    @Test
    public void testDims_3D() {
        TensorShape tensorShape = TensorShape.createShape(2, 3, 4);
        assertNotNull(tensorShape);
        assertEquals(3, tensorShape.dims());
    }

    @Test
    public void testGetDim_2D() {
        TensorShape tensorShape = TensorShape.createShape(2, 3);
        assertNotNull(tensorShape);
        assertEquals(2, tensorShape.dims());
        assertEquals(2, tensorShape.getDim(0));
        assertEquals(3, tensorShape.getDim(1));
    }

    @Test
    public void testGetDim_3D() {
        TensorShape tensorShape = TensorShape.createShape(2, 3, 4);
        assertNotNull(tensorShape);
        assertEquals(3, tensorShape.dims());
        assertEquals(2, tensorShape.getDim(0));
        assertEquals(3, tensorShape.getDim(1));
        assertEquals(4, tensorShape.getDim(2));
    }

    @Test
    public void testIsSameSize_2D() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3);
        TensorShape tensorShapeB = TensorShape.createShape(2, 3);
        assertTrue(tensorShapeA.isSameSize(tensorShapeB));
    }

    @Test
    public void testIsSameSize_3D() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3, 4);
        TensorShape tensorShapeB = TensorShape.createShape(2, 3, 4);
        assertTrue(tensorShapeA.isSameSize(tensorShapeB));
    }

    @Test
    public void testIsNotSameSize_2D_1() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3);
        TensorShape tensorShapeB = TensorShape.createShape(3, 2);
        assertFalse(tensorShapeA.isSameSize(tensorShapeB));
    }

    @Test
    public void testIsNotSameSize_2D_2() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3);
        TensorShape tensorShapeB = TensorShape.createShape(2, 3, 4);
        assertFalse(tensorShapeA.isSameSize(tensorShapeB));
    }

    @Test
    public void testIsNotSameSize_3D_1() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3, 4);
        TensorShape tensorShapeB = TensorShape.createShape(4, 3, 2);
        assertFalse(tensorShapeA.isSameSize(tensorShapeB));
    }

    @Test
    public void testIsNotSameSize_3D_2() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3, 4);
        TensorShape tensorShapeB = TensorShape.createShape(2, 3);
        assertFalse(tensorShapeA.isSameSize(tensorShapeB));
    }

    //--------------------------------------------------------------------------
    @Test
    public void testCreateShape_vector_dim_zero() {
        TensorShape tensorShape = TensorShape.createShape(0);
        assertNull(tensorShape);
    }

    @Test
    public void testCreateShape_vector_dim_negative() {
        TensorShape tensorShape = TensorShape.createShape(-1);
        assertNull(tensorShape);
    }

    @Test
    public void testCreateShape_2D_dim_zero() {
        TensorShape tensorShape = TensorShape.createShape(0, 2);
        assertNull(tensorShape);
    }

    @Test
    public void testCreateShape_2D_dim_negative() {
        TensorShape tensorShape = TensorShape.createShape(-1, 2);
        assertNull(tensorShape);
    }

    @Test
    public void testGetDim_dim_negative() {
        TensorShape tensorShape = TensorShape.createShape(2, 3);
        assertNotNull(tensorShape);
        assertEquals(-1, tensorShape.getDim(-1));
    }

    @Test
    public void testGetDim_dim_tooBig() {
        TensorShape tensorShape = TensorShape.createShape(2, 3);
        assertNotNull(tensorShape);
        assertEquals(-1, tensorShape.getDim(2));
    }

    @Test(expected = java.lang.NullPointerException.class)
    public void testIsSameSize_arg_null() {
        TensorShape tensorShapeA = TensorShape.createShape(2, 3);
        tensorShapeA.isSameSize(null);
    }
}
