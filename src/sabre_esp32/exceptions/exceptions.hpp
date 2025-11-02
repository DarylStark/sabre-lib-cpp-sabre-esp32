#pragma once

#include <esp_err.h>
#include <sabre/exceptions/exceptions.hpp>

namespace sabre::esp32
{
    /**
     * @brief Exception class for ESP-IDF specific errors.
     *
     * This class inherits from `sabre::APIError` and is used to throw
     * exceptions for errors that occur in the ESP-IDF context.
     */
    class ESP_IDF_Error : public sabre::APIError
    {
    public:
        /**
         * @brief Default constructor for `ESP_IDF_Error`.
         *
         * Initializes the error with a default message.
         */
        ESP_IDF_Error(const std::string &s);
    };

    /**
     * @brief Throws an ESP_IDF_Error if the provided esp_err_t value is not
     * ESP_OK.
     *
     * @param err The esp_err_t value to check.
     * @param msg The error message to include in the exception if thrown.
     *
     * @throws `ESP_IDF_Error` if err is not `ESP_OK`.
     */
    void throw_if_esp_err(esp_err_t err, const std::string &msg);

    /**
     * @brief Throws an ESP_IDF_Error if the provided value is negative.
     *
     * @param value The integer value to check.
     * @param msg The error message to include in the exception if thrown.
     *
     * @throws ESP_IDF_Error if value is less than 0.
     */
    void throw_if_negative_value(int32_t value, const std::string &msg);

    /**
     * @brief Exception class for unsupported features on specific ESP32
     * targets.
     *
     * This class inherits from `sabre::APIError` and is used to throw
     * exceptions when a feature is not supported on the target ESP32 chip
     * (e.g., Wi-Fi on ESP32-H2).
     */
    class UnsupportedFeatureException : public sabre::APIError
    {
    public:
        /**
         * @brief Constructor for `UnsupportedFeatureException`.
         *
         * @param s The error message describing the unsupported feature.
         */
        UnsupportedFeatureException(const std::string &s);
    };
} // namespace sabre::esp32