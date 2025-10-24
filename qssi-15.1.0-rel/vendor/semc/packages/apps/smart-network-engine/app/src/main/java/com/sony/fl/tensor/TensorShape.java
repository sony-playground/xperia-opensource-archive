package com.sony.fl.tensor;

/**
 * TensorShapeクラスはテンソルのサイズを表します。1次元～n次元の次元毎の要素数をシェイプとして定義します。
 */
public class TensorShape
{
    private final int[] dims;

    @SuppressWarnings("unused")
    private TensorShape()
    {
        this.dims = new int[]{0};
    }

    private TensorShape(int... dims)
    {
        this.dims = dims;
    }

    /**
     * TensorShapeオブジェクトを生成します。<br>
     *
     * <pre>{@code
     *   // Generates a shape object for vector representation
     *   TensorShape shape = TensorShape.createShape(3)
     *
     *   // Generates shape objects for 2D expression
     *   TensorShape shape2D = TensorShape.createShape(16, 13)  // or createShape(new int[] {16, 13})
     * }</pre>
     *
     * @param dims テンソルの次元毎の要素数です。
     * @return 生成したTensorShapeオブジェクトを返します。要素数に 0 以下の数が指定されていると null を返します。
     */
    public static TensorShape createShape(int... dims)
    {
        for (int dim: dims) {
            if (dim <= 0) {
                return null;
            }
        }
        return new TensorShape(dims);
    }

    /**
     * 次元数を返します。
     *
     * <pre>{@code
     *   // Generates shape objects for 2D expression
     *   TensorShape shape2D = TensorShape.createShape(16, 13);
     *
     *   assertEquals(2, shape.dims()));
     * }</pre>
     *
     * @return 次元数(1～)を返します。
     */
    public int dims()
    {
        return this.dims.length;
    }

    /**
     * 次元の要素数を返します。
     *
     * <pre>{@code
     *   // Generates shape objects for 2D expression
     *   TensorShape shape2D = TensorShape.createShape(16, 13);
     *
     *   assertEquals(2, shape.dims()));
     *
     *   assertEquals(16, shape.getDim(0)));
     *   assertEquals(13, shape.getDim(1)));
     * }</pre>
     *
     * @param d 次元
     * @return 要素数(1～)を返します。指定された次元が存在しない場合や不正な場合は -1 を返します。
     */
    public int getDim(int d)
    {
        try {
            return dims[d];
        }
        catch (ArrayIndexOutOfBoundsException ex) {
            return -1;
        }
    }

    /**
     * テンソルのサイズ(シェイプ)が同じか判定します。
     *
     * <pre>{@code
     *  TensorShape shapeA = TensorShape.createShape(1, 4);    // 1 x 4 = 4
     *  TensorShape shapeB = TensorShape.createShape(2, 2);    // 2 x 2 = 4
     *
     *  assertEquals(false, shapeA.isSameSize(shapeB));
     *
     *  TensorShape shapeA = TensorShape.createShape(2, 2);    // 2 x 2 = 4
     *  TensorShape shapeB = TensorShape.createShape(2, 2);    // 2 x 2 = 4
     *
     *  assertEquals(true, shapeA.isSameSize(shapeB));
     * }</pre>
     *
     * @param other 比較対象とするTensorShapeオブジェクト
     * @return true: 一致, false: 不一致
     */
    public boolean isSameSize(TensorShape other)
    {
        if (this.dims() != other.dims()) return false;
        final int dims = this.dims();
        for (int dim = 0; dim < dims; dim++) if (this.getDim(dim) != other.getDim(dim)) return false;
        return true;
    }

    /**
     * テンソルの要素数を返します。
     *
     * @return 要素数(1～)を返します。
     */
    public int size()
    {
        int size = 1;
        final int dims = this.dims();
        for (int dim = 0; dim < dims; dim++) { size *= this.dims[dim]; }
        return size;
    }
}
