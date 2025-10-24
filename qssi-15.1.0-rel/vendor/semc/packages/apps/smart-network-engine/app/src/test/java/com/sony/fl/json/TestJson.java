package com.sony.fl.json;

import java.lang.reflect.InvocationTargetException;

import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.ObjectNode;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

import com.sony.fl.utils.DataMetadataUtil;

public class TestJson {
    @Test
    public void test_Initialize_param_Serialize() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = com.sony.fl.json.LinearFedHLCR.parameters.Initialize.newInstance();

        initialize.parameters.server.globalWeight = "__globalWeight__";
        initialize.parameters.server.linearModels.add("__linearModel1__");
        initialize.parameters.server.linearModels.add("__linearModel2__");
        initialize.parameters.internal.clusterMap = "__clusterMap__";

        String json = Json.serialize(initialize);
        assertNotNull(json);

        System.out.printf("### test_Initialize_param_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Initialize", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_server = jn_parameters.get("server");
        assertNotNull(jn_server);
        JsonNode jn_globalWeight = jn_server.get("globalWeight");
        assertNotNull(jn_globalWeight);
        assertEquals("__globalWeight__", jn_globalWeight.textValue());
        JsonNode jn_linearModels = jn_server.get("linearModels");
        assertEquals(2, jn_linearModels.size());
        JsonNode jn_linearModels1 = jn_linearModels.get(0);
        assertNotNull(jn_linearModels1);
        assertEquals("__linearModel1__", jn_linearModels1.textValue());
        JsonNode jn_linearModels2 = jn_linearModels.get(1);
        assertNotNull(jn_linearModels2);
        assertEquals("__linearModel2__", jn_linearModels2.textValue());
        JsonNode jn_internal = jn_parameters.get("internal");
        assertNotNull(jn_internal);
        JsonNode jn_clusterMap = jn_internal.get("clusterMap");
        assertNotNull(jn_clusterMap);
        assertEquals("__clusterMap__", jn_clusterMap.textValue());
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{\"globalWeight\":\"__globalWeight__\",\"linearModels\":[\"__linearModel1__\",\"__linearModel2__\"]},\"internal\":{\"clusterMap\":\"__clusterMap__\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertEquals("__globalWeight__", server.globalWeight);
        assertEquals(2, server.linearModels.size());
        assertEquals("__linearModel1__", server.linearModels.get(0));
        assertEquals("__linearModel2__", server.linearModels.get(1));
        assertEquals("__clusterMap__", internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize: server.linearModels#1[%s]%n", server.linearModels.get(0));
        System.out.printf("### test_Initialize_param_Deserialize: server.linearModels#2[%s]%n", server.linearModels.get(1));
        System.out.printf("### test_Initialize_param_Deserialize: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Training_param_Serialize() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException, JsonProcessingException {/*[[[*/

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", "__tensor_map_file__");
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", "__tensor_map_index_file__");
        DataMetadataUtil.set(dataMetadata, "save_result", "__save_result__");

        com.sony.fl.json.LinearFedHLCR.parameters.Training training = com.sony.fl.json.LinearFedHLCR.parameters.Training.newInstance();

        training.parameters.server.hyperParams = "__hyperParams__";
        training.parameters.server.output = "__server__.__output__";
        training.parameters.client.dataSet = dataMetadata.toJsonString();
        training.parameters.client.output = "__client__.__output__";

        String json = Json.serialize(training);
        assertNotNull(json);

        System.out.printf("### test_Training_param_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Training", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_server = jn_parameters.get("server");
        assertNotNull(jn_server);
        JsonNode jn_client = jn_parameters.get("client");
        assertNotNull(jn_client);
        JsonNode jn_hyperParams = jn_server.get("hyperParams");
        assertNotNull(jn_hyperParams);
        assertEquals("__hyperParams__", jn_hyperParams.textValue());
        JsonNode jn_serverOutput = jn_server.get("output");
        assertNotNull(jn_serverOutput);
        assertEquals("__server__.__output__", jn_serverOutput.textValue());
        JsonNode jn_dataSet = jn_client.get("dataSet");
        assertNotNull(jn_dataSet);

        JsonNode jn_dataMetadata = new ObjectMapper().readTree(jn_dataSet.textValue());
        JsonNode jn_tensor_map_file = jn_dataMetadata.get("tensor_map_file");
        assertNotNull(jn_tensor_map_file);
        assertEquals("__tensor_map_file__", jn_tensor_map_file.textValue());
        JsonNode jn_tensor_map_index_file = jn_dataMetadata.get("tensor_map_index_file");
        assertNotNull(jn_tensor_map_index_file);
        assertEquals("__tensor_map_index_file__", jn_tensor_map_index_file.textValue());
        JsonNode jn_save_result = jn_dataMetadata.get("save_result");
        assertNotNull(jn_save_result);
        assertEquals("__save_result__", jn_save_result.textValue());

        JsonNode jn_clientOutput = jn_client.get("output");
        assertNotNull(jn_clientOutput);
        assertEquals("__client__.__output__", jn_clientOutput.textValue());
    }/*]]]*/

    @Test
    public void test_Training_param_Deserialize() throws JsonProcessingException {/*[[[*/
        String json = "{\"method\":\"Training\",\"parameters\":{\"server\":{\"hyperParams\":\"__hyperParams__\",\"output\":\"__server__.__output__\"},\"client\":{\"dataSet\":\"{\\\"save_result\\\":\\\"__save_result__\\\",\\\"tensor_map_file\\\":\\\"__tensor_map_file__\\\",\\\"tensor_map_index_file\\\":\\\"__tensor_map_index_file__\\\"}\",\"output\":\"__client__.__output__\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Training training = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Training.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Training.Parameters parameters = training.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Training.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Training.Parameters.Client client = parameters.client;

        assertEquals("Training", training.method);
        assertEquals("__hyperParams__", server.hyperParams);
        assertEquals("__server__.__output__", server.output);

        JsonNode jn_dataSet = new ObjectMapper().readTree(client.dataSet);
        JsonNode jn_tensor_map_file = jn_dataSet.get("tensor_map_file");
        assertNotNull(jn_tensor_map_file);
        assertEquals("__tensor_map_file__", jn_tensor_map_file.textValue());
        JsonNode jn_tensor_map_index_file = jn_dataSet.get("tensor_map_index_file");
        assertNotNull(jn_tensor_map_index_file);
        assertEquals("__tensor_map_index_file__", jn_tensor_map_index_file.textValue());
        JsonNode jn_save_result = jn_dataSet.get("save_result");
        assertNotNull(jn_save_result);
        assertEquals("__save_result__", jn_save_result.textValue());

        assertEquals("__client__.__output__", client.output);

        System.out.printf("### test_Training_param_Deserialize: method[%s]%n", training.method);
        System.out.printf("### test_Training_param_Deserialize: server.hyperParams[%s]%n", server.hyperParams);
        System.out.printf("### test_Training_param_Deserialize: server.output[%s]%n", server.output);
        System.out.printf("### test_Training_param_Deserialize: client.dataSet[%s]%n", client.dataSet);
        System.out.printf("### test_Training_param_Deserialize: client.output[%s]%n", client.output);
    }/*]]]*/

    @Test
    public void test_Training_result_Serialize() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.results.Training training = com.sony.fl.json.LinearFedHLCR.results.Training.newInstance();

        training.results.state = 123;
        training.results.server.linearModels.add("__linearModel1__");
        training.results.server.linearModels.add("__linearModel2__");
        training.results.server.localCount = "__localCount__";
        training.results.server.validationMetrix = "__validationMetrix__";
        training.results.client.clusterMap = "__clusterMap__";

        String json = Json.serialize(training);
        assertNotNull(json);

        System.out.printf("### test_Training_result_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Training", method.textValue());
        JsonNode jn_results = jn_node.get("results");
        assertNotNull(jn_results);
        JsonNode jn_state = jn_results.get("state");
        assertNotNull(jn_state);
        assertEquals(123, jn_state.intValue());
        JsonNode jn_server = jn_results.get("server");
        assertNotNull(jn_server);
        JsonNode jn_client = jn_results.get("client");
        assertNotNull(jn_client);
        JsonNode jn_linearModels = jn_server.get("linearModels");
        assertEquals(2, jn_linearModels.size());
        JsonNode jn_linearModel1 = jn_linearModels.get(0);
        assertNotNull(jn_linearModel1);
        assertEquals("__linearModel1__", jn_linearModel1.textValue());
        JsonNode jn_linearModel2 = jn_linearModels.get(1);
        assertNotNull(jn_linearModel2);
        assertEquals("__linearModel2__", jn_linearModel2.textValue());
        JsonNode jn_localCount = jn_server.get("localCount");
        assertNotNull(jn_localCount);
        assertEquals("__localCount__", jn_localCount.textValue());
        JsonNode jn_validationMetrix = jn_server.get("validationMetrix");
        assertNotNull(jn_validationMetrix);
        assertEquals("__validationMetrix__", jn_validationMetrix.textValue());
        JsonNode jn_clusterMap = jn_client.get("clusterMap");
        assertNotNull(jn_clusterMap);
        assertEquals("__clusterMap__", jn_clusterMap.textValue());
    }/*]]]*/

    @Test
    public void test_Training_result_Deserialize() {/*[[[*/
        String json = "{\"method\":\"Training\",\"results\":{\"state\":123,\"server\":{\"linearModels\":[\"__linearModel1__\",\"__linearModel2__\"],\"localCount\":\"__localCount__\",\"validationMetrix\":\"__validationMetrix__\"},\"client\":{\"clusterMap\":\"__clusterMap__\"}}}";

        com.sony.fl.json.LinearFedHLCR.results.Training training = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Training.class);

        com.sony.fl.json.LinearFedHLCR.results.Training.Results results = training.results;
        com.sony.fl.json.LinearFedHLCR.results.Training.Results.Server server = results.server;
        com.sony.fl.json.LinearFedHLCR.results.Training.Results.Client client = results.client;

        assertEquals("Training", training.method);
        assertEquals(123, training.results.state.intValue());
        assertEquals(2, server.linearModels.size());
        assertEquals("__linearModel1__", server.linearModels.get(0));
        assertEquals("__linearModel2__", server.linearModels.get(1));
        assertEquals("__localCount__", server.localCount);
        assertEquals("__validationMetrix__", server.validationMetrix);
        assertEquals("__clusterMap__", client.clusterMap);

        System.out.printf("### test_Training_result_Deserialize: method[%s]%n", training.method);
        System.out.printf("### test_Training_result_Deserialize: state[%d]%n", training.results.state);
        System.out.printf("### test_Training_result_Deserialize: server.linearModels#1[%s]%n", server.linearModels.get(0));
        System.out.printf("### test_Training_result_Deserialize: server.linearModels#2[%s]%n", server.linearModels.get(1));
        System.out.printf("### test_Training_result_Deserialize: server.localCount[%s]%n", server.localCount);
        System.out.printf("### test_Training_result_Deserialize: server.validationMetrix[%s]%n", server.validationMetrix);
        System.out.printf("### test_Training_result_Deserialize: client.clusterMap[%s]%n", client.clusterMap);
    }/*]]]*/

    @Test
    public void test_Evaluation_param_Serialize() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException, JsonProcessingException {/*[[[*/

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", "__tensor_map_file__");
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", "__tensor_map_index_file__");
        DataMetadataUtil.set(dataMetadata, "save_result", "__save_result__");

        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation evaluation = com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.newInstance();

        evaluation.parameters.server.output = "__output__";
        evaluation.parameters.client.dataSet = dataMetadata.toJsonString();

        String json = Json.serialize(evaluation);
        assertNotNull(json);

        System.out.printf("### test_Evaluation_param_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Evaluation", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_server = jn_parameters.get("server");
        assertNotNull(jn_server);
        JsonNode jn_output = jn_server.get("output");
        assertNotNull(jn_output);
        assertEquals("__output__", jn_output.textValue());

        JsonNode jn_client = jn_parameters.get("client");
        assertNotNull(jn_client);
        JsonNode jn_dataSet = jn_client.get("dataSet");
        assertNotNull(jn_dataSet);
        JsonNode jn_dataMetadata = new ObjectMapper().readTree(jn_dataSet.textValue());
        JsonNode jn_tensor_map_file = jn_dataMetadata.get("tensor_map_file");
        assertNotNull(jn_tensor_map_file);
        assertEquals("__tensor_map_file__", jn_tensor_map_file.textValue());
        JsonNode jn_tensor_map_index_file = jn_dataMetadata.get("tensor_map_index_file");
        assertNotNull(jn_tensor_map_index_file);
        assertEquals("__tensor_map_index_file__", jn_tensor_map_index_file.textValue());
        JsonNode jn_save_result = jn_dataMetadata.get("save_result");
        assertNotNull(jn_save_result);
        assertEquals("__save_result__", jn_save_result.textValue());
    }/*]]]*/

    @Test
    public void test_Evaluation_param_Deserialize() throws JsonProcessingException {/*[[[*/
        String json = "{\"method\":\"Evaluation\",\"parameters\":{\"server\":{\"output\":\"__output__\"},\"client\":{\"dataSet\":\"{\\\"save_result\\\":\\\"__save_result__\\\",\\\"tensor_map_file\\\":\\\"__tensor_map_file__\\\",\\\"tensor_map_index_file\\\":\\\"__tensor_map_index_file__\\\"}\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation evaluation = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.Parameters parameters = evaluation.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.Parameters.Client client = parameters.client;

        assertEquals("Evaluation", evaluation.method);
        assertEquals("__output__", server.output);

        JsonNode jn_dataSet = new ObjectMapper().readTree(client.dataSet);
        assertNotNull(jn_dataSet);
        JsonNode jn_tensor_map_file = jn_dataSet.get("tensor_map_file");
        assertNotNull(jn_tensor_map_file);
        assertEquals("__tensor_map_file__", jn_tensor_map_file.textValue());
        JsonNode jn_tensor_map_index_file = jn_dataSet.get("tensor_map_index_file");
        assertNotNull(jn_tensor_map_index_file);
        assertEquals("__tensor_map_index_file__", jn_tensor_map_index_file.textValue());
        JsonNode jn_save_result = jn_dataSet.get("save_result");
        assertNotNull(jn_save_result);
        assertEquals("__save_result__", jn_save_result.textValue());

        System.out.printf("### test_Evaluation_param_Deserialize: method[%s]%n", evaluation.method);
        System.out.printf("### test_Evaluation_param_Deserialize: server.output[%s]%n", server.output);
        System.out.printf("### test_Evaluation_param_Deserialize: client.dataSet[%s]%n", client.dataSet);
    }/*]]]*/

    @Test
    public void test_Evaluation_result_Serialize() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluation = com.sony.fl.json.LinearFedHLCR.results.Evaluation.newInstance();

        evaluation.results.state = 123;
        evaluation.results.server.evaluationResult = "__evaluationResult__";

        String json = Json.serialize(evaluation);
        assertNotNull(json);

        System.out.printf("### test_Evaluation_result_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Evaluation", method.textValue());
        JsonNode jn_results = jn_node.get("results");
        assertNotNull(jn_results);
        JsonNode jn_state = jn_results.get("state");
        assertNotNull(jn_state);
        assertEquals(123, jn_state.intValue());
        JsonNode jn_server = jn_results.get("server");
        assertNotNull(jn_server);
        JsonNode jn_evaluationResult = jn_server.get("evaluationResult");
        assertNotNull(jn_evaluationResult);
        assertEquals("__evaluationResult__", jn_evaluationResult.textValue());
    }/*]]]*/

    @Test
    public void test_Evaluation_result_Deserialize() {/*[[[*/
        String json = "{\"method\":\"Evaluation\",\"results\":{\"state\":123,\"server\":{\"evaluationResult\":\"__evaluationResult__\"}}}";

        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluation = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Evaluation.class);

        com.sony.fl.json.LinearFedHLCR.results.Evaluation.Results results = evaluation.results;
        com.sony.fl.json.LinearFedHLCR.results.Evaluation.Results.Server server = results.server;

        assertEquals("Evaluation", evaluation.method);
        assertEquals(123, evaluation.results.state.intValue());
        assertEquals("__evaluationResult__", server.evaluationResult);

        System.out.printf("### test_Evaluation_result_Deserialize: method[%s]%n", evaluation.method);
        System.out.printf("### test_Evaluation_result_Deserialize: state[%d]%n", results.state);
        System.out.printf("### test_Evaluation_result_Deserialize: server.evaluationResult[%s]%n", server.evaluationResult);
    }/*]]]*/

    @Test
    public void test_Prediction_param_Serialize() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException, JsonProcessingException {/*[[[*/

        TensorMap tensorMap = TensorMap.newInstance();

        Tensor resultTensor = Tensor.newTensor(
            TensorShape.createShape(2, 3),
            Tensor.toDoubleArrayFrom(
                new float[][] {
                    { 1.1F, 1.2F, 1.3F },
                    { 2.1F, 2.2F, 2.3F },
                }
            )
        );
        tensorMap.set("resultTensor", resultTensor);

        com.sony.fl.json.LinearFedHLCR.parameters.Prediction prediction = com.sony.fl.json.LinearFedHLCR.parameters.Prediction.newInstance();

        prediction.parameters.application.data = tensorMap.toJsonString();

        String json = Json.serialize(prediction);
        assertNotNull(json);

        System.out.printf("### test_Prediction_param_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Prediction", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_application = jn_parameters.get("application");
        assertNotNull(jn_application);
        JsonNode jn_data = jn_application.get("data");
        assertNotNull(jn_data);

        JsonNode jn_dataSet = new ObjectMapper().readTree(jn_data.textValue());
        assertNotNull(jn_dataSet);
        JsonNode jn_tensor = jn_dataSet.get("resultTensor");
        assertNotNull(jn_tensor);
        JsonNode jn_shape = jn_tensor.get("shape");
        assertNotNull(jn_shape);
        assertEquals(2, jn_shape.size());
        assertEquals(2, jn_shape.get(0).intValue());
        assertEquals(3, jn_shape.get(1).intValue());
        JsonNode jn_value = jn_tensor.get("value");
        assertNotNull(jn_value);
        assertEquals(1.1F, jn_value.get(0).floatValue(), 0.0);
        assertEquals(1.2F, jn_value.get(1).floatValue(), 0.0);
        assertEquals(1.3F, jn_value.get(2).floatValue(), 0.0);
        assertEquals(2.1F, jn_value.get(3).floatValue(), 0.0);
        assertEquals(2.2F, jn_value.get(4).floatValue(), 0.0);
        assertEquals(2.3F, jn_value.get(5).floatValue(), 0.0);
    }/*]]]*/

    @Test
    public void test_Prediction_param_Deserialize() throws JsonProcessingException {/*[[[*/
        String json = "{\"method\":\"Prediction\",\"parameters\":{\"application\":{\"data\":\"{\\\"resultTensor\\\":{\\\"shape\\\":[2,3],\\\"value\\\":[1.100000023841858,1.2000000476837158,1.2999999523162842,2.0999999046325684,2.200000047683716,2.299999952316284]}}\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Prediction prediction = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Prediction.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Prediction.Parameters parameters = prediction.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Prediction.Parameters.Application application = parameters.application;

        assertEquals("Prediction", prediction.method);

        JsonNode jn_data = new ObjectMapper().readTree(application.data);
        assertNotNull(jn_data);
        JsonNode jn_tensor = jn_data.get("resultTensor");
        assertNotNull(jn_tensor);
        JsonNode jn_shape = jn_tensor.get("shape");
        assertNotNull(jn_shape);
        assertEquals(2, jn_shape.size());
        assertEquals(2, jn_shape.get(0).intValue());
        assertEquals(3, jn_shape.get(1).intValue());
        JsonNode jn_value = jn_tensor.get("value");
        assertNotNull(jn_value);
        assertEquals(1.1F, jn_value.get(0).floatValue(), 0.0);
        assertEquals(1.2F, jn_value.get(1).floatValue(), 0.0);
        assertEquals(1.3F, jn_value.get(2).floatValue(), 0.0);
        assertEquals(2.1F, jn_value.get(3).floatValue(), 0.0);
        assertEquals(2.2F, jn_value.get(4).floatValue(), 0.0);
        assertEquals(2.3F, jn_value.get(5).floatValue(), 0.0);

        System.out.printf("### test_Prediction_param_Deserialize: method[%s]%n", prediction.method);
        System.out.printf("### test_Prediction_param_Deserialize: data[%s]%n", application.data);
    }/*]]]*/

    @Test
    public void test_Prediction_result_Serialize() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = com.sony.fl.json.LinearFedHLCR.results.Prediction.newInstance();

        prediction.results.state = 123;
        prediction.results.application.predictionResult = "__predictionResult__";

        String json = Json.serialize(prediction);
        assertNotNull(json);

        System.out.printf("### test_Prediction_result_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Prediction", method.textValue());
        JsonNode jn_results = jn_node.get("results");
        assertNotNull(jn_results);
        JsonNode jn_state = jn_results.get("state");
        assertNotNull(jn_state);
        assertEquals(123, jn_state.intValue());
        JsonNode jn_application = jn_results.get("application");
        assertNotNull(jn_application);
        JsonNode jn_predictionResult = jn_application.get("predictionResult");
        assertNotNull(jn_predictionResult);
        assertEquals("__predictionResult__", jn_predictionResult.textValue());
    }/*]]]*/

    @Test
    public void test_Prediction_result_Deserialize() {/*[[[*/
        String json = "{\"method\":\"Prediction\",\"results\":{\"state\":123,\"application\":{\"predictionResult\":\"__predictionResult__\"}}}";

        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);

        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results results = prediction.results;
        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results.Application application = results.application;

        assertEquals("Prediction", prediction.method);
        assertEquals(123, results.state.intValue());
        assertEquals("__predictionResult__", application.predictionResult);

        System.out.printf("### test_Prediction_result_Deserialize: method[%s]%n", prediction.method);
        System.out.printf("### test_Prediction_result_Deserialize: state[%d]%n", results.state);
        System.out.printf("### test_Prediction_result_Deserialize: application.predictionResult[%s]%n", application.predictionResult);
    }/*]]]*/

