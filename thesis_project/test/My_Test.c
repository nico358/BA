#include "unity.h"
#include "lib/sensor-adapter/sensor_adapter.h"

void
test_shouldPass(void)
{
  int a = add(1,2);
  TEST_ASSERT_EQUAL(3,a);

}

void
test_shouldFail(void)
{
  TEST_ASSERT_EQUAL(12, add(4,8));
}

