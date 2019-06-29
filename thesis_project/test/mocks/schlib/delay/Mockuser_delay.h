/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKUSER_DELAY_H
#define _MOCKUSER_DELAY_H

#include "unity.h"
#include "lib/delay/user_delay.h"
#include "CException.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mockuser_delay_Init(void);
void Mockuser_delay_Destroy(void);
void Mockuser_delay_Verify(void);




#define user_delay_ms_Ignore() user_delay_ms_CMockIgnore()
void user_delay_ms_CMockIgnore(void);
#define user_delay_ms_ExpectAnyArgs() user_delay_ms_CMockExpectAnyArgs(__LINE__)
void user_delay_ms_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define user_delay_ms_Expect(period) user_delay_ms_CMockExpect(__LINE__, period)
void user_delay_ms_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32_t period);
typedef void (* CMOCK_user_delay_ms_CALLBACK)(uint32_t period, int cmock_num_calls);
void user_delay_ms_StubWithCallback(CMOCK_user_delay_ms_CALLBACK Callback);
#define user_delay_ms_ExpectAndThrow(period, cmock_to_throw) user_delay_ms_CMockExpectAndThrow(__LINE__, period, cmock_to_throw)
void user_delay_ms_CMockExpectAndThrow(UNITY_LINE_TYPE cmock_line, uint32_t period, CEXCEPTION_T cmock_to_throw);
#define user_delay_ms_IgnoreArg_period() user_delay_ms_CMockIgnoreArg_period(__LINE__)
void user_delay_ms_CMockIgnoreArg_period(UNITY_LINE_TYPE cmock_line);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif