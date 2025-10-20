#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/clients/ntp.hpp>

class NTPClientTest : public ::testing::Test
{
protected:
    sabre::esp32::NTPClient _ntp_client{"pool.ntp.org"};
};

TEST_F(NTPClientTest, StartNTPClient)
{
    _ntp_client.start();
    mockoc.was_called("esp_sntp_setservername");
    mockoc.was_called("esp_sntp_init");
}

TEST_F(NTPClientTest, StopNTPClient)
{
    _ntp_client.stop();
    mockoc.was_called("esp_sntp_stop");
}

TEST_F(NTPClientTest, IsSynchronizedFalse)
{
    ASSERT_FALSE(_ntp_client.is_synchronized());
}

TEST_F(NTPClientTest, IsSynchronizedTrue)
{
    mock_mcu.set_time_synced(true);
    ASSERT_TRUE(_ntp_client.is_synchronized());
}

TEST_F(NTPClientTest, IsStoppedInDestructor)
{
    // Check if the destructor calls stop()
    {
        sabre::esp32::NTPClient ntp_client{"time.nist.gov"};
    }
    ASSERT_TRUE(mockoc.was_called("esp_sntp_stop"));
}