#include <math.h>

#include "NNHLCR/data_normalizer.h"

float DataNormalizer::normalize(float feature, float mean, float std) {
    return (feature - mean) / std;
}

float DataNormalizer::log_normalize(float feature, float base, float mean, float std) {
    float log_feature = log(feature + base);
    return normalize(log_feature, mean, std);
}

float DataNormalizer::one_hot(int id, int pos) {
    if (id == pos)
        return 1;
    else
        return 0;
}

int DataNormalizer::itoid(int feature, std::vector<int> values) {
    for (int id = 0; id < (int)values.size(); id++) {
        if (feature == values[id]) {
            return id;
        }
    }
    return 0;
}

int DataNormalizer::btoid(bool feature) {
    if (feature) {
        return 1;
    }

    return 0;
}

int DataNormalizer::stoid(std::string feature, std::vector<std::string> values) {
    for(int id = 0; id < (int)values.size(); id++) {
        if (feature == values[id]) {
            return id;
        }
    }

    return 0;
}

int DataNormalizer::test_itoid() {
    int id = itoid(30, {10, 20, 30});
#ifdef DEBUG
    printf("result of itoid: %d\n", id);
#endif
    return id;
}

int DataNormalizer::test_stoid() {
    int id = stoid("bbb", {"aaa", "bbb", "ccc"});
#ifdef DEBUG
    printf("result of stoid: %d\n", id);
#endif
    return id;
}

float DataNormalizer::normalize_inference_primary(float feature) {
    return log_normalize(feature, 0.0001, -5.244569, 2.730395);
}

float DataNormalizer::normalize_inference_secondary(float feature) {
    return log_normalize(feature, 0.0001, -6.025045, 3.183082);
}

float DataNormalizer::normalize_rssi(float feature) {
    return normalize(feature, -71.334244, 9.558289);
}

float DataNormalizer::normalize_integral_used_descriptor_in_driver(float feature) {
    return log_normalize(feature, 2.0, 4.391474, 3.160911);
}

float DataNormalizer::normalize_ccabt_avg(float feature) {
    return log_normalize(feature, 0.01, -2.364670, 1.212559);
}

float DataNormalizer::normalize_link_speed(float feature) {
    return log_normalize(feature, 0.0, 3.609188, 1.504258);
}

float DataNormalizer::normalize_contention_average_time(float feature) {
    return log_normalize(feature, 1.0, 6.210528, 1.673166);
}

float DataNormalizer::normalize_rx_pkt(float feature) {
    return log_normalize(feature, 1.0, 2.201363, 2.157463);
}

float DataNormalizer::normalize_tx_pkt(float feature) {
    return log_normalize(feature, 1.0, 2.192953, 1.975420);
}

float DataNormalizer::normalize_is_moving(float feature) {
    int id = btoid((bool)feature);
    return one_hot(id, 1);
}

float DataNormalizer::normalize_sensor_step_count(float feature) {
    return log_normalize(feature, 1.0, 0.232431, 0.633336);
}

float DataNormalizer::normalize_band_id_1(float feature) {
    //int id = stoid(feature, {"2.4Ghz", "5GHz"});
    int id = btoid((bool)feature);
    return one_hot(id, 1);
}

float DataNormalizer::normalize_wifi_security_type_id_1(float feature) {
    int id = itoid((int)feature, {-1, 0, 1, 2, 3, 4, 6});
    return one_hot(id, 1);
}

float DataNormalizer::normalize_wifi_security_type_id_2(float feature) {
    int id = itoid((int)feature, {-1, 0, 1, 2, 3, 4, 6});
    return one_hot(id, 2);
}

float DataNormalizer::normalize_wifi_security_type_id_3(float feature) {
    int id = itoid((int)feature, {-1, 0, 1, 2, 3, 4, 6});
    return one_hot(id, 3);
}

float DataNormalizer::normalize_wifi_security_type_id_4(float feature) {
    int id = itoid((int)feature, {-1, 0, 1, 2, 3, 4, 6});
    return one_hot(id, 4);
}

float DataNormalizer::normalize_wifi_security_type_id_5(float feature) {
    int id = itoid((int)feature, {-1, 0, 1, 2, 3, 4, 6});
    return one_hot(id, 5);
}

float DataNormalizer::normalize_wifi_security_type_id_6(float feature) {
    int id = itoid((int)feature, {-1, 0, 1, 2, 3, 4, 6});
    return one_hot(id, 6);
}

float DataNormalizer::normalize_turned_off_on_before_id_1(float feature) {
    int id = btoid((bool)feature);
    return one_hot(id, 1);
}

bool DataNormalizer::normalize_all_features(int d_of_raw_data, int d_of_normalized_data, 
        float features[], float normalized_features[]) {
    if (d_of_raw_data != 13) {
        return false;
    }
    if (d_of_normalized_data != 18) {
        return false;
    }
    normalized_features[0] = normalize_inference_primary(features[0]);
    normalized_features[1] = normalize_inference_secondary(features[1]);
    normalized_features[2] = normalize_rssi(features[2]);
    normalized_features[3] = normalize_integral_used_descriptor_in_driver(features[3]);
    normalized_features[4] = normalize_ccabt_avg(features[4]);
    normalized_features[5] = normalize_link_speed(features[5]);
    normalized_features[6] = normalize_contention_average_time(features[6]);
    normalized_features[7] = normalize_rx_pkt(features[7]);
    normalized_features[8] = normalize_tx_pkt(features[8]);
    normalized_features[9] = normalize_is_moving(features[9]);
    //normalized_features[10] = normalize_sensor_step_count(features[10]);
    normalized_features[10] = normalize_band_id_1(features[10]);
    normalized_features[11] = normalize_wifi_security_type_id_1(features[11]);
    normalized_features[12] = normalize_wifi_security_type_id_2(features[11]);
    normalized_features[13] = normalize_wifi_security_type_id_3(features[11]);
    normalized_features[14] = normalize_wifi_security_type_id_4(features[11]);
    normalized_features[15] = normalize_wifi_security_type_id_5(features[11]);
    normalized_features[16] = normalize_wifi_security_type_id_6(features[11]);
    normalized_features[17] = normalize_turned_off_on_before_id_1(features[12]);
    return true;
}

void DataNormalizer::test_normalize_band_id_1() {
    //std::string feature("2.4Ghz");
    //float f = normalize_band_id_1("5GHz");
    //printf("return of normalize_band_id_1: %f\n", f);
}
