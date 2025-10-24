package com.sony.fl.tensor;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import com.sony.fl.exception.FLException;

public class TestDataSerializer {
    public static final Path INPUT_PATH = Paths.get("src/test/resources/input");
    public static final String TENSOR_MAP_JSON_STRING = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [16, 13], \"value\": [0.857794, 1.069542, 1.876248, 0.666642, 0.646275, 1.349414, 1.041156, 1.259321, 0.01865, 1.045818, 1.0, 1.0, 0.0, 1.053484, 0.926854, 1.662627, 1.137241, 1.529959, 1.055488, 0.637683, 0.947744, 1.864815, 0.020755, 1.0, 1.0, 0.0, 1.490171, 0.174854, 1.954317, 0.284297, 1.664206, 0.452631, 1.755731, 0.500042, 0.429072, 0.513032, 1.0, 1.0, 0.0, 1.721924, 0.097231, 0.876755, 0.682838, 0.834283, 1.556183, 0.504749, 1.015972, 1.400632, 0.275577, 1.0, 1.0, 0.0, 1.862259, 0.390042, 0.844716, 1.076349, 0.841206, 0.066427, 1.697208, 0.465949, 1.43036, 0.489663, 1.0, 1.0, 0.0, 1.755041, 0.884185, 1.214192, 1.157967, 0.219609, 1.491656, 1.796584, 1.717885, 0.13992, 0.947506, 1.0, 1.0, 0.0, 0.138756, 1.032719, 1.737744, 0.54604, 1.964188, 1.09852, 1.600144, 1.406094, 1.491822, 0.504435, 1.0, 1.0, 0.0, 1.898207, 1.858959, 0.110164, 0.875559, 0.024409, 0.367739, 1.852587, 0.755329, 0.126964, 1.147889, 1.0, 1.0, 0.0, 0.374914, 1.564331, 1.218059, 1.877848, 0.209167, 1.458295, 0.152921, 0.589017, 1.610823, 1.843708, 1.0, 1.0, 0.0, 0.113296, 1.321201, 0.352085, 1.989424, 0.106816, 0.526028, 0.535334, 1.525832, 1.030717, 0.778521, 1.0, 1.0, 0.0, 0.325969, 0.345854, 0.144434, 0.358698, 1.176167, 0.985261, 1.045117, 1.732317, 1.301922, 0.913824, 1.0, 1.0, 0.0, 0.299956, 1.607262, 0.54261, 1.686827, 1.133771, 0.964085, 0.498744, 1.916791, 0.59393, 1.784905, 1.0, 1.0, 0.0, 1.050038, 0.414032, 0.805368, 1.731645, 1.238555, 1.284437, 0.659694, 1.654002, 0.559588, 1.329483, 1.0, 1.0, 0.0, 1.576912, 1.812203, 0.378607, 1.139914, 1.428911, 0.606778, 0.601802, 1.620971, 0.485459, 0.095943, 1.0, 1.0, 0.0, 0.348698, 1.280218, 0.158756, 0.999035, 1.120368, 1.525332, 0.221014, 1.650828, 0.424302, 0.909746, 1.0, 1.0, 0.0, 1.927778, 0.980503, 0.789579, 1.939464, 1.991026, 0.654966, 0.116232, 0.300867, 1.694313, 1.203679, 1.0, 1.0, 0.0]}}";
    public static final String TENSOR_MAP_JSON_STRING_2 = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"2\"]}, \"y\": {\"shape\": [1], \"value\": [1]}, \"x\": {\"shape\": [18, 13], \"value\": [1.799629, 1.52179, 1.784469, 1.653022, 1.270414, 0.686919, 0.985187, 1.978955, 1.748691, 0.973343, 1.0, 1.0, 1.0, 0.372508, 1.665185, 0.216902, 0.720034, 1.65562, 0.376195, 0.947337, 1.113516, 0.448184, 0.997362, 1.0, 1.0, 1.0, 0.414792, 0.117768, 0.929763, 1.749554, 0.064235, 1.376615, 0.85802, 0.278813, 1.776654, 1.616665, 1.0, 1.0, 1.0, 1.519702, 1.725569, 0.818573, 1.386478, 1.231919, 0.889136, 1.697129, 0.79401, 1.543517, 1.383331, 1.0, 1.0, 1.0, 0.706273, 1.54562, 1.219424, 1.749424, 1.730206, 1.82533, 1.750217, 0.281383, 0.806989, 1.296218, 1.0, 1.0, 1.0, 1.958282, 0.391785, 0.367152, 0.301667, 0.545038, 1.953179, 1.979316, 1.401177, 0.243106, 1.231895, 1.0, 1.0, 1.0, 0.342093, 1.082309, 1.291035, 0.88148, 1.041577, 1.287055, 0.064831, 0.417112, 1.586351, 1.498987, 1.0, 1.0, 1.0, 0.214506, 0.159714, 0.269104, 0.311309, 1.631314, 1.952836, 1.176351, 0.506047, 0.290006, 1.102978, 1.0, 1.0, 1.0, 1.952711, 1.712632, 1.317761, 0.540833, 1.405419, 0.268341, 1.581513, 1.178037, 1.449714, 1.493807, 1.0, 1.0, 1.0, 0.897465, 1.827958, 0.427271, 1.911452, 0.381933, 0.374252, 0.262179, 1.133536, 0.922216, 1.151406, 1.0, 1.0, 1.0, 0.031189, 1.270182, 1.407087, 0.148241, 1.222354, 0.191868, 1.671846, 1.873844, 0.089231, 1.715883, 1.0, 1.0, 1.0, 1.099698, 0.031973, 1.141854, 1.031918, 0.235999, 0.6345, 1.816179, 0.236207, 1.078346, 1.668874, 1.0, 1.0, 1.0, 0.847958, 0.077768, 1.832514, 0.138691, 0.602515, 1.744633, 1.853385, 1.515562, 0.33635, 0.722796, 1.0, 1.0, 1.0, 1.600027, 1.258885, 1.609874, 0.273606, 0.629603, 1.738648, 0.359466, 0.503527, 0.318331, 1.497897, 1.0, 1.0, 1.0, 1.999295, 0.083619, 1.649718, 0.696049, 0.630784, 1.227827, 1.715967, 1.218273, 1.325, 1.560908, 1.0, 1.0, 1.0, 0.988283, 1.990902, 1.058515, 0.582253, 1.22171, 1.769885, 1.374177, 0.249991, 1.897595, 0.391562, 1.0, 1.0, 1.0, 0.065285, 1.455318, 0.525378, 1.770743, 0.669877, 0.215384, 0.356776, 0.073562, 0.156812, 0.685606, 1.0, 1.0, 1.0, 0.967106, 0.735306, 0.039764, 0.337489, 1.358698, 0.141332, 0.946013, 0.542656, 1.989379, 0.604451, 1.0, 1.0, 1.0]}}";

