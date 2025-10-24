package com.sony.fl.json.LinearFedHLCR.parameters;

import com.sony.fl.json.AbstractMessage;

/**
 * 推論(逐次) (Java → C++)
 * <p>
 * <pre>{@code
 * {
 *   "method": "Prediction",
 *   "parameters": {
 *     "application": {
 *       "data": "...",
 *     }
 *   }
 * }
 * }</pre>
 */
public class Prediction extends AbstractMessage {

    /**
     * デフォルト・コンストラクタ
     * <p>
     * Prediction.newInstance() でインスタンスを生成するほうが便利です。コンストラクタで生成した場合はメンバ変数を初期化する必要があります。
     */
    public Prediction() {}

    public Parameters parameters = new Parameters();

    public static class Parameters {
        public final Application application = new Application();

        public static class Application {
            /**
             * データ (TensorMapをシリアライズしてJSON文字列にして格納)
             */
            public String data;
        }
    }

    /**
     * メソッド名："Prediction"
     */
    protected String myName() {
        return "Prediction";
    }

    /**
     * 推論(逐次)パラメータを生成します。
     * <p>
     * 推論(逐次)パラメータを生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   Prediction prediction = Prediction.newInstance();
     *   prediction.parameters.application.data = "...";
     * }</pre>
     * @return 推論(逐次)パラメータ
     */
    public static Prediction newInstance() {
        return (Prediction)AbstractMessage.newInstance(Prediction.class);
    }
}
