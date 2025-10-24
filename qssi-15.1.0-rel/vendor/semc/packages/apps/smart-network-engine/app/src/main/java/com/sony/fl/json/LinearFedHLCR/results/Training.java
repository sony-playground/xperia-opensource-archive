package com.sony.fl.json.LinearFedHLCR.results;

import java.util.ArrayList;
import java.util.List;

import com.sony.fl.json.AbstractMessage;

/**
 * 学習結果 (C++ → Java)
 * <p>
 * <pre>{@code
 * {
 *   "method": "Training",
 *   "results": {
 *     "state": 111,
 *     "server": {
 *       "linearModels": [
 *         "aaa",
 *         "bbb"
 *       ],
 *       "localCount": "ccc",
 *       "validationMetrix": "ddd"
 *     },
 *     "client": {
 *       "clusterMap": "eee"
 *     }
 *   }
 * }
 * }</pre>
 */
public class Training extends AbstractMessage {

    /**
     * 学習結果
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
         * 内部パラメータ
         */
        public Client client = new Client();

        /**
         * 外部パラメータ
         */
        public static class Server {
            /**
             * 更新済みモデルの重み or 学習処理の中間生成値 x クラスター個
             */
            public List<String> linearModels = new ArrayList<>();
            /**
             * local count
             */
            public String localCount;
            /**
             * validation metrix
             */
            public String validationMetrix;
        }

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
     * メソッド名："Training"
     */
    protected String myName() {
        return "Training";
    }

    /**
     * 学習結果を生成します。
     * <p>
     * 学習結果を生成して各パラメータに値を格納してください。
     * <pre>{@code
     *   Training training = Training.newInstance();
     *   training.results.state = ...;
     *   training.results.server.linearModels.add("...");
     *   training.results.server.linearModels.add("...");
     *   training.results.server.localCount = "...";
     *   training.results.server.validationMetrix = "...";
     *   training.results.client.clusterMap = "...";
     * }</pre>
     * @return 学習結果
     */
    public static Training newInstance() {
        return (Training)AbstractMessage.newInstance(Training.class);
    }
}
