#include "exceptions.hpp"

namespace sabre::esp32
{
    ESP_IDF_Error::ESP_IDF_Error(const std::string &s) : APIError(s) {}

    void throw_if_esp_err(esp_err_t err, const std::string &msg)
    {
        if (err != ESP_OK)
            throw ESP_IDF_Error(msg);
    }

    void throw_if_negative_value(int32_t value, const std::string &msg)
    {
        if (value < 0)
            throw ESP_IDF_Error(msg);
    }

    UnsupportedFeatureException::UnsupportedFeatureException(
        const std::string &s)
        : APIError(s)
    {
    }
} // namespace sabre::esp32
