/*******************************************************************************
	Filename:       SaBLExAPITypes
	Revised:        05.07.2017 18:44:06
	Revision:       1.0

	Description:    This file contains the SaBLE-x definitions

	Copyright 2017 LS Research, LLC (LSR). All rights reserved.

	IMPORTANT: Your use of this Software is limited to those specific rights
	granted under the terms of a software license agreement between the user
	who downloaded the software, his/her employer (which must be your employer)
	and LSR (the "License").  You may not use this
	Software unless you agree to abide by the terms of the License. The License
	limits your use, and you acknowledge, that the Software may not be modified,
	copied or distributed unless embedded on a Texas Instruments microcontroller
	or used solely and exclusively in conjunction with a LSR radio
	frequency transceiver, which is integrated into your product.  Other than for
	the foregoing purpose, you may not use, reproduce, copy, prepare derivative
	works of, modify, distribute, perform, display or sell this Software and/or
	its documentation for any purpose.

	YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
	PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
	INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
	NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
	TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
	NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
	LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
	INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
	OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
	OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
	(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

	Should you have any questions regarding your right to use this Software,
	contact LSR at www.lsr.com.
*******************************************************************************/

#ifndef SABLEXAPITYPES_H
#define SABLEXAPITYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#pragma pack(1)
typedef struct s_ByteStruct
{
		unsigned bit0: 1;
		unsigned bit1: 1;
		unsigned bit2: 1;
		unsigned bit3: 1;
		unsigned bit4: 1;
		unsigned bit5: 1;
		unsigned bit6: 1;
		unsigned bit7: 1;
} ByteStruct_t;

typedef union u_u8Union
{
		uint8_t			u8;
		ByteStruct_t			u8Struct;
} u8Union_t;
typedef union u_s8Union
{
		int8_t			s8;
		ByteStruct_t			s8Struct;
} s8Union_t;
#pragma pack()

typedef struct s_u16Struct
{
		u8Union_t			lb;
		u8Union_t			hb;
} u16Struct_t;

typedef struct s_s16Struct
{
		s8Union_t			lb;
		s8Union_t			hb;
} s16Struct_t;

typedef union u_u16Union
{
		uint16_t			u16;
		u16Struct_t			u16Struct;
} u16Union_t;

typedef union u_s16Union
{
		int16_t			s16;
		s16Struct_t			s16Struct;
} s16Union_t;

typedef struct s_u32Struct
{
		u8Union_t			lb;
		u8Union_t			mlb;
		u8Union_t			mhb;
		u8Union_t			hb;
} u32Struct_t;

typedef struct s_s32Struct
{
		s8Union_t			lb;
		s8Union_t			mlb;
		s8Union_t			mhb;
		s8Union_t			hb;
} s32Struct_t;

typedef union u_u32Union
{
		uint32_t			u32;
		u32Struct_t			u32Struct;
} u32Union_t;

typedef union u_s32Union
{
		int32_t			s32;
		s32Struct_t			s32Struct;
} s32Union_t;


#ifdef __cplusplus
}
#endif

#endif /*SABLEXAPITYPES_H*/
