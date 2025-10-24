package com.sony.fl.json.LinearFedHLCR.results;

import com.sony.fl.json.AbstractMessage;

/**
 * 内部モデルパラメータの更新結果 (C++ → Java)
 * <p>
 * <pre>{@code
 * {
 *   "method": "UpdateInfo",
 *   "results": {
 *     "state": 111,
 *     "client": {
 *       "clusterMap": "eee"
 *     }
 *   }
 * }
 * }</pre>
 */
public class UpdateInfo extends AbstractMessage {

    /**
     * 内部モデルパラメータの更新結果
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
         * 内部パラメータ
         */
        public Client client = new Client();

        /**
         * 内部パラメータ
         */
        public static class Client {
            /**
             * クラスター・マップ (ファイル)
             */
            public String clusterMap;
        }
    }

    /**
     * メソッド名："UpdateInfo"
     */
    protected String myName() {
        return "UpdateInfo";
    }

    /**
     * 内部モデルパラメータの更新結果を生成します。
     * <p>
     * 内部モデルパラメータの更新結果を生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   UpdateInfo updateInfo = UpdateInfo.newInstance();
     *   updateInfo.results.state = ...;
     *   updateInfo.results.client.clusterMap = "...";
     * }</pre>
     * @return 内部モデルパラメータの更新結果
     */
    public static UpdateInfo newInstance() {
        return (UpdateInfo)AbstractMessage.newInstance(UpdateInfo.class);
    }
}
