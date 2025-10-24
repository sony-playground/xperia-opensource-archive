package com.sony.fl.tensor;

import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.utils.PathChecker;

/**
 * DataSerializer クラスは、TensorMap オブジェクトにマッピングされている key と Tensor オブジェクトを JSON 文字列としてファイルに保存します。
 *
 * <p>DataSerializer クラスは、TensorMap オブジェクトを2つのファイルに保存します。ひとつは JSON 文字列を格納する「テンソルマップ・ファイル」です。もうひとつは JSON 文字列の 1行を取得するために利用するバイトオフセットを格納する「テンソルマップ・インデックス・ファイル」です。
 * これらのファイルの情報は「テンソルマップ・メタデータ」に保持します。
 * <table border="1">
 * <caption>テンソルマップ・メタデータに保持する情報</caption>
 * <tr><th>key</th><th>value</th><th>description</th></tr>
 * <tr><td>tensor_map_file</td><td>例) .../tensor_map.json</td><td>テンソルマップ・ファイルのパス</td></tr>
 * <tr><td>tensor_map_index_file</td><td>例) .../tensor_map.txt</td><td>テンソルマップ・インデックス・ファイルのパス</td></tr>
 * <tr><td>save_result</td><td>success<br>failed</td><td>{@link #save(TensorMap)} メソッドの実行結果: "success" または "failed"</td></tr>
 * </table>
 */
public class DataSerializer {
    private static final String DATA_FILE_KEY = "tensor_map_file";
    private static final String INDEX_FILE_KEY = "tensor_map_index_file";
    private static final String SAVE_RESULT_KEY = "save_result";
    private static final String SAVE_RESULT_VALUE_SUCCESS = "success";
    private static final String SAVE_RESULT_VALUE_FAILED = "failed";

    private final DataMetadata metadata = new DataMetadata();
    private long offset = 0;

    private DataSerializer() {
    }

    /**
     * 指定された TensorMap オブジェクトを 1行の JSON 文字列でファイルに保存します。save を実行するたびにファイルに追記します。
     *
     * <p>改行文字は System.lineSeparator() を使用します。
     *
     * <p>ファイルの保存に失敗した場合、失敗したという情報がテンソルマップ・メタデータに設定され、後続処理を実行した時に失敗していたか判定されます。後続処理で失敗していたかどうかが判定されるため、このメソッドの呼び出し後に結果を判定する必要はありません。
     *
     * @see <a href="https://json.nlohmann.me/features/parsing/json_lines/">JSON Lines</a>
     * @param tensorMap  JSON 文字列としてファイルに保存するための TensorMap オブジェクト
     * @return  ファイルの保存に成功したら this を返します。ファイルを保存する際に発生し得る例外はこのメソッド内部でキャッチしてファイルの保存に失敗したことをテンソルマップ・メタデータに保存しつつ this を返します。
     */
    public DataSerializer save(TensorMap tensorMap) {
        Path datFile = Paths.get(this.metadata.get(DataSerializer.DATA_FILE_KEY));
        Path idxFile = Paths.get(this.metadata.get(DataSerializer.INDEX_FILE_KEY));

        long newOffset = 0;
        try (FileWriter writer = new FileWriter(datFile.toString(), true)) {
            String tensorMapJson = tensorMap.toJsonString();
            String jsonLine = tensorMapJson + System.lineSeparator();
            writer.write(jsonLine);
            newOffset += jsonLine.length();
        } catch (IOException ex) {
            FLLogger.e("Caught IOException [" + ex.toString() + "][" + datFile + "]");
            this.metadata.set(DataSerializer.SAVE_RESULT_KEY, DataSerializer.SAVE_RESULT_VALUE_FAILED);
        }

        try (FileWriter writer = new FileWriter(idxFile.toString(), true)) {
            String offsetStr = String.format("%09d", this.offset);
            writer.write(offsetStr + System.lineSeparator());
            this.offset += newOffset;
        } catch (IOException ex) {
            FLLogger.e("Caught IOException [" + ex.toString() + "][" + idxFile + "]");
            this.metadata.set(DataSerializer.SAVE_RESULT_KEY, DataSerializer.SAVE_RESULT_VALUE_FAILED);
        }
        if (this.metadata.get(DataSerializer.SAVE_RESULT_KEY) == null) {
            this.metadata.set(DataSerializer.SAVE_RESULT_KEY, DataSerializer.SAVE_RESULT_VALUE_SUCCESS);
        }
        return this;
    }

