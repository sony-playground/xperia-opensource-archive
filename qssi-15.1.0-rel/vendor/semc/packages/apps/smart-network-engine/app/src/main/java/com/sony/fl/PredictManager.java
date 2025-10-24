package com.sony.fl;
import java.nio.file.Files;
/**
 * @author Masanobu Jimbo
 */
import java.nio.file.Path;
import java.nio.file.Paths;

import com.google.protobuf.InvalidProtocolBufferException;
import com.sony.fl.algorithm.*;
import com.sony.fl.db.DBFactory;
import com.sony.fl.db.DBForPredictManager;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.*;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;
import com.sony.fl.utils.PathChecker;

public class PredictManager {
    private final DBForPredictManager mDatabase;
    private final Path mRoot;
    private final String mAppID;
    private final FLClient mClient;
    private final TaskInfo.PBDeployInfo mDeployInfo;
    private final Path mDeployPath;

    public PredictManager(Path dirPath, String appID) throws FLException {
        mRoot = dirPath;
        if (!PathChecker.checkFolderPath(dirPath, true, true, true)) {
            FLLogger.e(dirPath.toString() + " is an invalid path.");
            throw new FLException("Creating TrainManager was failed due to invalid input.");
        }
        mAppID = appID;
        try {
            mDatabase = new DBForPredictManager((DBFactory)Class.forName(
                    Configuration.DB_FACTORY_FQCN).newInstance(), mRoot);
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            FLLogger.e(e.toString());
            throw new FLException("Invalid DB type.");
        }
        String deployPathStr = mDatabase.searchForBackUpPathFromDB(mAppID);
        Path deployPath = null;
        if (deployPathStr != null) {
            deployPath= Paths.get(deployPathStr);
            if (!Files.exists(deployPath)) {
                FLLogger.e(deployPath + "is not found.");
                deployPath = null;
            }
        }
        mDeployPath = deployPath;
        TaskInfo.PBDeployInfo deployInfo = null;
        try {
            deployInfo =  TaskInfo.PBDeployInfo.parseFrom(mDatabase.searchForModelInfoFromDB(mAppID));
        } catch (InvalidProtocolBufferException e) {
            FLLogger.w(e.toString());
        } catch (NullPointerException e) {
            FLLogger.w(e.toString());
        }
        mDeployInfo = deployInfo;
        if (mDeployPath != null && mDeployInfo != null) {
            switch(mDeployInfo.getModelType()) {
                case LinerHLCR:
                    mClient = new LinearFedHLCRClient(mDeployInfo.getLinearHLCRGlobalModel(), 
                            mDeployPath, mDeployPath);
                    break;
                case NNHLCR:
                    mClient = new NNFedHLCRClient(mDeployInfo.getNNHLCRModel(), 
                            mDeployPath, mDeployPath);
                    break;
                default:
                    mClient = null;
                    throw new FLException("Creating PredictManager was failed due to invalid model type.");
            }
        } else {
            FLLogger.w(appID + " has no deployed model.");
            mClient = null;
        }
    }

