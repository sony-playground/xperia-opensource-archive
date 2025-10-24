package com.sony.fl.json.LinearFedHLCR.parameters;

import com.sony.fl.json.AbstractMessage;

/**
 * 内部モデルパラメータの更新 (Java → C++)
 * <p>
 * <pre>{@code
 * {
 *   "method": "UpdateInfo",
 *   "parameters": {
 *     "server": {
 *       "hyperParams": "..."
 *     },
 *     "client": {
 *       "dataSet": "...",
 *       "output": "..."
 *     }
 *   }
 * }
 * }</pre>
 */
public class UpdateInfo extends AbstractMessage {

    /**
     * デフォルト・コンストラクタ
     * <p>
     * UpdateInfo.newInstance() でインスタンスを生成するほうが便利です。コンストラクタで生成した場合はメンバ変数を初期化する必要があります。
     */
    public UpdateInfo() {}

    public Parameters parameters = new Parameters();

    public static class Parameters {
        public final Server server = new Server();
        public final Client client = new Client();

        public static class Server {
            /**
             * 更新用ハイパーパラメータ (ファイル)
             */
            public String hyperParams;
        }

        public static class Client {
            /**
             * 更新用データセット (DataMetadataをシリアライズしてJSON文字列にして格納)
             */
            public String dataSet;

            /**
             * 実行結果の保存先 (サーバ返答用、内部モデルパラメータ用)
             */
            public String output;
        }
    }

    /**
     * メソッド名："UpdateInfo"
     */
    protected String myName() {
        return "UpdateInfo";
    }

    /**
     * 内部モデルパラメータの更新パラメータを生成します。
     * <p>
     * 内部モデルパラメータの更新パラメータを生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   UpdateInfo updateInfo = UpdateInfo.newInstance();
     *   updateInfo.parameters.server.hyperParams = "...";
     *   updateInfo.parameters.client.dataSet = "...";
     *   updateInfo.parameters.client.output = "...";
     * }</pre>
     * @return 内部モデルパラメータの更新パラメータ
     */
    public static UpdateInfo newInstance() {
        return (UpdateInfo)AbstractMessage.newInstance(UpdateInfo.class);
    }
}
