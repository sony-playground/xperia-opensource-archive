package com.sony.fl.json.LinearFedHLCR.results;

import com.sony.fl.json.AbstractMessage;

/**
 * 推論(逐次)結果 (C++ → Java)
 * <p>
 * <pre>{@code
 * {
 *   "method": "Prediction",
 *   "results": {
 *     "state": 111,
 *     "application": {
 *       "predictionResult": "aaa"
 *     }
 *   }
 * }
 * }</pre>
 */
public class Prediction extends AbstractMessage {

    /**
     * 推論(逐次)結果
     */
    public Results results = new Results();

    public static class Results {
        /**
         * 結果 (0:正常 0以外:失敗、異常)
         */
        public Integer state;
        /**
         * 詳細メッセージ (state != 0 の場合のみ有効)
         */
        public String description;
        /**
         * アプリケーション・パラメータ
         */
        public Application application = new Application();

        /**
         * アプリケーション・パラメータ
         */
        public static class Application {
            /**
             * Prediction Result
             */
            public String predictionResult;
        }
    }

    /**
     * メソッド名："Prediction"
     */
    protected String myName() {
        return "Prediction";
    }

    /**
     * 評価(逐次)結果を生成します。
     * <p>
     * 評価(逐次)結果を生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   Prediction prediction = Prediction.newInstance();
     *   prediction.results.state = ...;
     *   prediction.results.application.predictionResult = "...";
     * }</pre>
     * @return 評価(逐次)結果
     */
    public static Prediction newInstance() {
        return (Prediction)AbstractMessage.newInstance(Prediction.class);
    }
}