    /**
     * テンソルマップ・メタデータを返します。
     *
     * <p>テンソルマップ・メタデータには保存したファイルのパス情報や保存結果などが格納されています。このメソッドで取得したテンソルマップ・メタデータは後続処理に渡すために利用します。
     *
     * @return  テンソルマップ・メタデータを返します
     */
    public DataMetadata getMetadata() {
        return this.metadata;
    }

    /**
     * DataSerializer インスタンスを生成します。
     *
     * <p>指定されたテンソルマップ・ファイルとテンソルマップ・インデックス・ファイルは、テンソルマップ・メタデータとして DataSerializer インスタンスに保持します。
     *
     * <p>第一引数 dataFile にはテンソルマップ・ファイルのパスを指定します。テンソルマップ・ファイルは 1 行がひとつの TensorMap オブジェクトの JSON 文字列になっています。つまり、テンソルマップ・ファイルには複数の TensorMap を JSON 文字列で格納できることになります。
     * <p>第二引数 indexFile にはテンソルマップ・インデックス・ファイルのパスを指定します。テンソルマップ・インデックス・ファイルには、特定の TensorMap の JSON 文字列の 1行を取得するために利用するバイトオフセットを表すゼロパディングされた 9 桁の数値が格納されます。テンソルマップ・インデックス・ファイルに保存された各行のバイトオフセットは、テンソルマップ・ファイルの各行と対応関係にあります。
     * <p>テンソルマップ・ファイルには、最大で 50 MB 程度まで保存されることを想定しています。TensorMap の JSON 文字列の 1 行が最大 5,000 bytes あり、10,000 行まで記録される想定です。
     * ただし、バイトオフセットは 9 桁まで用意してあるため、実際にはテンソルマップ・ファイルは 1 GB 程度まで保存できます。
     *
     * <p>テンソルマップ・ファイルの例です。
     * <pre>{@code
     * {"num_of_features":{"shape":[1],"value":[13]},"x":{"shape":[16,13],"value":[0.857794,...,1.0,1.0,0.0]},"groupLabel":{"shape":[1],"value":["1"]},"y":{"shape":[1],"value":[1]}}
     * {"num_of_features":{"shape":[1],"value":[13]},"x":{"shape":[16,13],"value":[0.632478,...,1.0,1.0,0.0]},"groupLabel":{"shape":[1],"value":["1"]},"y":{"shape":[1],"value":[0]}}
     * ...
     * {"num_of_features":{"shape":[1],"value":[13]},"x":{"shape":[16,13],"value":[0.218375,...,1.0,1.0,0.0]},"groupLabel":{"shape":[1],"value":["1"]},"y":{"shape":[1],"value":[0]}}
     * }</pre>
     * <p>テンソルマップ・インデックス・ファイルの例です。
     * <pre>{@code
     * 000000000
     * 000000150
     * ...
     * 000001500
     * }</pre>
     * @param dataFile  テンソルマップ・ファイルのパス
     * @param indexFile  テンソルマップ・インデックス・ファイルのパス
     * @return  DataSerializer のインスタンスを返します
     * @throws FLException dataFile もしくは indexFile で指定されたファイルがすでに存在する、dataFile もしくは indexFile にディレクトリが指定された、dataFile と indexFile に同じファイルが指定された、または dataFile もしくは indexFile が格納されるディレクトリのアクセス権（読み込み、書き込み、実行のいずれか）が無い場合にスローします。
     */
    public static DataSerializer createFor(Path dataFile, Path indexFile) throws FLException {
        if (dataFile.toString().isEmpty() || indexFile.toString().isEmpty()) {
            FLLogger.e("dataFile \"" + dataFile + "\"" + " or " + "indexFile \"" + indexFile + "\"" + " is empty.");
            throw new FLException("Input path is empty.");
        }

        Path datAbsolutePath = dataFile.toAbsolutePath();
        Path idxAbsolutePath = indexFile.toAbsolutePath();
        if (Files.exists(datAbsolutePath) || Files.exists(idxAbsolutePath)) {
            FLLogger.e("dataFile \"" + dataFile + "\"" + " or " + "indexFile \"" + indexFile + "\"" + " already exists.");
            throw new FLException("Input path exists. [" + datAbsolutePath + "][" + idxAbsolutePath + "]");
        }
        if (datAbsolutePath.equals(idxAbsolutePath)) {
            FLLogger.e("dataFile \"" + dataFile + "\"" + " and " + "indexFile \"" + dataFile + "\"" + " are the same path.");
            throw new FLException("Input paths are the same. [" + datAbsolutePath + "][" + idxAbsolutePath + "]");
        }

        Path datParent = datAbsolutePath.getParent();
        Path idxParent = idxAbsolutePath.getParent();
        if (!PathChecker.checkFolderPath(datParent, true, true, true)) {
            FLLogger.e("\"" + datParent.toString() + "\" does not have read, write, or execute permissions.");
            throw new FLException("Permission denied on parent directory of TensorMap file. [" + datParent + "]");
        }
        if (!PathChecker.checkFolderPath(idxParent, true, true, true)) {
            FLLogger.e("\"" + idxParent.toString() + "\" does not have read, write, or execute permissions.");
            throw new FLException("Permission denied on parent directory of TensorMapIndex file. [" + idxParent + "]");
        }

        try {
            if (datAbsolutePath.toFile().createNewFile()) {
                FLLogger.d(datAbsolutePath + " is newly created.");
            }
        } catch (IOException ex) {
            FLLogger.e("Caught IOException [" + ex.toString() + "][" + datAbsolutePath + "]");
            throw new FLException("TensorMap file generation failed. [" + datAbsolutePath + "]");
        }

        try {
            if (idxAbsolutePath.toFile().createNewFile()) {
                FLLogger.d(idxAbsolutePath + " is newly created.");
            }
        } catch (IOException ex) {
            FLLogger.e("Caught IOException [" + ex.toString() + "][" + idxAbsolutePath + "]");
            throw new FLException("TensorMapIndex file generation failed. [" + idxAbsolutePath + "]");
        }

        DataSerializer dataSerializer = new DataSerializer();
        dataSerializer.metadata.set(DataSerializer.DATA_FILE_KEY, datAbsolutePath.toString());
        dataSerializer.metadata.set(DataSerializer.INDEX_FILE_KEY, idxAbsolutePath.toString());
        return dataSerializer;
    }

