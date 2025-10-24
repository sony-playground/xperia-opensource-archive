package com.sony.fl.json.LinearFedHLCR.parameters;

import com.sony.fl.json.AbstractMessage;

/**
 * 評価 (Java → C++)
 * <p>
 * <pre>{@code
 * {
 *   "method": "Evaluation",
 *   "parameters": {
 *     "server": {
 *       "output": "..."
 *     },
 *     "client": {
 *       "dataSet": "..."
 *     }
 *   }
 * }
 * }</pre>
 */
public class Evaluation extends AbstractMessage {

    /**
     * デフォルト・コンストラクタ
     * <p>
     * Evaluation.newInstance() でインスタンスを生成するほうが便利です。コンストラクタで生成した場合はメンバ変数を初期化する必要があります。
     */
    public Evaluation() {}

    public Parameters parameters = new Parameters();

    public static class Parameters {
        public final Server server = new Server();
        public final Client client = new Client();

        public static class Server {
            /**
             * 実行結果の保存先 (サーバ返答用)
             */
            public String output;
        }

        public static class Client {
            /**
             * 評価用データセット (DataMetadataをシリアライズしてJSON文字列にして格納)
             */
            public String dataSet;
        }
    }

    /**
     * メソッド名："Evaluation"
     */
    protected String myName() {
        return "Evaluation";
    }

    /**
     * 評価パラメータを生成します。
     * <p>
     * 評価パラメータを生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   Evaluation evaluation = Evaluation.newInstance();
     *   evaluation.parameters.server.output = "...";
     *   evaluation.parameters.client.dataSet = "...";
     * }</pre>
     * @return 評価パラメータ
     */
    public static Evaluation newInstance() {
        return (Evaluation)AbstractMessage.newInstance(Evaluation.class);
    }
}
