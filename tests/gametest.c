#include "./Unity/src/unity.h"
#include "../main.h"



void test_inbounds(void)
{
//TEST_ASSERT_EQUAL_HEX8(40, AverageThreeBytes(30, 40, 50));
inBounds(0,0);


}



int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_inbounds);
//RUN_TEST(test_AverageThreeBytes_should_AverageHighValues);
return UNITY_END();
}