    /**
     * 推論を行う
     *
     * <pre>{@code
     *   // PredictManager オブジェクトを生成する
     *   PredictManager manager = new PredictManager(Paths.get(...), "appID");
     *
     *   // テンソル・マップに `フィーチャー数`, `シーケンス・データ`, `グループ・ラベル` テンソルを格納する
     *   TensorMap tensorMap = TensorMap.newInstance();
     *   tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(13));
     *   tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.getShape(16, 13), new Double[] {
     *       0.857794,1.069542,1.876248,0.666642,0.646275,1.349414,1.041156,1.259321,0.018650,1.045818,1.0,1.0,0.0,
     *       1.053484,0.926854,1.662627,1.137241,1.529959,1.055488,0.637683,0.947744,1.864815,0.020755,1.0,1.0,0.0,
     *       1.490171,0.174854,1.954317,0.284297,1.664206,0.452631,1.755731,0.500042,0.429072,0.513032,1.0,1.0,0.0,
     *       1.721924,0.097231,0.876755,0.682838,0.834283,1.556183,0.504749,1.015972,1.400632,0.275577,1.0,1.0,0.0,
     *       1.862259,0.390042,0.844716,1.076349,0.841206,0.066427,1.697208,0.465949,1.430360,0.489663,1.0,1.0,0.0,
     *       1.755041,0.884185,1.214192,1.157967,0.219609,1.491656,1.796584,1.717885,0.139920,0.947506,1.0,1.0,0.0,
     *       0.138756,1.032719,1.737744,0.546040,1.964188,1.098520,1.600144,1.406094,1.491822,0.504435,1.0,1.0,0.0,
     *       1.898207,1.858959,0.110164,0.875559,0.024409,0.367739,1.852587,0.755329,0.126964,1.147889,1.0,1.0,0.0,
     *       0.374914,1.564331,1.218059,1.877848,0.209167,1.458295,0.152921,0.589017,1.610823,1.843708,1.0,1.0,0.0,
     *       0.113296,1.321201,0.352085,1.989424,0.106816,0.526028,0.535334,1.525832,1.030717,0.778521,1.0,1.0,0.0,
     *       0.325969,0.345854,0.144434,0.358698,1.176167,0.985261,1.045117,1.732317,1.301922,0.913824,1.0,1.0,0.0,
     *       0.299956,1.607262,0.542610,1.686827,1.133771,0.964085,0.498744,1.916791,0.593930,1.784905,1.0,1.0,0.0,
     *       1.050038,0.414032,0.805368,1.731645,1.238555,1.284437,0.659694,1.654002,0.559588,1.329483,1.0,1.0,0.0,
     *       1.576912,1.812203,0.378607,1.139914,1.428911,0.606778,0.601802,1.620971,0.485459,0.095943,1.0,1.0,0.0,
     *       0.348698,1.280218,0.158756,0.999035,1.120368,1.525332,0.221014,1.650828,0.424302,0.909746,1.0,1.0,0.0,
     *       1.927778,0.980503,0.789579,1.939464,1.991026,0.654966,0.116232,0.300867,1.694313,1.203679,1.0,1.0,0.0
     *   }));
     *   tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor("1"));
     *
     *   // テンソル・マップに格納された `フィーチャー数`, `シーケンス・データ`, `グループ・ラベル` テンソルに基づいて推論する
     *   PredictResult result = manager.predict(tensorMap);
     *   });
     * }</pre>
     *
     * @param input テンソル・マップ
     * @return 推論結果
     */
    public PredictResult predict(TensorMap input) {
        TensorMap ret = null;
        String key = "";
        if (mDeployInfo == null || mDeployPath == null) {
            FLLogger.w("There is no deployed model");
            return new PredictResult(3);
        }
        if (input == null) {
            FLLogger.w("There is no meta-data");
            return new PredictResult(1);
        }
        if (input.get(NNFedHLCRClient.TENSOR_GROUP_LABEL) == null) {
            input.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(TensorShape.createShape(1), new String[] {""}));
        }
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.w("This task could not be started because another task is running.");
                return new PredictResult(2);
            }
            ret = _predict(input);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        if (ret == null) {
            FLLogger.e("predict result is invalid.");
            return new PredictResult(1, ret);
        }
        return new PredictResult(0, ret);
    }

    private TensorMap _predict(TensorMap input) {
        return mClient.predict(input);
    }

    /**
     * Cluster Mappingの更新を行う
     *
     * <pre>{@code
     *   // PredictManager オブジェクトを生成する
     *   PredictManager manager = new PredictManager(Paths.get(...), "appID");
     *
     *   // テンソル・マップに `x` テンソルや `グループ・ラベル` などの Cluster Mapping の更新に必要なテンソルを格納する
     *   DataSerializer dataSerializer = DataSerializer.createFor(Paths.get(...), Paths.get(...));
     *   for (x: [...]) {
     *       String groupLabel = ...;
     *       int y = ...;
     *       float[][] x = ...;
     *       int m = x.length;
     *       int n = x[0].length;;
     *       TensorMap tensorMap = TensorMap.newInstance();
     *       tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_Y, Tensor.newTensor(y));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.getShape(m, n), Tensor.toDoubleArrayFrom(x)));
     *       // NOTE:
     *       // - ファイルへの保存に失敗すると、後続の PredictManager#calibrate() において失敗したことを検出してエラーが応答される
     *       dataSerializer.save(tensorMap);
     *   }
     *   DataMetadata metaData = dataSerializer.getMetadata();
     *
     *   // テンソル・マップに格納された `フィーチャー数`, `シーケンス・データ`, `グループ・ラベル` テンソルに基づいて Cluster Mapping を更新する
     *   int result = manager.calibrate(metaData);
     * }</pre>
     *
     * @param metaData テンソルマップ・メタデータ
     * @return 結果
     */
    public int calibrate(DataMetadata metaData) {
        String key = "";
        int ret = 1;
        if (mDeployInfo == null || mDeployPath == null || mClient == null) {
            FLLogger.w("There is no deployed model");
            return 3;
        }
        if (metaData == null) {
            FLLogger.w("There is no meta-data");
            return 3;
        }
        if (!DataSerializer.wasSaved(metaData)) {
            FLLogger.d("TensorMap file is not saved.");
            return 0;
        }
        if (!DataSerializer.wasSuccess(metaData)) {
            FLLogger.w("Failed to create TensorMap File.");
            return 1;
        }
        if (!(mClient instanceof FedHLCRClient)) {
            FLLogger.w("This algorithm dose not support calibrate.");
            return 1;
        }
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.w("This task could not be started because another task is running.");
                return 2;
            }
            ret = _calibrate(metaData);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        return ret;
    }

    private int _calibrate(DataMetadata metaData) {
        return ((FedHLCRClient)mClient).updateClusterMapping(mDeployInfo, metaData, 
                mDeployPath, mDeployPath, mDeployPath);
    }

    public void finalize() {
        if (mClient != null) {
            mClient.finalize();
        }
    }

    public static class PredictResult {
        private final int status;
        private final TensorMap result;

        private PredictResult(int status) {
            this.status = status;
            this.result = null;
        }

        private PredictResult(int status, TensorMap result) {
            this.status = status;
            this.result = result;
        }

        /**
         * ステータス・コードを返します。
         *
         * @return ステータス・コード (0, 1, 2, 3)<br>
         * <ul>
         *   <li>0: 正常</li>
         *   <li>1: 何らかの問題が発生した場合
         *     <ul>
         *       <li>引数のフォルダパスが仕様を満たしていない</li>
         *       <li>DB操作に失敗</li>
         *       <li>コア部分でのエラー</li>
         *       <li>など</li>
         *     </ul></li>
         *   <li>2: タスクの競合</li>
         *   <li>3: モデルがデプロイされていない</li>
         * </ul>
         */
        public int getStatus() {
            return status;
        }

        /**
         * 推論結果を返します。
         *
         * <pre>{@code
         *   PredictResult result = predictManager.predict(input);
         *   TensorMap output = result.getResult();
         *   Double predictLabel = (Double)tensorMap.get(NNFedHLCRClient.TENSOR_Y_PRED).getValue();
         *   System.out.printf("predictLabel %f%n", predictLabel);
         * }</pre>
         *
         * @return 推論結果(テンソル・マップ)を返します。ステータス・コードが 0 以外のときは null を返します。
         */
        public TensorMap getResult() {
            return this.result;
        }
    }
}
