#include <gtest/gtest.h>
#include <sabre_esp32/exceptions/exceptions.hpp>

TEST(ExceptionTest, ESPIDFErrorThrow)
{
    EXPECT_THROW(sabre::esp32::throw_if_esp_err(ESP_FAIL, "ESP Error occurred"),
                 sabre::esp32::ESP_IDF_Error);
}

TEST(ExceptionTest, ESPIDFErrorNoThrow)
{
    EXPECT_NO_THROW(sabre::esp32::throw_if_esp_err(ESP_OK, "No error"));
}

TEST(ExceptionTest, NegativeValueThrow)
{
    EXPECT_THROW(
        sabre::esp32::throw_if_negative_value(-1, "Negative value error"),
        sabre::esp32::ESP_IDF_Error);
}

TEST(ExceptionTest, NegativeValueNoThrow)
{
    EXPECT_NO_THROW(sabre::esp32::throw_if_negative_value(10, "No error"));
}