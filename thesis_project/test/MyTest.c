//#include "unity.h"
#include "BazelTemplate/Functions.h"

void
test_shouldPass(void)
{
  TEST_ASSERT_EQUAL(5, add(3,2));
}

void
test_shouldFail(void)
{
  TEST_ASSERT_EQUAL(12, add(4,3));
}