/**
 * @file private_mib_module.h
 * @brief Private MIB module
 *
 * @section License
 *
 * Copyright (C) 2010-2016 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.2
 **/

#ifndef _PRIVATE_MIB_MODULE_H
#define _PRIVATE_MIB_MODULE_H

//Dependencies
#include "mibs/mib_common.h"

//Size of testString object
#define PRIVATE_MIB_TEST_STRING_SIZE 32
//Number of LEDs
#define PRIVATE_MIB_LED_COUNT 24
//Size of ledColor object
#define PRIVATE_MIB_LED_COLOR_SIZE 8


/**
 * @brief LED table entry
 **/

typedef struct
{
   char_t ledColor[PRIVATE_MIB_LED_COLOR_SIZE];
   size_t ledColorLen;
   int32_t ledState;
} PrivateMibLedEntry;


/**
 * @brief Private MIB base
 **/

typedef struct
{
   char_t testString[PRIVATE_MIB_TEST_STRING_SIZE];      //测试字符型的大小
   size_t testStringLen;                                //测试字符型的长度
   int32_t testInteger;                               //测试整型
   uint32_t currentTime;                             //当前时间值
   int32_t ledCount;                                   //LED数量
   PrivateMibLedEntry ledTable[PRIVATE_MIB_LED_COUNT];  //LED状态、颜色等
} PrivateMibBase;


//Private MIB related constants
extern PrivateMibBase privateMibBase;
extern const MibObject privateMibObjects[];
extern const MibModule privateMibModule;

#endif
