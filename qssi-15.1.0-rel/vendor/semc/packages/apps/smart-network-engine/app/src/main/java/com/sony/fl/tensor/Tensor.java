package com.sony.fl.tensor;

/**
 * Tensorクラスはテンソルを表します。テンソルは整数値、実数値、文字列から成る1次元あるいは多次元配列です。スカラー値を表すこともできます。
 * @param <T> 指定される型は {@link java.lang.Integer}, {@link java.lang.Long}, {@link java.lang.Double}, {@link java.lang.String} を想定しています。これらの型は {@link TensorMap} クラスが扱える型です。
 */
public class Tensor<T>
{
    protected final TensorShape shape;
    private final T scalar_value;
    private final T[] dimensional_value;

    private Tensor(TensorShape shape, T[] dimensional_value)
    {
        this.shape = shape;
        this.dimensional_value = dimensional_value;
        this.scalar_value = null;
    }

    /**
     * Tensorオブジェクトを生成します。<br>
     *
     * <p>Tに指定できる型は {@link java.lang.Integer}, {@link java.lang.Long}, {@link java.lang.Double} および {@link java.lang.String} です。
     * これら以外の型を指定してもTensorオブジェクトを生成できますが {@link TensorMap} クラスで処理できないため、
     * シリアライズやデシリアライズの対象外となります。
     *
     * <pre>{@code
     *   // Generates a shape object for vector representation
     *   TensorShape shape = TensorShape.createShape(2);
     *
     *   // Generates tensor objects
     *   Tensor tensor = Tensor.newTensor(shape, new Integer[] {123, 456});           // Integer[]
     *   Tensor tensor = Tensor.newTensor(shape, new Long[] {123, 456});              // Long[]
     *   Tensor tensor = Tensor.newTensor(shape, new Double[] {1.01, 2.01});          // Double[]
     *   Tensor tensor = Tensor.newTensor(shape, new String[] {"hello", "world"});    // String[]
     *
     *   // Generates shape objects for 2D expression
     *   TensorShape shape2D = TensorShape.createShape(2, 3);
     *
     *   // Generates tensor objects
     *   Tensor tensor = Tensor.newTensor(shape2D, new Double[] {
     *       1.01, 1.02, 1.03,
     *       2.01, 2.02, 2.03
     *   });
     * }</pre>
     *
     * @param <T> {@link java.lang.Integer}, {@link java.lang.Long}, {@link java.lang.Double} または {@link java.lang.String}
     * @param shape TensorShapeオブジェクトです。
     * @param dimensional_value テンソルを1次元配列に平坦化して指定します。
     * @return 生成した Tensor オブジェクトを返します。shape で指定されたサイズと dimensional_value の要素数が一致しないと null を返します。
     */
    @SuppressWarnings({"rawtypes","unchecked"})
    static public <T> Tensor newTensor(TensorShape shape, T[] dimensional_value)
    {
        if (shape.size() != dimensional_value.length) {
            return null;
        }
        if (shape.size() == 1) {
            return new Tensor(dimensional_value[0]);
        } else {
            return new Tensor(shape, dimensional_value);
        }
    }

    private Tensor(T scalar_value)
    {
        this.shape = TensorShape.createShape(1);
        this.dimensional_value = null;
        this.scalar_value = scalar_value;
    }

    /**
     * Tensorオブジェクトを生成します。<br>
     *
     * <p>Tに指定できる型は {@link java.lang.Integer}, {@link java.lang.Long}, {@link java.lang.Double} および {@link java.lang.String} です。
     * これら以外の型を指定してもTensorオブジェクトを生成できますが {@link TensorMap} クラスで処理できないため、
     * シリアライズやデシリアライズの対象外となります。
     *
     * <pre>{@code
     *   // Generates a integer scalar-valued tensor object
     *   Integer value = new Integer(123);
     *   Tensor tensor = Tensor.newTensor(value);   // or Tensor tensor = Tensor.newTensor(123);
     *
     *   // Generates a double scalar-valued tensor object
     *   Double value = new Double(0.12d);
     *   Tensor tensor = Tensor.newTensor(value);   // or Tensor tensor = Tensor.newTensor(0.12d);
     *
     *   // Generates a string scalar-valued tensor object
     *   Tensor tensor = Tensor.newTensor("hello");
     * }</pre>
     *
     * @param <T> {@link java.lang.Integer}, {@link java.lang.Long}, {@link java.lang.Double} または {@link java.lang.String}
     * @param scalar_value スカラー値
     * @return Tensorオブジェクトを返します。
     */
    @SuppressWarnings({"rawtypes","unchecked"})
    static public <T> Tensor newTensor(T scalar_value)
    {
        return new Tensor(scalar_value);
    }

    /**
     * テンソルまたはスカラー値を返します。テンソルは1次元配列に平坦化されて返されます。
     *
     * <pre>{@code
     *   // Generates a shape object for vector representation
     *   TensorShape shape = TensorShape.createShape(2);
     *
     *   // Generates tensor objects
     *   Tensor<Double[]> tensor = Tensor.newTensor(shape, new Double[] {1.01, 2.01});
     *
     *   // Gets a value from a tensor
     *   Double[] arr = tensor.getValue();
     *   assertEquals(1.01d, arr[0]);
     *   assertEquals(2.01d, arr[1]);
     *
     *   // Generates a double scalar-valued tensor object
     *   Tensor<Double> tensor = Tensor.newTensor(0.12d);
     *
     *   // Gets a value from a tensor
     *   Double val = tensor.getValue();
     *   assertEquals(0.12d, val);
     * }</pre>
     *
     * @return テンソルまたはスカラー値を返します。テンソルは1次元配列に平坦化されて返されます。どちらも本来の型ではなく Object インスタンスとして返されます。本来の型にキャストして利用してください。
     */
    @SuppressWarnings("unchecked")
    public T getValue()
    {
        if (this.dimensional_value != null)
            return (T)this.dimensional_value;
        else
            return this.scalar_value;
    }

    /**
     * スカラー値か判定します。
     *
     * <pre>{@code
     *   // Generates a shape object for vector representation
     *   TensorShape shape = TensorShape.createShape(2);
     *
     *   // Generates tensor objects
     *   Tensor tensor = Tensor.newTensor(shape, new Double[] {1.01, 2.01});
     *
     *   assertEquals(false, tensor.isScalar());    // is not Scalar
     *
     *   // Generates a double scalar-valued tensor object
     *   Tensor tensor = Tensor.newTensor(0.12d);
     *
     *   assertEquals(true, tensor.isScalar());     // is Scalar
     * }</pre>
     *
     * @return true: スカラー値、false: テンソル
     */
    public boolean isScalar()
    {
        return (this.dimensional_value == null);
    }

    /**
     * テンソルの次元数を返します
     *
     * <pre>{@code
     *   // Generates shape objects for 2D expression
     *   TensorShape shape2D = TensorShape.createShape(2, 3);
     *
     *   // Generates tensor objects
     *   Tensor tensor = Tensor.newTensor(shape2D, new Double[] {
     *       1.01, 1.02, 1.03,
     *       2.01, 2.02, 2.03
     *   });
     *
     *   assertEquals(2, tensor.dims()));
     * }</pre>
     *
     * @return テンソルの次元数(1～)を返します。スカラーの場合は 1 を返します。
     */
    public int dims()
    {
        return this.shape.dims();
    }

    /**
     * 次元の要素数を返します。
     *
     * <pre>{@code
     *   // Generates shape objects for 2D expression
     *   TensorShape shape2D = TensorShape.createShape(2, 3);
     *
     *   // Generates tensor objects
     *   Tensor tensor = Tensor.newTensor(shape2D, new Double[] {
     *       1.01, 1.02, 1.03,
     *       2.01, 2.02, 2.03
     *   });
     *
     *   assertEquals(2, tensor.dims()));
     *
     *   assertEquals(2, tensor.getDim(0)));
     *   assertEquals(3, tensor.getDim(1)));
     * }</pre>
     *
     * @param d 次元
     * @return 要素数(1～)を返します。指定された次元が存在しない場合や不正な場合は -1 を返します。
     */
    public int getDim(int d)
    {
        return this.shape.getDim(d);
    }

