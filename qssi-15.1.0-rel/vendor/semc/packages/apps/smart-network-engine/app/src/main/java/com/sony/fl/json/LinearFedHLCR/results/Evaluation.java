package com.sony.fl.json.LinearFedHLCR.results;

import com.sony.fl.json.AbstractMessage;

/**
 * 評価結果 (C++ → Java)
 * <p>
 * <pre>{@code
 * {
 *   "method": "Evaluation",
 *   "results": {
 *     "state": 111,
 *     "server": {
 *       "evaluationResult": "aaa"
 *     }
 *   }
 * }
 * }</pre>
 */
public class Evaluation extends AbstractMessage {

    /**
     * 評価結果
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
         * 外部パラメータ
         */
        public Server server = new Server();

        /**
         * 外部パラメータ
         */
        public static class Server {
            /**
             * Evaluation Result
             */
            public String evaluationResult;
        }
    }

    /**
     * メソッド名："Evaluation"
     */
    protected String myName() {
        return "Evaluation";
    }

    /**
     * 評価結果を生成します。
     * <p>
     * 評価結果を生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   Evaluation evaluation = Evaluation.newInstance();
     *   evaluation.results.state = ...;
     *   evaluation.results.server.evaluationResult = "...";
     * }</pre>
     * @return 評価結果
     */
    public static Evaluation newInstance() {
        return (Evaluation)AbstractMessage.newInstance(Evaluation.class);
    }
}
