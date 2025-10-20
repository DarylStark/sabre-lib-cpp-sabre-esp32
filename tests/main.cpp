#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>

class MyGlobalListener : public ::testing::EmptyTestEventListener
{
public:
    void OnTestStart(const ::testing::TestInfo &test_info) override
    {
        mockoc.clear();
        mock_mcu.clear();
    }
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners &listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new MyGlobalListener);
    return RUN_ALL_TESTS();
}