    public DataSerializer serializer;

    @Before
    public void setUp() throws IOException {
        Files.createDirectories(INPUT_PATH);
        // System.err.println("ENTER TestDataSerializer#setUp");
    }

    @After
    public void tearDown() throws IOException {
        PathUtils.deleteDirectory(INPUT_PATH);
        // System.err.println("ENTER TestDataSerializer#tearDown");
    }

    @Test
    public void testSave() throws FLException, IOException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);

        DataMetadata metaData = dataSerializer.getMetadata();
        assertNull(metaData.get("save_result"));

        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);
        dataSerializer.save(tensorMap);
        metaData = dataSerializer.getMetadata();
        assertEquals("success", metaData.get("save_result"));

        tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING_2);
        dataSerializer.save(tensorMap);
        assertEquals("success", metaData.get("save_result"));

        StringBuffer idxJsonString = new StringBuffer();
        try (BufferedReader br = Files.newBufferedReader(idxFile)) {
            br.lines().forEach(line -> {
                idxJsonString.append(line);
            });
        }
        StringBuffer datJsonString = new StringBuffer();
        try (BufferedReader br = Files.newBufferedReader(datFile)) {
            br.lines().forEach(line -> {
                datJsonString.append(line.trim() + System.lineSeparator());
            });
        }
        int lineOffset1 = Integer.parseInt(idxJsonString.substring(0, 9));
        int lineOffset2 = Integer.parseInt(idxJsonString.substring(9, 18));
        String tensorMapJsonString = datJsonString.substring(lineOffset1, lineOffset2);
        String tensorMapJsonString2 = datJsonString.substring(lineOffset2);

        // line 1
        {
            TensorMap tensorMapFromJson = TensorMap.fromJsonString(tensorMapJsonString);
            assertNotNull(tensorMapFromJson);

            Tensor tensorNumOfFeatures = tensorMapFromJson.get("num_of_features");
            assertNotNull(tensorNumOfFeatures);
            assertTrue(tensorNumOfFeatures.isScalar());
            Integer numOfFeaturesScalarValue = (Integer)tensorNumOfFeatures.getValue();
            assertEquals(13, numOfFeaturesScalarValue.intValue());

            Tensor tensorGroupLabel = tensorMapFromJson.get("group_label");
            assertNotNull(tensorGroupLabel);
            assertTrue(tensorGroupLabel.isScalar());
            String groupLabelScalarValue = (String)tensorGroupLabel.getValue();
            assertEquals("1", groupLabelScalarValue);

            Tensor tensorY = tensorMapFromJson.get("y");
            assertNotNull(tensorY);
            assertTrue(tensorY.isScalar());
            Integer yScalarValue = (Integer)tensorY.getValue();
            assertEquals(0, yScalarValue.intValue());

            Tensor tensorX = tensorMapFromJson.get("x");
            assertNotNull(tensorX);
            assertEquals(2, tensorX.dims());
            assertEquals(16, tensorX.getDim(0));
            assertEquals(13, tensorX.getDim(1));
            assertEquals(208, tensorX.size());
            Double[] XTensorValue = (Double[])tensorX.getValue();
            assertEquals(0.857794, XTensorValue[0].doubleValue(), 0.0);
            assertEquals(0.000000, XTensorValue[12].doubleValue(), 0.0);
            assertEquals(1.053484, XTensorValue[13].doubleValue(), 0.0);
            assertEquals(0.000000, XTensorValue[194].doubleValue(), 0.0);
            assertEquals(1.927778, XTensorValue[195].doubleValue(), 0.0);
            assertEquals(0.000000, XTensorValue[207].doubleValue(), 0.0);
        }

        // line 2
        {
            TensorMap tensorMapFromJson = TensorMap.fromJsonString(tensorMapJsonString2);
            assertNotNull(tensorMapFromJson);

            Tensor tensorNumOfFeatures = tensorMapFromJson.get("num_of_features");
            assertNotNull(tensorNumOfFeatures);
            assertTrue(tensorNumOfFeatures.isScalar());
            Integer numOfFeaturesScalarValue = (Integer)tensorNumOfFeatures.getValue();
            assertEquals(13, numOfFeaturesScalarValue.intValue());

            Tensor tensorGroupLabel = tensorMapFromJson.get("group_label");
            assertNotNull(tensorGroupLabel);
            assertTrue(tensorGroupLabel.isScalar());
            String groupLabelScalarValue = (String)tensorGroupLabel.getValue();
            assertEquals("2", groupLabelScalarValue);

            Tensor tensorY = tensorMapFromJson.get("y");
            assertNotNull(tensorY);
            assertTrue(tensorY.isScalar());
            Integer yScalarValue = (Integer)tensorY.getValue();
            assertEquals(1, yScalarValue.intValue());

            Tensor tensorX = tensorMapFromJson.get("x");
            assertNotNull(tensorX);
            assertEquals(2, tensorX.dims());
            assertEquals(18, tensorX.getDim(0));
            assertEquals(13, tensorX.getDim(1));
            assertEquals(234, tensorX.size());
            Double[] XTensorValue = (Double[])tensorX.getValue();
            assertEquals(1.799629, XTensorValue[0].doubleValue(), 0.0);
            assertEquals(1.000000, XTensorValue[12].doubleValue(), 0.0);
            assertEquals(0.372508, XTensorValue[13].doubleValue(), 0.0);
            assertEquals(1.000000, XTensorValue[220].doubleValue(), 0.0);
            assertEquals(0.967106, XTensorValue[221].doubleValue(), 0.0);
            assertEquals(1.000000, XTensorValue[233].doubleValue(), 0.0);
        }
    }

    @Test
    public void testSaveWithNull() throws FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");

        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        try {
            dataSerializer.save(null);
            fail();
        }
        catch (NullPointerException ex) {
            ;
        }

        DataMetadata metaData = dataSerializer.getMetadata();
        assertNull(metaData.get("save_result"));
    }

    @Test
    public void testSaveWithEmptyTensorMap() throws FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        TensorMap tensorMap = TensorMap.fromJsonString("{}");

        dataSerializer.save(tensorMap);

        DataMetadata metaData = dataSerializer.getMetadata();
        assertEquals("success", metaData.get("save_result"));
    }

    @Test
    public void testSaveWithNotWritableDataFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        datFile.toFile().createNewFile();
        datFile.toFile().setWritable(false);
        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);

        dataSerializer.save(tensorMap);

        DataMetadata metaData = dataSerializer.getMetadata();
        assertEquals("failed", metaData.get("save_result"));
    }

    @Test
    public void testSaveWithNotWritableIndexFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        idxFile.toFile().createNewFile();
        idxFile.toFile().setWritable(false);
        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);

        dataSerializer.save(tensorMap);

        DataMetadata metaData = dataSerializer.getMetadata();
        assertEquals("failed", metaData.get("save_result"));
    }

    @Test
    public void testSaveWithNotWritableBothFiles() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        datFile.toFile().createNewFile();
        datFile.toFile().setWritable(false);
        idxFile.toFile().createNewFile();
        idxFile.toFile().setWritable(false);
        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);

        dataSerializer.save(tensorMap);

        DataMetadata metaData = dataSerializer.getMetadata();
        assertEquals("failed", metaData.get("save_result"));
    }

    @Test
    public void testGetMetadata() throws FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);
        dataSerializer.save(tensorMap);

        DataMetadata metaData = dataSerializer.getMetadata();

        String data_file = metaData.get("tensor_map_file");
        assertEquals(Paths.get("src/test/resources/input/TestData.jsonl").toAbsolutePath().toString(), data_file);
        String index_file = metaData.get("tensor_map_index_file");
        assertEquals(Paths.get("src/test/resources/input/TestData.txt").toAbsolutePath().toString(), index_file);
        assertEquals("success", metaData.get("save_result"));
    }

    @Test
    public void testCreateFor() throws FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");

        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);

        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);
        dataSerializer.save(tensorMap);
        DataMetadata metaData = dataSerializer.getMetadata();
        assertEquals("success", metaData.get("save_result"));
    }

    @Test
    public void testCreateForWithNotWritableDataFile() throws FLException, IOException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "notWritable/TestData.jsonl");
        datFile.getParent().toFile().createNewFile();
        datFile.getParent().toFile().setWritable(false);
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Permission denied on parent directory of TensorMap file. [%s]", datFile.getParent().toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithNotWritableIndexFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "notWritable/TestData.txt");
        idxFile.getParent().toFile().createNewFile();
        idxFile.getParent().toFile().setWritable(false);

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Permission denied on parent directory of TensorMapIndex file. [%s]", idxFile.getParent().toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithNotWritableBothFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "notWritableA/TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "notWritableB/TestData.txt");
        datFile.getParent().toFile().createNewFile();
        datFile.getParent().toFile().setWritable(false);
        idxFile.getParent().toFile().createNewFile();
        idxFile.getParent().toFile().setWritable(false);

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Permission denied on parent directory of TensorMap file. [%s]", datFile.getParent().toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithNullTensorMapFile() throws FLException {
        Path datFile = null;
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (NullPointerException ex) {
            ;
        }
    }

    @Test
    public void testCreateForWithNullIndexFile() throws FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = null;

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (NullPointerException ex) {
            ;
        }
    }

    @Test
    public void testCreateForWithNullBothFile() throws FLException {
        Path datFile = null;
        Path idxFile = null;

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (NullPointerException ex) {
            ;
        }
    }

    @Test
    public void testCreateForWithSamePath() throws FLException {
        Path datFile = Paths.get("src/test/resources/input/TestData.jsonl");
        Path idxFile = Paths.get("src/test/resources/input/TestData.jsonl").toAbsolutePath();

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Input paths are the same. [%s][%s]", datFile.toAbsolutePath(), idxFile.toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithEmptyDataFileName() throws FLException {
        Path datFile = Paths.get("");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals("Input path is empty.", ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithEmptyIndexFileName() throws FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get("");

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals("Input path is empty.", ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithEmptyBothFileName() throws FLException {
        Path datFile = Paths.get("");
        Path idxFile = Paths.get("");

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals("Input path is empty.", ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithExistsDataFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        datFile.toFile().createNewFile();
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Input path exists. [%s][%s]", datFile.toAbsolutePath(), idxFile.toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithExistsIndexFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        idxFile.toFile().createNewFile();

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Input path exists. [%s][%s]", datFile.toAbsolutePath(), idxFile.toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testCreateForWithExistsBothFile() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        datFile.toFile().createNewFile();
        idxFile.toFile().createNewFile();

        try {
            DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
            fail();
        }
        catch (FLException ex) {
            assertEquals(String.format("Input path exists. [%s][%s]", datFile.toAbsolutePath(), idxFile.toAbsolutePath()), ex.getMessage());
        }
    }

    @Test
    public void testWasSuccess() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        DataMetadata metaData = dataSerializer.getMetadata();
        assertNull(metaData.get("save_result"));
        assertFalse(DataSerializer.wasSuccess(metaData));

        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);
        dataSerializer.save(tensorMap);
        metaData = dataSerializer.getMetadata();
        assertEquals("success", metaData.get("save_result"));
        assertTrue(DataSerializer.wasSuccess(metaData));

        datFile.toFile().setWritable(false);
        dataSerializer.save(tensorMap);
        metaData = dataSerializer.getMetadata();
        assertEquals("failed", metaData.get("save_result"));
        assertFalse(DataSerializer.wasSuccess(metaData));
    }

    @Test
    public void testWasSaved() throws IOException, FLException {
        Path datFile = Paths.get(INPUT_PATH.toString(), "TestData.jsonl");
        Path idxFile = Paths.get(INPUT_PATH.toString(), "TestData.txt");
        DataSerializer dataSerializer = DataSerializer.createFor(datFile, idxFile);
        DataMetadata metaData = dataSerializer.getMetadata();
        assertNull(metaData.get("save_result"));
        assertFalse(DataSerializer.wasSaved(metaData));

        TensorMap tensorMap = TensorMap.fromJsonString(TENSOR_MAP_JSON_STRING);
        dataSerializer.save(tensorMap);
        metaData = dataSerializer.getMetadata();
        assertEquals("success", metaData.get("save_result"));
        assertTrue(DataSerializer.wasSaved(metaData));

        datFile.toFile().setWritable(false);
        dataSerializer.save(tensorMap);
        metaData = dataSerializer.getMetadata();
        assertEquals("failed", metaData.get("save_result"));
        assertTrue(DataSerializer.wasSaved(metaData));
    }
}

