#ifndef SABRE_ESP32_CLIENTS_NTP_HPP
#define SABRE_ESP32_CLIENTS_NTP_HPP

#include <sabre/clients/ntp.hpp>
#include <string>

namespace sabre::esp32
{
    class NTPClient : public sabre::NTPClient
    {
    private:
        std::string _server;

    public:
        /**
         * @brief Constructs the NTPClient object.
         *
         * @param server The NTP server to use.
         */
        NTPClient(const std::string &server);

        /**
         * @brief Destructs the NTPClient object.
         *
         * This will stop the NTP client if it is running.
         */
        ~NTPClient();

        /**
         * @brief Starts the NTP client.
         *
         * This will initialize the NTP client and start synchronizing time
         * with the specified NTP server.
         */
        void start() override;

        /**
         * @brief Stops the NTP client.
         *
         * This will stop the NTP client and cease time synchronization.
         */
        void stop() override;

        /**
         * @brief Checks if the NTP client is synchronized.
         *
         * @returns true if the NTP client is synchronized, false otherwise.
         */
        bool is_synchronized() const override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_CLIENTS_NTP_HPP