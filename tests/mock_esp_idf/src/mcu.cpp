#include "mock_mcu.hpp"

/*
This translation unit is needed to instantiate the global gpio_state object that
will be used by the mock functions to talk to a "MCU".
*/

MockMCUConfiguration mock_mcu_config = {
    .gpio_count = 40 // Example GPIO count for ESP32
};
MockMCU mock_mcu(mock_mcu_config);