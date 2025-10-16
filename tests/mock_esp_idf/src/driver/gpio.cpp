#include "../../include/driver/gpio.h"
#include <mockoc.hpp>

esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
{
    return mock_call(
        "gpio_set_level",
        [](gpio_num_t gpio_num, uint32_t level) { return ESP_OK; }, gpio_num,
        level);
}

int gpio_get_level(gpio_num_t gpio_num)
{
    return mock_call(
        "gpio_get_level", [](gpio_num_t gpio_num) { return 1; }, gpio_num);
}

esp_err_t gpio_install_isr_service(int intr_alloc_flags)
{
    return mock_call(
        "gpio_install_isr_service", [](int intr_alloc_flags) { return ESP_OK; },
        intr_alloc_flags);
}

esp_err_t gpio_isr_handler_add(gpio_num_t gpio_num, gpio_isr_t isr_handler,
                               void *args)
{
    return mock_call(
        "gpio_isr_handler_add",
        [](gpio_num_t gpio_num, gpio_isr_t isr_handler, void *args)
        { return ESP_OK; },
        gpio_num, isr_handler, args);
}

esp_err_t gpio_pulldown_dis(gpio_num_t gpio_num)
{
    return mock_call(
        "gpio_pulldown_dis", [](gpio_num_t gpio_num) { return ESP_OK; },
        gpio_num);
}

esp_err_t gpio_pulldown_en(gpio_num_t gpio_num)
{
    return mock_call(
        "gpio_pulldown_en", [](gpio_num_t gpio_num) { return ESP_OK; },
        gpio_num);
}

esp_err_t gpio_pullup_dis(gpio_num_t gpio_num)
{
    return mock_call(
        "gpio_pullup_dis", [](gpio_num_t gpio_num) { return ESP_OK; },
        gpio_num);
}

esp_err_t gpio_pullup_en(gpio_num_t gpio_num)
{
    return mock_call(
        "gpio_pullup_en", [](gpio_num_t gpio_num) { return ESP_OK; }, gpio_num);
}

esp_err_t gpio_set_intr_type(gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
    return mock_call(
        "gpio_set_intr_type",
        [](gpio_num_t gpio_num, gpio_int_type_t intr_type) { return ESP_OK; },
        gpio_num, intr_type);
}

esp_err_t gpio_reset_pin(gpio_num_t gpio_num)
{
    return mock_call(
        "gpio_reset_pin", [](gpio_num_t gpio_num) { return ESP_OK; }, gpio_num);
}

esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode)
{
    return mock_call(
        "gpio_set_direction",
        [](gpio_num_t gpio_num, gpio_mode_t mode) { return ESP_OK; }, gpio_num,
        mode);
}