    /**
     * テンソルのサイズ(シェイプ)が同じか判定します。
     *
     * <pre>{@code
     *  TensorShape shapeA = TensorShape.createShape(1, 4);     // 1 x 4 = 4
     *  TensorShape shapeB = TensorShape.createShape(2, 2);     // 2 x 2 = 4
     *  Tensor tensorA = Tensor.newTensor(shapeA, new Double[] {1.01, 1.02, 1.03, 1.04});
     *  Tensor tensorB = Tensor.newTensor(shapeB, new Double[] {1.01, 1.02, 2.01, 2.02});
     *
     *  assertEquals(false, tensorA.isSameSize(tensorB));
     *
     *  TensorShape shapeA = TensorShape.createShape(2, 2);     // 2 x 2 = 4
     *  TensorShape shapeB = TensorShape.createShape(2, 2);     // 2 x 2 = 4
     *  Tensor tensorA = Tensor.newTensor(shapeA, new Double[] {1.01, 1.02, 2.01, 2.02});
     *  Tensor tensorB = Tensor.newTensor(shapeB, new Double[] {8.01, 8.02, 9.01, 9.02});
     *
     *  assertEquals(true, tensorA.isSameSize(tensorB));
     * }</pre>
     *
     * @param other 比較対象とするTensorオブジェクト
     * @return true: 一致, false: 不一致
     */
    public boolean isSameSize(Tensor<T> other)
    {
        return this.shape.isSameSize(other.shape);
    }

    /**
     * テンソルのサイズ(シェイプ)が同じか判定します。
     *
     * <pre>{@code
     *  TensorShape shapeA = TensorShape.createShape(1, 4);     // 1 x 4 = 4
     *  TensorShape shapeB = TensorShape.createShape(2, 2);     // 2 x 2 = 4
     *  Tensor tensorA = Tensor.newTensor(shapeA, new Double[] {1.01, 1.02, 1.03, 1.04});
     *
     *  assertEquals(false, tensorA.isSameSize(shapeB));
     *
     *  TensorShape shapeA = TensorShape.createShape(2, 2);     // 2 x 2 = 4
     *  TensorShape shapeB = TensorShape.createShape(2, 2);     // 2 x 2 = 4
     *  Tensor tensorA = Tensor.newTensor(shapeA, new Double[] {1.01, 1.02, 1.03, 1.04});
     *
     *  assertEquals(true, tensorA.isSameSize(shapeB));
     * }</pre>
     *
     * @param otherShape 比較対象とするTensorShapeオブジェクト
     * @return true: 一致, false: 不一致
     */
    public boolean isSameSize(TensorShape otherShape)
    {
        return this.shape.isSameSize(otherShape);
    }

    /**
     * テンソルの要素数を返します。
     *
     * @return 要素数(1～)を返します。スカラーの場合は 1 を返します。
     */
    public int size()
    {
        return this.shape.size();
    }

    /**
     * float の2次元配列を1次元配列に平坦化します。
     *
     * @param floatMatrix floatの2次元配列
     * @return 平坦化された {@link java.lang.Double} の配列を返します。
     */
    public static Double[] toDoubleArrayFrom(float[][] floatMatrix)
    {
        int width = -1;
        int length = 0;
        for (int i = 0; i < floatMatrix.length; i++) {
            if (i == 0) {
                width = floatMatrix[i].length;
            } else
            if (width != floatMatrix[i].length) {
                return null;
            }
            length += floatMatrix[i].length;
        }
        Double[] flatted = new Double[length];
        int p = 0;
        for (float[] floats : floatMatrix) {
            for (float aFloat : floats) {
                flatted[p++] = (double) aFloat;
            }
        }
        return flatted;
    }
}
