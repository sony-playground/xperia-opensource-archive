#ifndef DATA_NORMALIZER_HPP_
#define DATA_NORMALIZER_HPP_
#include <vector>
#include <string>

class DataNormalizer {
private:

public:
    float normalize(float feature, float mean, float std);
    float log_normalize(float feature, float base, float mean, float std);
    float one_hot(int id, int pos);
    int itoid(int feature, std::vector<int> values);
    int btoid(bool feature);
    int stoid(std::string feature, std::vector<std::string> values);
    int test_itoid();
    int test_stoid();

    float normalize_inference_primary(float feature);
    float normalize_inference_secondary(float feature);
    float normalize_rssi(float feature);
    float normalize_integral_used_descriptor_in_driver(float feature);
    float normalize_ccabt_avg(float feature);
    float normalize_link_speed(float feature);
    float normalize_contention_average_time(float feature);
    float normalize_rx_pkt(float feature);
    float normalize_tx_pkt(float feature);
    float normalize_is_moving(float feature);
    float normalize_sensor_step_count(float feature);
    float normalize_band_id_1(float feature);
    float normalize_wifi_security_type_id_1(float feature);
    float normalize_wifi_security_type_id_2(float feature);
    float normalize_wifi_security_type_id_3(float feature);
    float normalize_wifi_security_type_id_4(float feature);
    float normalize_wifi_security_type_id_5(float feature);
    float normalize_wifi_security_type_id_6(float feature);
    float normalize_turned_off_on_before_id_1(float feature);

    bool normalize_all_features(int d_of_raw_data, int d_of_normalized_data, 
            float features[], float normalized_features[]);

    void test_normalize_band_id_1();
};

#endif  // DATA_NORMALIZER_HPP_
