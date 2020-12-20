#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t UINTPTR;
typedef int s32;
//typedef int s16;

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)


//void Xil_Out32(UINTPTR Addr, u32 Value);
//u64 Xil_In32(UINTPTR Addr);

#define Xil_In32(Addr)  *(volatile u32*)(Addr)
#define Xil_Out32(Addr, Value)  *(volatile u32*)((Addr)) = (u32)(Value)

//#define TRUE 1
//#define FALSE 0

//#define XST_SUCCESS             0
//#define XST_FAILURE             -1
//#define XST_DEVICE_NOT_FOUND    2
//#define XST_INVALID_PARAM       -2
//#define XST_OPEN_DEVICE_FAILED  3
//#define XIL_COMPONENT_IS_READY  1


#ifdef __cplusplus
}
#endif

#endif


