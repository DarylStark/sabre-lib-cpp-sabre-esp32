#include "factory.hpp"
#include "exceptions/exceptions.hpp"

namespace sabre::esp32
{
    sabre::UARTUniquePtr Factory::create_uart_object(uint32_t uart_number,
                                                     int32_t baud_rate,
                                                     int32_t tx_pin,
                                                     int32_t rx_pin) const
    {
        return std::make_unique<UART>(static_cast<uart_port_t>(uart_number),
                                      baud_rate, tx_pin, rx_pin);
    }

    sabre::InputGPIOUniquePtr Factory::create_input_gpio(int32_t pin) const
    {
        return std::make_unique<InputGPIO>(pin);
    }

    sabre::OutputGPIOUniquePtr Factory::create_output_gpio(int32_t pin) const
    {
        return std::make_unique<OutputGPIO>(pin);
    }

    sabre::WifiStationUniquePtr Factory::create_wifi_station() const
    {
        return std::make_unique<WifiStation>();
    }

    sabre::WifiSoftAPUniquePtr Factory::create_wifi_soft_ap() const
    {
        return std::make_unique<WifiSoftAP>();
    }

    sabre::MQTTClientUniquePtr Factory::create_mqtt_client() const
    {
        return std::make_unique<MQTTClient>();
    }

    sabre::WaitForUniquePtr Factory::create_wait_for(WaitForPred fn,
                                                     uint64_t timeout_in_ms,
                                                     uint64_t sleep_time) const
    {
        return std::make_unique<WaitFor>(fn, timeout_in_ms, sleep_time);
    }

    sabre::NTPClientUniquePtr
    Factory::create_ntp_client(const std::string &server) const
    {
        return std::make_unique<NTPClient>(server);
    }

    sabre::WallClockUniquePtr Factory::create_wall_clock() const
    {
        return std::make_unique<WallClock>();
    }

    sabre::ServiceUniquePtr Factory::create_service(ServiceHandler fn) const
    {
        return std::make_unique<Service>(fn);
    }
} // namespace sabre::esp32