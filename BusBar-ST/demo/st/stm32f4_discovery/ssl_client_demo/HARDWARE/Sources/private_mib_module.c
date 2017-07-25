/**
 * @file private_mib_module.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL SNMP_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "mibs/mib_common.h"
#include "private_mib_module.h"
#include "private_mib_impl.h"
#include "crypto.h"
#include "asn1.h"
#include "oid.h"
#include "debug.h"


/**
 * @brief Private MIB base  ˽��MIB��
 **/

PrivateMibBase privateMibBase;


/**
 * @brief Private MIB objects  ˽��MIB����
 **/
 
// struct _MibObject
//{
//   const char_t *name;
//   uint8_t oid[MIB_MAX_OID_SIZE];
//   size_t oidLen;
//   uint_t class;
//   uint_t type;
//   MibAccess access;
//   void *value;
//   size_t *valueLen;
//   size_t valueSize;
//   MibSetValue setValue;
//   MibGetValue getValue;
//   MibGetNext getNext;
//};

const MibObject privateMibObjects[] =
{
   //testString object (1.3.6.1.4.1.8072.30966.10.2)
   {
      "deviceinfo",                                            //����
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 1, 1},        // OID
      12,                                                    // OID����
      ASN1_CLASS_UNIVERSAL,                                 //ASN.1 class
      ASN1_TYPE_OCTET_STRING,                              //����ģʽ  ----STRING���ַ�����ʽ         00     //devicename
      MIB_ACCESS_READ_WRITE,                                 //��дģʽ
      NULL,                          
      NULL,                     
      sizeof(int32_t),                     
      NULL,
      privateMibGetLedEntry,
      NULL
   },	
   //testString object (1.3.6.1.4.1.8072.30966.10.2)
   {
      "deviceinfo",                                            //����
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 1, 2},        // OID                        01   //ser
      12,                                                    // OID����
      ASN1_CLASS_UNIVERSAL,                                 //ASN.1 class
      ASN1_TYPE_INTEGER,                                     //����ģʽ  
      MIB_ACCESS_READ_WRITE,                                 //��дģʽ
      NULL,                          
      NULL,                     
      sizeof(int32_t),                     
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },	
   //testString object (1.3.6.1.4.1.8072.30966.10.2)
   {
      "deviceinfo",                                            //����
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 1, 3},        // OID                      02
      12,                                                    // OID����
      ASN1_CLASS_UNIVERSAL,                                 //ASN.1 class              //������
      ASN1_TYPE_INTEGER,                                    //����ģʽ  
      MIB_ACCESS_READ_WRITE,                                 //��дģʽ
      NULL,                          
      NULL,                     
      sizeof(int32_t),                     
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },	
   //testString object (1.3.6.1.4.1.8072.30966.10.2)
   {
      "deviceinfo",                                            //����
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 1, 4},        // OID                      03
      12,                                                    // OID����
      ASN1_CLASS_UNIVERSAL,                                 //ASN.1 class              //������
      ASN1_TYPE_INTEGER,                                    //����ģʽ  
      MIB_ACCESS_READ_WRITE,                                 //��дģʽ
      NULL,                          
      NULL,                     
      sizeof(int32_t),                     
      NULL,
      privateMibGetLedEntry,
      NULL
   },		 
   //testString object (1.3.6.1.4.1.8072.30966.10.2)            total    5
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 1},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ  ��ѹA         04
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   //testString object (1.3.6.1.4.1.8072.30966.10.2)
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 2},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ     ��ѹB            05
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 3},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ   ��ѹC           06
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 4},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ   ����A    07
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },	
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 5},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ    ����B    08
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 6},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ    ����C    09
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },	 
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 7},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ  ����A    10
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 8},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ    ����B    11
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 9},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ     ����C    12
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },	 
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 10},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ    ����A    13
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 11},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ    ����B    14
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 12},
      12,
      ASN1_CLASS_UNIVERSAL, 
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ        ����C    15
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },		
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 13},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //�¶�   16
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "ElectricParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 14},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //ʪ��   17
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 1},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L1��ѹ����ֵ  18
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 2},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L1��ѹ����ֵ  19
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 3},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L2��ѹ����ֵ  20
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 4},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L2��ѹ����ֵ  21
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 5},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L3��ѹ����ֵ  22
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 6},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L3��ѹ����ֵ  23
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 7},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L1��������ֵ  24
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 8},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L1��������ֵ  25
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 9},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L2��������ֵ  26
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 10},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L2��������ֵ  27
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 11},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L3��������ֵ  28
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "SettingParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 3, 12},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L3��������ֵ  29
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      privateMibSetLedEntry,
      privateMibGetLedEntry,
      NULL
   },
   {
      "AlarmParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 4, 1},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L1��ѹ�澯  30
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "AlarmParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 4, 2},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L2��ѹ�澯  31
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "AlarmParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 4, 3},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L3��ѹ�澯  32
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "AlarmParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 4, 4},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L1��������ֵ�澯  33
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "AlarmParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 4, 5},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ          //L2��������ֵ�澯  34
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   },
   {
      "AlarmParameter",
      {43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 4, 6},
      12,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,                                           //����ģʽ  ----INTEGER��������ʽ            //L3��������ֵ�澯  35
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      privateMibGetLedEntry,
      NULL
   } 	 
 
};


/**
 * @brief Private MIB module ˽��MIBģ��
 **/

const MibModule privateMibModule =
{
   privateMibObjects,
   arraysize(privateMibObjects),
   privateMibInit,
   privateMibLock,
   privateMibUnlock
};
