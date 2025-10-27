#ifndef SABRE_ESP32_FACTORY_H
#define SABRE_ESP32_FACTORY_H

#include "clients/mqtt.hpp"
#include "clients/ntp.hpp"
#include "gpio/input_gpio.hpp"
#include "gpio/output_gpio.hpp"
#include "service/service.hpp"
#include "system/wall_clock.hpp"
#include "uart/uart.hpp"
#include "utility/wait_for.hpp"
#include "wifi/wifi_soft_ap.hpp"
#include "wifi/wifi_station.hpp"
#include <map>
#include <memory>
#include <sabre/factory.hpp>

namespace sabre::esp32
{
    /**
     * @brief Factory class for creating ESP32-specific objects.
     *
     * This class implements the sabre::Factory interface and provides methods
     * to create various ESP32-specific objects such as UART, GPIO, Wi-Fi
     * Station, Wi-Fi Soft AP, MQTT Client, and WaitFor.
     */
    class Factory : public sabre::Factory
    {
    private:
        std::map<uint16_t, std::unique_ptr<std::ostream>> _output_streams;

    public:
        /**
         * @brief Create a UART object for the specified UART number.
         *
         * @param uart_number The UART number to configure the object with.
         * @param baud_rate The baud rate for the serial interface.
         * @param tx_pin Transmit pin.
         * @param rx_pin Receive pin.
         *
         * @returns A UARTUniquePtr shared pointer to a UART object.
         */
        sabre::UARTUniquePtr create_uart_object(uint32_t uart_number,
                                                int32_t baud_rate,
                                                int32_t tx_pin,
                                                int32_t rx_pin) const override;

        /**
         * @brief Create a a InputGPIO object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @returns A InputGPIOUniquePtr shared pointer to a InputGPIO object.
         */
        sabre::InputGPIOUniquePtr create_input_gpio(int32_t pin) const override;

        /**
         * @brief Create a OutputGPIO object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @returns A OutputGPIOUniquePtr shared pointer to a OutputGPIO object.
         */
        sabre::OutputGPIOUniquePtr
        create_output_gpio(int32_t pin) const override;

        /**
         * @brief Create a Wi-Fi Station object.
         *
         * @returns A WifiStationUniquePtr shared pointer to a WifiStation
         * object.
         */
        sabre::WifiStationUniquePtr create_wifi_station() const override;

        /**
         * @brief Create a Wi-Fi Soft AP object.
         *
         * @returns A WifiSoftAPUniquePtr shared pointer to a WifiSoftAP object.
         */
        sabre::WifiSoftAPUniquePtr create_wifi_soft_ap() const override;

        /**
         * @brief Create a MQTT Client object.
         *
         * @returns A MQTTClientUniquePtr shared pointer to a MQTTClient object.
         */
        sabre::MQTTClientUniquePtr create_mqtt_client() const override;

        /**
         * @brief Create a WaitFor object.
         *
         * @param fn The predicate function to check.
         * @param timeout_in_ms The maximum time to wait in milliseconds.
         * @param sleep_time The time to sleep between checks in milliseconds.
         *
         * @returns A WaitForUniquePtr shared pointer to a WaitFor object.
         */
        sabre::WaitForUniquePtr
        create_wait_for(WaitForPred fn, uint64_t timeout_in_ms,
                        uint64_t sleep_time) const override;

        /**
         * @brief Create a `NTPClient` object.
         *
         * @param server the NTP server to use.
         *
         * @returns A `NTPClientUniquePtr` shared pointer to a `NTPClient`.
         */
        sabre::NTPClientUniquePtr
        create_ntp_client(const std::string &server) const override;

        /**
         * @brief Create a `WallClock` object.
         *
         * @return A `WallClockUniquePtr` shared pointer to a `WallClock`
         * object.
         */
        sabre::WallClockUniquePtr create_wall_clock() const override;

        /**
         * @brief Create a `Service` object.
         *
         * @param fn the function to run as the service.
         *
         * @return A `ServiceUniquePtr` shared pointer to a `Service`
         * object.
         */
        sabre::ServiceUniquePtr
        create_service(ServiceHandler fn) const override;
    };
} // namespace sabre::esp32

#endif /* SABRE_ESP32_FACTORY_H */