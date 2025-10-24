package com.sony.fl.tensor;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.junit.Test;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sony.fl.exception.FLException;

public class TestDataMetadata {
    public static final Path INPUT_PATH = Paths.get("src/test/resources/input");

    public DataMetadata meta;

    @Test
    public void testGetWithExistsKey() throws IOException, FLException {
        DataMetadata meta = new DataMetadata();
        String key1 = "tensor_map_file";
        String key2 = "tensor_map_index_file";
        String key3 = "save_result";
        String value1 = INPUT_PATH.resolve("test.jsonl").toString();
        String value2 = INPUT_PATH.resolve("test.txt").toString();
        String value3 = "success";
        meta.set(key1, value1);
        meta.set(key2, value2);
        meta.set(key3, value3);

        assertEquals(value1, meta.get(key1));
        assertEquals(value2, meta.get(key2));
        assertEquals(value3, meta.get(key3));
    }

    @Test
    public void testGetWithNotExistsKey() throws IOException, FLException {
        DataMetadata meta = new DataMetadata();
        String result = meta.get("tensor_map_file");
        assertNull(result);
    }

    @Test
    public void testGetWithEmptyKey() {
        DataMetadata meta = new DataMetadata();
        String result = meta.get("");
        assertNull(result);
    }

    @Test
    public void testSetWithExistsKey() {
        DataMetadata meta = new DataMetadata();
        String key = "tensor_map_file";
        String value = INPUT_PATH.resolve("test.jsonl").toString();

        meta.set(key, value);
        assertEquals(value, meta.get(key));

        value = "testSetWithExistsKey";
        meta.set(key, value);
        assertEquals(value, meta.get(key));
    }

    @Test
    public void testSetWithNotExistsKey() {
        DataMetadata meta = new DataMetadata();
        String key = "tensor_map_file";
        String value = INPUT_PATH.resolve("test.jsonl").toString();

        meta.set(key, value);
        assertEquals(value, meta.get(key));
    }

    @Test
    public void testSetWithEmptyKey() {
        DataMetadata meta = new DataMetadata();
        String key = "";
        String value = INPUT_PATH.resolve("test.jsonl").toString();
        meta.set(key, value);
        assertEquals(value, meta.get(key));
    }

    @Test
    public void testSetWithEmptyValue() {
        DataMetadata meta = new DataMetadata();
        String key = "tensor_map_file";
        String value = "";

        meta.set(key, value);
        assertEquals(value, meta.get(key));
    }

    @Test
    public void testToJsonString() throws JsonMappingException, JsonProcessingException {
        DataMetadata meta = new DataMetadata();
        String key1 = "tensor_map_file";
        String key2 = "tensor_map_index_file";
        String key3 = "save_result";
        String value1 = INPUT_PATH.resolve("test.jsonl").toString();
        String value2 = INPUT_PATH.resolve("test.txt").toString();
        String value3 = "success";
        meta.set(key1, value1);
        meta.set(key2, value2);
        meta.set(key3, value3);
        String json = meta.toJsonString();
        JsonNode jsonNode = new ObjectMapper().readTree(json);
        assertEquals(value1, jsonNode.get(key1).asText());
        assertEquals(value2, jsonNode.get(key2).asText());
        assertEquals(value3, jsonNode.get(key3).asText());
    }

    @Test
    public void testToJsonStringWithNothingSet() {
        DataMetadata meta = new DataMetadata();
        String json = meta.toJsonString();
        assertEquals("{}", json);
    }

    @Test
    public void testFromJsonString_FullMember() {
        String jsonString = "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Evaluation_Result.jsonl\",\"tensor_map_index_file\":\"/tmp/Evaluation_Result.txt\"}";
        DataMetadata meta = DataMetadata.fromJsonString(jsonString);

        assertEquals("success", meta.get("save_result"));
        assertEquals("/tmp/Evaluation_Result.jsonl", meta.get("tensor_map_file"));
        assertEquals("/tmp/Evaluation_Result.txt", meta.get("tensor_map_index_file"));
    }

    @Test
    public void testFromJsonString_NoSaveResult() {
        String jsonString = "{\"tensor_map_file\":\"/tmp/Evaluation_Result.jsonl\",\"tensor_map_index_file\":\"/tmp/Evaluation_Result.txt\"}";
        DataMetadata meta = DataMetadata.fromJsonString(jsonString);

        assertNull(meta.get("save_result"));
        assertEquals("/tmp/Evaluation_Result.jsonl", meta.get("tensor_map_file"));
        assertEquals("/tmp/Evaluation_Result.txt", meta.get("tensor_map_index_file"));
    }

    @Test
    public void testFromJsonString_ContainNumber() {
        String jsonString = "{\"text\":\"Text\",\"number\":123}";
        DataMetadata meta = DataMetadata.fromJsonString(jsonString);

        assertEquals("Text", meta.get("text"));
        assertNull(meta.get("number"));
    }

    @Test
    public void testFromJsonString_EmptyJson() {
        String jsonString = "{}";
        DataMetadata meta = DataMetadata.fromJsonString(jsonString);
        assertEquals(jsonString, meta.toJsonString());
    }
}