    /**
     * DataSerializer の {@link #save save} の結果を判定します。
     *
     * <p> {@link #save save} に成功している場合 true を返します。{@link #save save} に失敗している場合、または {@link #save save} が呼び出されていなかった場合に false を返します。
     * @param metaData  テンソルマップ・メタデータ
     * @return  {@link #save save} に成功している場合 true を返します。{@link #save save} に失敗している場合、または {@link #save save} が呼び出されていなかった場合に false を返します。
     */
    public static boolean wasSuccess(DataMetadata metaData) {
        String save_result = metaData.get(DataSerializer.SAVE_RESULT_KEY);
        if (save_result == null) {
            return false;
        }
        return save_result.equals(DataSerializer.SAVE_RESULT_VALUE_SUCCESS);
    }

    /**
     * DataSerializer の {@link #save save} が呼び出されていたか判定します。 {@link #save save} の結果は関知せず、呼び出されていたかだけを判定します。結果を判定する場合は {@link #wasSuccess wasSuccess} を利用してください。
     *
     * <p> {@link #save save} が呼び出されていた場合 true を返します。{@link #save save} が呼び出されていなかった場合は false を返します。
     * @param metaData  テンソルマップ・メタデータ
     * @return  {@link #save save} が呼び出されていた場合 true を返します。{@link #save save} が呼び出されていなかった場合は false を返します。
     */
    public static boolean wasSaved(DataMetadata metaData) {
        String save_result = metaData.get(DataSerializer.SAVE_RESULT_KEY);
        return (save_result != null);
    }
}