    @Test
    public void test_UpdateInfo_param_Serialize() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException, JsonProcessingException {/*[[[*/

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", "__tensor_map_file__");
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", "__tensor_map_index_file__");
        DataMetadataUtil.set(dataMetadata, "save_result", "__save_result__");

        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo updateInfo = com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.newInstance();

        updateInfo.parameters.server.hyperParams = "__hyperParams__";
        updateInfo.parameters.client.dataSet = dataMetadata.toJsonString();
        updateInfo.parameters.client.output = "__output__";

        String json = Json.serialize(updateInfo);
        assertNotNull(json);

        System.out.printf("### test_UpdateInfo_param_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("UpdateInfo", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_server = jn_parameters.get("server");
        assertNotNull(jn_server);
        JsonNode jn_client = jn_parameters.get("client");
        assertNotNull(jn_client);
        JsonNode jn_hyperParams = jn_server.get("hyperParams");
        assertNotNull(jn_hyperParams);
        assertEquals("__hyperParams__", jn_hyperParams.textValue());
        JsonNode jn_dataSet = jn_client.get("dataSet");
        assertNotNull(jn_dataSet);

        JsonNode jn_dataMetadata = new ObjectMapper().readTree(jn_dataSet.textValue());
        JsonNode jn_tensor_map_file = jn_dataMetadata.get("tensor_map_file");
        assertNotNull(jn_tensor_map_file);
        assertEquals("__tensor_map_file__", jn_tensor_map_file.textValue());
        JsonNode jn_tensor_map_index_file = jn_dataMetadata.get("tensor_map_index_file");
        assertNotNull(jn_tensor_map_index_file);
        assertEquals("__tensor_map_index_file__", jn_tensor_map_index_file.textValue());
        JsonNode jn_save_result = jn_dataMetadata.get("save_result");
        assertNotNull(jn_save_result);
        assertEquals("__save_result__", jn_save_result.textValue());

        JsonNode jn_output = jn_client.get("output");
        assertNotNull(jn_output);
        assertEquals("__output__", jn_output.textValue());
    }/*]]]*/

    @Test
    public void test_UpdateInfo_param_Deserialize() throws JsonProcessingException {/*[[[*/
        String json = "{\"method\":\"UpdateInfo\",\"parameters\":{\"server\": {\"hyperParams\":\"__hyperParams__\"}, \"client\": {\"dataSet\":\"{\\\"save_result\\\":\\\"__save_result__\\\",\\\"tensor_map_file\\\":\\\"__tensor_map_file__\\\",\\\"tensor_map_index_file\\\":\\\"__tensor_map_index_file__\\\"}\",\"output\":\"__output__\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo updateInfo = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.class);

        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.Parameters parameters = updateInfo.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.Parameters.Client client = parameters.client;

        assertEquals("UpdateInfo", updateInfo.method);
        assertEquals("__hyperParams__", server.hyperParams);

        JsonNode jn_dataSet = new ObjectMapper().readTree(client.dataSet);
        assertNotNull(jn_dataSet);
        JsonNode jn_tensor_map_file = jn_dataSet.get("tensor_map_file");
        assertNotNull(jn_tensor_map_file);
        assertEquals("__tensor_map_file__", jn_tensor_map_file.textValue());
        JsonNode jn_tensor_map_index_file = jn_dataSet.get("tensor_map_index_file");
        assertNotNull(jn_tensor_map_index_file);
        assertEquals("__tensor_map_index_file__", jn_tensor_map_index_file.textValue());
        JsonNode jn_save_result = jn_dataSet.get("save_result");
        assertNotNull(jn_save_result);
        assertEquals("__save_result__", jn_save_result.textValue());

        assertEquals("__output__", client.output);

        System.out.printf("### test_UpdateInfo_param_Deserialize: method[%s]%n", updateInfo.method);
        System.out.printf("### test_UpdateInfo_param_Deserialize: server.hyperParams[%s]%n", server.hyperParams);
        System.out.printf("### test_UpdateInfo_param_Deserialize: client.dataSet[%s]%n", client.dataSet);
        System.out.printf("### test_UpdateInfo_param_Deserialize: client.output[%s]%n", client.output);
    }/*]]]*/

    @Test
    public void test_UpdateInfo_result_Serialize() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfo = com.sony.fl.json.LinearFedHLCR.results.UpdateInfo.newInstance();

        updateInfo.results.state = 123;
        updateInfo.results.client.clusterMap = "__clusterMap__";

        String json = Json.serialize(updateInfo);
        assertNotNull(json);

        System.out.printf("### test_UpdateInfo_result_Serialize: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("UpdateInfo", method.textValue());
        JsonNode jn_results = jn_node.get("results");
        assertNotNull(jn_results);
        JsonNode jn_state = jn_results.get("state");
        assertEquals(123, jn_state.intValue());
        JsonNode jn_client = jn_results.get("client");
        assertNotNull(jn_client);
        JsonNode jn_clusterMap = jn_client.get("clusterMap");
        assertNotNull(jn_clusterMap);
        assertEquals("__clusterMap__", jn_clusterMap.textValue());
    }/*]]]*/

    @Test
    public void test_UpdateInfo_result_Deserialize() {/*[[[*/
        String json = "{\"method\":\"UpdateInfo\",\"results\":{\"state\":123,\"client\":{\"clusterMap\":\"__clusterMap__\"}}}";

        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfo = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.UpdateInfo.class);

        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo.Results results = updateInfo.results;
        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo.Results.Client client = results.client;

        assertEquals("UpdateInfo", updateInfo.method);
        assertEquals(123, results.state.intValue());
        assertEquals("__clusterMap__", client.clusterMap);

        System.out.printf("### test_UpdateInfo_result_Deserialize: method[%s]%n", updateInfo.method);
        System.out.printf("### test_UpdateInfo_result_Deserialize: results.state[%d]%n", results.state);
        System.out.printf("### test_UpdateInfo_result_Deserialize: results.client.clusterMap[%s]%n", client.clusterMap);
    }/*]]]*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    @Test
    public void test_Initialize_param_Serialize_NoLinearModels() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = com.sony.fl.json.LinearFedHLCR.parameters.Initialize.newInstance();

        initialize.parameters.server.globalWeight = "__globalWeight__";
        initialize.parameters.internal.clusterMap = "__clusterMap__";

        String json = Json.serialize(initialize);
        assertNotNull(json);

        System.out.printf("### test_Initialize_param_Serialize_NoLinearModels: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Initialize", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_server = jn_parameters.get("server");
        assertNotNull(jn_server);
        JsonNode jn_globalWeight = jn_server.get("globalWeight");
        assertNotNull(jn_globalWeight);
        assertEquals("__globalWeight__", jn_globalWeight.textValue());
        JsonNode jn_linearModels = jn_server.get("linearModels");
        assertEquals(0, jn_linearModels.size());
        JsonNode jn_internal = jn_parameters.get("internal");
        assertNotNull(jn_internal);
        JsonNode jn_clusterMap = jn_internal.get("clusterMap");
        assertNotNull(jn_clusterMap);
        assertEquals("__clusterMap__", jn_clusterMap.textValue());
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_NoLinearModels_p1() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{\"globalWeight\":\"__globalWeight__\",\"linearModels\":[]},\"internal\":{\"clusterMap\":\"__clusterMap__\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertEquals("__globalWeight__", server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertEquals("__clusterMap__", internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_NoLinearModels_p1: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_NoLinearModels_p1: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_NoLinearModels_p1: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_NoLinearModels_p2() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{\"globalWeight\":\"__globalWeight__\"},\"internal\":{\"clusterMap\":\"__clusterMap__\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertEquals("__globalWeight__", server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertEquals("__clusterMap__", internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_NoLinearModels_p2: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_NoLinearModels_p2: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_NoLinearModels_p2: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    @Test
    public void test_Initialize_param_Serialize_onlyNew() throws JsonProcessingException {/*[[[*/

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = com.sony.fl.json.LinearFedHLCR.parameters.Initialize.newInstance();

        String json = Json.serialize(initialize);
        assertNotNull(json);

        System.out.printf("### test_Initialize_param_Serialize_onlyNew: %s%n", json);

        JsonNode jn_node = new ObjectMapper().readTree(json);
        assertNotNull(jn_node);
        JsonNode method = jn_node.get("method");
        assertEquals("Initialize", method.textValue());
        JsonNode jn_parameters = jn_node.get("parameters");
        assertNotNull(jn_parameters);
        JsonNode jn_server = jn_parameters.get("server");
        assertNotNull(jn_server);
        JsonNode jn_globalWeight = jn_server.get("globalWeight");
        assertNotNull(jn_globalWeight);
        assertNull(jn_globalWeight.textValue());
        JsonNode jn_linearModels = jn_server.get("linearModels");
        assertEquals(0, jn_linearModels.size());
        JsonNode jn_internal = jn_parameters.get("internal");
        assertNotNull(jn_internal);
        JsonNode jn_clusterMap = jn_internal.get("clusterMap");
        assertNotNull(jn_clusterMap);
        assertNull(jn_clusterMap.textValue());
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_NoParameters() {/*[[[*/
        String json = "{\"method\":\"Initialize\"}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNotNull(parameters);
        assertNotNull(server);
        assertNotNull(internal);
        assertNull(server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertNull(internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_NoParameters: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_NoParameters: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_NoParameters: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_EmptyParameters() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNotNull(parameters);
        assertNotNull(server);
        assertNotNull(internal);
        assertNull(server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertNull(internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_EmptyParameters: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyParameters: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyParameters: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_EmptyServerParameters() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{}, \"internal\":{\"clusterMap\":\"__clusterMap__\"}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNotNull(parameters);
        assertNotNull(server);
        assertNotNull(internal);
        assertNull(server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertNotNull(internal.clusterMap);
        assertEquals("__clusterMap__", internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_EmptyParameters: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyParameters: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyParameters: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_EmptyInternalParameters() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{\"globalWeight\":\"__globalWeight__\",\"linearModels\":[\"__linearModel1__\",\"__linearModel2__\"]},\"internal\":{}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNotNull(parameters);
        assertNotNull(server);
        assertNotNull(internal);
        assertNotNull(server.globalWeight);
        assertEquals("__globalWeight__", server.globalWeight);
        assertEquals(2, server.linearModels.size());
        assertEquals("__linearModel1__", server.linearModels.get(0));
        assertEquals("__linearModel2__", server.linearModels.get(1));
        assertNull(internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_EmptyInternalParameters: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyInternalParameters: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyInternalParameters: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_EmptyServerAndInternalParameters() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{},\"internal\":{}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNotNull(parameters);
        assertNotNull(server);
        assertNotNull(internal);
        assertNull(server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertNull(internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_EmptyServerAndInternalParameters: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyServerAndInternalParameters: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyServerAndInternalParameters: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_EmptyJson() {/*[[[*/
        String json = "{}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertNull(initialize.method);
        assertNotNull(parameters);
        assertNotNull(server);
        assertNotNull(internal);
        assertNull(server.globalWeight);
        assertEquals(0, server.linearModels.size());
        assertNull(internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_EmptyJson: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyJson: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_EmptyJson: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_InvalidJson() {/*[[[*/
        String json = "InvalidJson";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        assertNull(initialize);
    }/*]]]*/

    @Test
    public void test_NotSupport_Serialize() throws JsonProcessingException {/*[[[*/
        String json = Json.serialize(this);
        assertNull(json);
    }/*]]]*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    @Test
    public void test_Prediction_result_Deserialize_NoResults() {/*[[[*/
        // String json = "{\"method\":\"Prediction\",\"results\":{\"state\":123,\"application\":{\"predictionResult\":\"__predictionResult__\"}}}";
        String json = "{\"method\":\"Prediction\"}";

        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);

        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results results = prediction.results;
        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results.Application application = results.application;

        assertEquals("Prediction", prediction.method);
        assertNull(results.state);
        assertNull(application.predictionResult);

        System.out.printf("### test_Prediction_result_Deserialize_NoResults: method[%s]%n", prediction.method);
        System.out.printf("### test_Prediction_result_Deserialize_NoResults: state[%d]%n", results.state);
        System.out.printf("### test_Prediction_result_Deserialize_NoResults: application.predictionResult[%s]%n", application.predictionResult);
    }/*]]]*/

    @Test
    public void test_Prediction_result_Deserialize_EmptyResults() {/*[[[*/
        // String json = "{\"method\":\"Prediction\",\"results\":{\"state\":123,\"application\":{\"predictionResult\":\"__predictionResult__\"}}}";
        String json = "{\"method\":\"Prediction\",\"results\":{}}";

        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);

        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results results = prediction.results;
        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results.Application application = results.application;

        assertEquals("Prediction", prediction.method);
        assertNull(results.state);
        assertNull(application.predictionResult);

        System.out.printf("### test_Prediction_result_Deserialize_EmptyResults: method[%s]%n", prediction.method);
        System.out.printf("### test_Prediction_result_Deserialize_EmptyResults: state[%d]%n", results.state);
        System.out.printf("### test_Prediction_result_Deserialize_EmptyResults: application.predictionResult[%s]%n", application.predictionResult);
    }/*]]]*/

    @Test
    public void test_Prediction_result_Deserialize_NoState() {/*[[[*/
        // String json = "{\"method\":\"Prediction\",\"results\":{\"state\":123,\"application\":{\"predictionResult\":\"__predictionResult__\"}}}";
        String json = "{\"method\":\"Prediction\",\"results\":{\"application\":{\"predictionResult\":\"__predictionResult__\"}}}";

        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);

        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results results = prediction.results;
        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results.Application application = results.application;

        assertEquals("Prediction", prediction.method);
        assertNull(results.state);
        assertEquals("__predictionResult__", application.predictionResult);

        System.out.printf("### test_Prediction_result_Deserialize_NoState: method[%s]%n", prediction.method);
        System.out.printf("### test_Prediction_result_Deserialize_NoState: state[%d]%n", results.state);
        System.out.printf("### test_Prediction_result_Deserialize_NoState: application.predictionResult[%s]%n", application.predictionResult);
    }/*]]]*/

    @Test
    public void test_Prediction_result_Deserialize_NoApplication() {/*[[[*/
        // String json = "{\"method\":\"Prediction\",\"results\":{\"state\":123,\"application\":{\"predictionResult\":\"__predictionResult__\"}}}";
        String json = "{\"method\":\"Prediction\",\"results\":{\"state\":123}}";

        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);

        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results results = prediction.results;
        com.sony.fl.json.LinearFedHLCR.results.Prediction.Results.Application application = results.application;

        assertEquals("Prediction", prediction.method);
        assertEquals(123, results.state.intValue());
        assertNull(application.predictionResult);

        System.out.printf("### test_Prediction_result_Deserialize_NoApplication: method[%s]%n", prediction.method);
        System.out.printf("### test_Prediction_result_Deserialize_NoApplication: state[%d]%n", results.state);
        System.out.printf("### test_Prediction_result_Deserialize_NoApplication: application.predictionResult[%s]%n", application.predictionResult);
    }/*]]]*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    @Test
    public void test_Initialize_param_Deserialize_null() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":{\"globalWeight\":null,\"linearModels\":[null,null]},\"internal\":{\"clusterMap\":null}}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNull(server.globalWeight);
        assertEquals(2, server.linearModels.size());
        assertNull(server.linearModels.get(0));
        assertNull(server.linearModels.get(1));
        assertNull(internal.clusterMap);

        System.out.printf("### test_Initialize_param_Deserialize_null: method[%s]%n", initialize.method);
        System.out.printf("### test_Initialize_param_Deserialize_null: server.globalWeight[%s]%n", server.globalWeight);
        System.out.printf("### test_Initialize_param_Deserialize_null: server.linearModels#1[%s]%n", server.linearModels.get(0));
        System.out.printf("### test_Initialize_param_Deserialize_null: server.linearModels#2[%s]%n", server.linearModels.get(1));
        System.out.printf("### test_Initialize_param_Deserialize_null: internal.clusterMap[%s]%n", internal.clusterMap);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_null_2() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":{\"server\":null,\"internal\":null}}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertEquals("Initialize", initialize.method);
        assertNull(server);
        assertNull(internal);

        System.out.printf("### test_Initialize_param_Deserialize_null_2: method[%s]%n", initialize.method);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_null_3() {/*[[[*/
        String json = "{\"method\":\"Initialize\",\"parameters\":null}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;

        assertEquals("Initialize", initialize.method);
        assertNull(parameters);

        System.out.printf("### test_Initialize_param_Deserialize_null_3: method[%s]%n", initialize.method);
    }/*]]]*/

    @Test
    public void test_Initialize_param_Deserialize_null_4() {/*[[[*/
        String json = "{\"method\":null}";

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize initialize = Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters parameters = initialize.parameters;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Server server = parameters.server;
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize.Parameters.Internal internal = parameters.internal;

        assertNull(initialize.method);
    }/*]]]*/
}
// vim:set foldmethod=marker foldmarker=[[[,]]]:
