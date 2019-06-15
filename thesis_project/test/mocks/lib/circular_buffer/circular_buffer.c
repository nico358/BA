/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "circular_buffer.h"

static const char* CMockString_c = "c";
static const char* CMockString_circBufCount = "circBufCount";
static const char* CMockString_circBufCountObjects = "circBufCountObjects";
static const char* CMockString_circBufFree = "circBufFree";
static const char* CMockString_circBufInit = "circBufInit";
static const char* CMockString_circBufPop = "circBufPop";
static const char* CMockString_circBufPush = "circBufPush";
static const char* CMockString_circBufSpace = "circBufSpace";
static const char* CMockString_data = "data";
static const char* CMockString_size = "size";


typedef struct _CMOCK_circBufInit_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  circularBufferMock* Expected_c;
  uint16_t Expected_size;

} CMOCK_circBufInit_CALL_INSTANCE;

typedef struct _CMOCK_circBufFree_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  circularBufferMock* Expected_c;

} CMOCK_circBufFree_CALL_INSTANCE;

typedef struct _CMOCK_circBufSpace_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint16_t ReturnVal;
  circularBufferMock* Expected_c;

} CMOCK_circBufSpace_CALL_INSTANCE;

typedef struct _CMOCK_circBufCount_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint16_t ReturnVal;
  circularBufferMock* Expected_c;

} CMOCK_circBufCount_CALL_INSTANCE;

typedef struct _CMOCK_circBufCountObjects_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint16_t ReturnVal;
  circularBufferMock* Expected_c;
  uint16_t Expected_size;

} CMOCK_circBufCountObjects_CALL_INSTANCE;

typedef struct _CMOCK_circBufPush_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint8_t ReturnVal;
  circularBufferMock* Expected_c;
  uint8_t Expected_data;

} CMOCK_circBufPush_CALL_INSTANCE;

typedef struct _CMOCK_circBufPop_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint8_t ReturnVal;
  circularBufferMock* Expected_c;
  uint8_t* Expected_data;

} CMOCK_circBufPop_CALL_INSTANCE;

static struct Mockcircular_bufferInstance
{
  CMOCK_MEM_INDEX_TYPE circBufInit_CallInstance;
  CMOCK_MEM_INDEX_TYPE circBufFree_CallInstance;
  CMOCK_MEM_INDEX_TYPE circBufSpace_CallInstance;
  CMOCK_MEM_INDEX_TYPE circBufCount_CallInstance;
  CMOCK_MEM_INDEX_TYPE circBufCountObjects_CallInstance;
  CMOCK_MEM_INDEX_TYPE circBufPush_CallInstance;
  CMOCK_MEM_INDEX_TYPE circBufPop_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void Mockcircular_buffer_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_circBufInit);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufInit_CallInstance, cmock_line, CMockStringCalledLess);
  UNITY_SET_DETAIL(CMockString_circBufFree);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufFree_CallInstance, cmock_line, CMockStringCalledLess);
  UNITY_SET_DETAIL(CMockString_circBufSpace);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufSpace_CallInstance, cmock_line, CMockStringCalledLess);
  UNITY_SET_DETAIL(CMockString_circBufCount);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufCount_CallInstance, cmock_line, CMockStringCalledLess);
  UNITY_SET_DETAIL(CMockString_circBufCountObjects);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufCountObjects_CallInstance, cmock_line, CMockStringCalledLess);
  UNITY_SET_DETAIL(CMockString_circBufPush);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufPush_CallInstance, cmock_line, CMockStringCalledLess);
  UNITY_SET_DETAIL(CMockString_circBufPop);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.circBufPop_CallInstance, cmock_line, CMockStringCalledLess);
}

void Mockcircular_buffer_Init(void)
{
  Mockcircular_buffer_Destroy();
}

void Mockcircular_buffer_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

void circBufInit(circularBufferMock* c, uint16_t size)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufInit_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufInit);
  cmock_call_instance = (CMOCK_circBufInit_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufInit_CallInstance);
  Mock.circBufInit_CallInstance = CMock_Guts_MemNext(Mock.circBufInit_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufInit,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_circBufInit,CMockString_size);
    UNITY_TEST_ASSERT_EQUAL_HEX16(cmock_call_instance->Expected_size, size, cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_circBufInit(CMOCK_circBufInit_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c, uint16_t size)
{
  cmock_call_instance->Expected_c = c;
  cmock_call_instance->Expected_size = size;
}

void circBufInit_CMockExpect(UNITY_LINE_TYPE cmock_line, circularBufferMock* c, uint16_t size)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufInit_CALL_INSTANCE));
  CMOCK_circBufInit_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufInit_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufInit_CallInstance = CMock_Guts_MemChain(Mock.circBufInit_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufInit(cmock_call_instance, c, size);
  UNITY_CLR_DETAILS();
}

void circBufFree(circularBufferMock* c)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufFree_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufFree);
  cmock_call_instance = (CMOCK_circBufFree_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufFree_CallInstance);
  Mock.circBufFree_CallInstance = CMock_Guts_MemNext(Mock.circBufFree_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufFree,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_circBufFree(CMOCK_circBufFree_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c)
{
  cmock_call_instance->Expected_c = c;
}

void circBufFree_CMockExpect(UNITY_LINE_TYPE cmock_line, circularBufferMock* c)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufFree_CALL_INSTANCE));
  CMOCK_circBufFree_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufFree_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufFree_CallInstance = CMock_Guts_MemChain(Mock.circBufFree_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufFree(cmock_call_instance, c);
  UNITY_CLR_DETAILS();
}

uint16_t circBufSpace(circularBufferMock* c)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufSpace_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufSpace);
  cmock_call_instance = (CMOCK_circBufSpace_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufSpace_CallInstance);
  Mock.circBufSpace_CallInstance = CMock_Guts_MemNext(Mock.circBufSpace_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufSpace,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_circBufSpace(CMOCK_circBufSpace_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c)
{
  cmock_call_instance->Expected_c = c;
}

void circBufSpace_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, circularBufferMock* c, uint16_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufSpace_CALL_INSTANCE));
  CMOCK_circBufSpace_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufSpace_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufSpace_CallInstance = CMock_Guts_MemChain(Mock.circBufSpace_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufSpace(cmock_call_instance, c);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

uint16_t circBufCount(circularBufferMock* c)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufCount_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufCount);
  cmock_call_instance = (CMOCK_circBufCount_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufCount_CallInstance);
  Mock.circBufCount_CallInstance = CMock_Guts_MemNext(Mock.circBufCount_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufCount,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_circBufCount(CMOCK_circBufCount_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c)
{
  cmock_call_instance->Expected_c = c;
}

void circBufCount_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, circularBufferMock* c, uint16_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufCount_CALL_INSTANCE));
  CMOCK_circBufCount_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufCount_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufCount_CallInstance = CMock_Guts_MemChain(Mock.circBufCount_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufCount(cmock_call_instance, c);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

uint16_t circBufCountObjects(circularBufferMock* c, uint16_t size)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufCountObjects_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufCountObjects);
  cmock_call_instance = (CMOCK_circBufCountObjects_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufCountObjects_CallInstance);
  Mock.circBufCountObjects_CallInstance = CMock_Guts_MemNext(Mock.circBufCountObjects_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufCountObjects,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_circBufCountObjects,CMockString_size);
    UNITY_TEST_ASSERT_EQUAL_HEX16(cmock_call_instance->Expected_size, size, cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_circBufCountObjects(CMOCK_circBufCountObjects_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c, uint16_t size)
{
  cmock_call_instance->Expected_c = c;
  cmock_call_instance->Expected_size = size;
}

void circBufCountObjects_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, circularBufferMock* c, uint16_t size, uint16_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufCountObjects_CALL_INSTANCE));
  CMOCK_circBufCountObjects_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufCountObjects_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufCountObjects_CallInstance = CMock_Guts_MemChain(Mock.circBufCountObjects_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufCountObjects(cmock_call_instance, c, size);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

uint8_t circBufPush(circularBufferMock* c, uint8_t data)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufPush_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufPush);
  cmock_call_instance = (CMOCK_circBufPush_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufPush_CallInstance);
  Mock.circBufPush_CallInstance = CMock_Guts_MemNext(Mock.circBufPush_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufPush,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_circBufPush,CMockString_data);
    UNITY_TEST_ASSERT_EQUAL_HEX8(cmock_call_instance->Expected_data, data, cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_circBufPush(CMOCK_circBufPush_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c, uint8_t data)
{
  cmock_call_instance->Expected_c = c;
  cmock_call_instance->Expected_data = data;
}

void circBufPush_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, circularBufferMock* c, uint8_t data, uint8_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufPush_CALL_INSTANCE));
  CMOCK_circBufPush_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufPush_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufPush_CallInstance = CMock_Guts_MemChain(Mock.circBufPush_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufPush(cmock_call_instance, c, data);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

uint8_t circBufPop(circularBufferMock* c, uint8_t* data)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_circBufPop_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_circBufPop);
  cmock_call_instance = (CMOCK_circBufPop_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.circBufPop_CallInstance);
  Mock.circBufPop_CallInstance = CMock_Guts_MemNext(Mock.circBufPop_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_circBufPop,CMockString_c);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_c), (void*)(c), sizeof(circularBufferMock), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_circBufPop,CMockString_data);
    if (cmock_call_instance->Expected_data == NULL)
      { UNITY_TEST_ASSERT_NULL(data, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(cmock_call_instance->Expected_data, data, 1, cmock_line, CMockStringMismatch); }
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_circBufPop(CMOCK_circBufPop_CALL_INSTANCE* cmock_call_instance, circularBufferMock* c, uint8_t* data)
{
  cmock_call_instance->Expected_c = c;
  cmock_call_instance->Expected_data = data;
}

void circBufPop_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, circularBufferMock* c, uint8_t* data, uint8_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_circBufPop_CALL_INSTANCE));
  CMOCK_circBufPop_CALL_INSTANCE* cmock_call_instance = (CMOCK_circBufPop_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.circBufPop_CallInstance = CMock_Guts_MemChain(Mock.circBufPop_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_circBufPop(cmock_call_instance, c, data);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

