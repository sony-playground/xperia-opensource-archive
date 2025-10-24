package com.sony.fl.json.LinearFedHLCR.parameters;

import com.sony.fl.json.AbstractMessage;

/**
 * 学習 (Java → C++)
 * <p>
 * <pre>{@code
 * {
 *   "method": "Training",
 *   "parameters": {
 *     "server": {
 *       "hyperParams": "...",
 *       "output": "..."
 *     },
 *     "client": {
 *       "dataSet": "...",
 *       "output": "..."
 *     }
 *   }
 * }
 * }</pre>
 */
public class Training extends AbstractMessage {

    /**
     * デフォルト・コンストラクタ
     * <p>
     * Training.newInstance() でインスタンスを生成するほうが便利です。コンストラクタで生成した場合はメンバ変数を初期化する必要があります。
     */
    public Training() {}

    public Parameters parameters = new Parameters();

    public static class Parameters {
        public final Server server = new Server();
        public final Client client = new Client();

        public static class Server {
            /**
             * 学習用ハイパーパラメータ (ファイル)
             */
            public String hyperParams;

            /**
             * 実行結果の保存先 (サーバ返答用)
             */
            public String output;
        }

        public static class Client {
            /**
             * 学習用データセット (DataMetadataをシリアライズしてJSON文字列にして格納)
             */
            public String dataSet;

            /**
             * 実行結果の保存先 (内部モデルパラメータ用)
             */
            public String output;
        }
    }

    /**
     * メソッド名："Training"
     */
    protected String myName() {
        return "Training";
    }

    /**
     * 学習パラメータを生成します。
     * <p>
     * 学習パラメータを生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   Training training = Training.newInstance();
     *   training.parameters.server.hyperParams = "...";
     *   training.parameters.server.output = "...";
     *   training.parameters.client.dataSet = "...";
     *   training.parameters.client.output = "...";
     * }</pre>
     * @return 学習パラメータ
     */
    public static Training newInstance() {
        return (Training)AbstractMessage.newInstance(Training.class);
    }
}
