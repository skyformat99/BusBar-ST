/**
 * @file private_mib_impl.c
 * @brief Private MIB module implementation
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

//Dependencies
#include "led.h"
#include "core/net.h"
#include "private_mib_module.h"
#include "private_mib_impl.h"
#include "crypto.h"
#include "asn1.h"
#include "oid.h"
#include "debug.h"
#include "ip_info.h"
#include <string.h>

//Mutex preventing simultaneous access to the private MIB base
static OsMutex privateMibMutex;


/**
 * @brief Private MIB module initialization  私有MIB模块的初始化
 * @return Error code
 **/

error_t privateMibInit(void)
{
   //Debug message
   TRACE_INFO("Initializing private MIB base...\r\n");

   //Clear private MIB base  清空MIB库
   memset(&privateMibBase, 0, sizeof(privateMibBase));

   //Default value for testString object 测试字符型对象的默认值
   strcpy(privateMibBase.testString, "ip+pdu");
   privateMibBase.testStringLen = strlen(privateMibBase.testString);

   //Default value for testInteger object  测试整型对象的默认值
   privateMibBase.testInteger = 123;

   //Number of LEDs  LED的数量
   privateMibBase.ledCount = 3;

   //LED1 color  LED1的颜色
   strcpy(privateMibBase.ledTable[0].ledColor, "green");
   privateMibBase.ledTable[0].ledColorLen = strlen(privateMibBase.ledTable[0].ledColor);
   //LED1 state  LED1的状态
   privateMibBase.ledTable[0].ledState = 0;

   //LED2 color  LED2的颜色
   strcpy(privateMibBase.ledTable[1].ledColor, "orange");
   privateMibBase.ledTable[1].ledColorLen = strlen(privateMibBase.ledTable[1].ledColor);
   //LED2 state  LED2的状态
   privateMibBase.ledTable[1].ledState = 0;

   //LED3 color  LED3的颜色
   strcpy(privateMibBase.ledTable[2].ledColor, "red");
   privateMibBase.ledTable[2].ledColorLen = strlen(privateMibBase.ledTable[2].ledColor);
   //LED3 state   LED3的状态
   privateMibBase.ledTable[2].ledState = 0;

   //Create a mutex to prevent simultaneous access to the private MIB base 创建一个互斥信号量来防止多个同时访问私有MIB库
   if(!osCreateMutex(&privateMibMutex))
   {
      //Failed to create mutex
      return ERROR_OUT_OF_RESOURCES;
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Lock private MIB base
 **/

void privateMibLock(void)
{
   //Enter critical section
   osAcquireMutex(&privateMibMutex);
}


/**
 * @brief Unlock private MIB base
 **/

void privateMibUnlock(void)
{
   //Leave critical section
   osReleaseMutex(&privateMibMutex);
}


/**
 * @brief Get currentTime object value  得到对象当前值
 * @param[in] object Pointer to the MIB object descriptor
 * @param[in] oid Object identifier (object name and instance sub-identifier)
 * @param[in] oidLen Length of the OID, in bytes
 * @param[out] value Object value
 * @param[in,out] valueLen Length of the object value, in bytes
 * @return Error code
 **/

error_t privateMibGetCurrentTime(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   //Get object value
   value->timeTicks = osGetSystemTime() / 10;
   //Successful processing
   return NO_ERROR;
}

/**
 * @brief Set ledEntry object value   设置LED对象值
 * @param[in] object Pointer to the MIB object descriptor 指向MIB对象的描述符
 * @param[in] oid Object identifier (object name and instance sub-identifier)  对象标识符
 * @param[in] oidLen Length of the OID, in bytes  OID长度
 * @param[in] value Object value   对象值
 * @param[in] valueLen Length of the object value, in bytes  对象值的长度
 * @return Error code
 **/

error_t privateMibSetLedEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, const MibVariant *value, size_t valueLen)
{
   uint_t index;
	 char setvalue[3];
	
		 //Get index  
	 index = oid[oidLen - 2];

		 //Check index range  检查指数范围
	 if(index < 1 || index > 25)                  
			return ERROR_INSTANCE_NOT_FOUND;			

   //Check OID length  检查OID的长度
   if(oidLen != (object->oidLen + 1))
      return ERROR_INSTANCE_NOT_FOUND;
	 
	 
	 
	 if(!strcmp(object->name, "deviceinfo"))
	 {
		 
			if(index==2)
			{
					ser = value->integer;
					I2cWrite(224,ser);     //从机地址						
			}
			else if(index==3)
			{	
					 if(value->integer==1200)
					 {
							baud = 0;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,1200);
					 }		
					 else if(value->integer==2400)
					 {
							baud = 1;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,2400);						 
					 }
					 else if(value->integer==4800)
					 {
							baud = 2;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,4800);						 
					 }
					 else if(value->integer==9600)
					 {
							baud = 3;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,9600);						 
					 }
					 else if(value->integer==19200) 
					 {
							baud = 4;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,19200);						 
					 }
					 else if(value->integer==38400)
					 {
							baud = 5;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,38400);								 
					 }
					 else
					 {
							baud = 3;
							I2cWrite(225,baud);		 //波特率	
							USART_SetBaudRate(USART3,9600);								 
					 }
			}	 			
	 }
	 if(!strcmp(object->name, "SettingParameter"))
	 {
		 
			if(index==1)
			{
					Tvol[0][1] = value->integer;
					I2cWrite_2(9,Tvol[0][1]>>8);
					I2cWrite_2(10,Tvol[0][1]);				
			}
			else if(index==2)
			{
					Tvol[0][2] = value->integer;
					I2cWrite_2(11,Tvol[0][2]>>8);
					I2cWrite_2(12,Tvol[0][2]);					
			}	 		
			else if(index==3)
			{
					Tvol[1][1] = value->integer;
					I2cWrite_2(17,Tvol[1][1]>>8);
					I2cWrite_2(18,Tvol[1][1]);					
			}	
			else if(index==4)
			{
					Tvol[1][2] = value->integer;
					I2cWrite_2(19,Tvol[1][2]>>8);
					I2cWrite_2(20,Tvol[1][2]);					
			}		
			else if(index==5)
			{
					Tvol[2][1] = value->integer;
					I2cWrite_2(25,Tvol[2][1]>>8);
					I2cWrite_2(26,Tvol[2][1]);					
			}	
			else if(index==6)
			{
					Tvol[2][2] = value->integer;
					I2cWrite_2(27,Tvol[2][2]>>8);
					I2cWrite_2(28,Tvol[2][2]);					
			}	
			else if(index==7)
			{
					Tcur[0][1] = value->integer;
					I2cWrite_2(13,Tcur[0][1]>>8);
					I2cWrite_2(14,Tcur[0][1]);				
			}
			else if(index==8)
			{
					Tcur[0][2] = value->integer;
					I2cWrite_2(15,Tcur[0][2]>>8);
					I2cWrite_2(16,Tcur[0][2]);					
			}	 		
			else if(index==9)
			{
					Tcur[1][1] = value->integer;
					I2cWrite_2(21,Tcur[1][1]>>8);
					I2cWrite_2(22,Tcur[1][1]);					
			}	
			else if(index==10)
			{
					Tcur[1][2] = value->integer;
					I2cWrite_2(23,Tcur[1][2]>>8);
					I2cWrite_2(24,Tcur[1][2]);					
			}		
			else if(index==11)
			{
					Tcur[2][1] = value->integer;
					I2cWrite_2(29,Tcur[2][1]>>8);
					I2cWrite_2(30,Tcur[2][1]);					
			}	
			else if(index==12)
			{
					Tcur[2][2] = value->integer;
					I2cWrite_2(31,Tcur[2][2]>>8);
					I2cWrite_2(32,Tcur[2][2]);					
			}					
	 }	 

   //Unknown object?
   else
   {
      //The specified object does not exist
      return ERROR_OBJECT_NOT_FOUND;
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Get ledEntry object value 得到LED的值
 * @param[in] object Pointer to the MIB object descriptor  指向MIB对象描述符
 * @param[in] oid Object identifier (object name and instance sub-identifier)  指向OID
 * @param[in] oidLen Length of the OID, in bytes  OID长度
 * @param[out] value Object value      对象值
 * @param[in,out] valueLen Length of the object value, in bytes  对象值的长度
 * @return Error code
 **/

error_t privateMibGetLedEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   uint_t index=0;
	 uint_t lengt=0;

   //Check OID length
   if(oidLen != (object->oidLen + 1))
      return ERROR_INSTANCE_NOT_FOUND;

   //Get index    OID倒数第二个节点，例如43, 6, 1, 4, 1, 129, 241, 118, 10, 2, 2, 2, 5，得到index=5
   index = oid[oidLen - 2];
	 

   //Check index range
   if(index < 1 || index > 25)              //指数大小
      return ERROR_INSTANCE_NOT_FOUND;
	 
   //ledColor object?  判断名字
   if(!strcmp(object->name, "deviceinfo"))
	 {
		  switch(index)
			{
				case 1:
					memcpy(value->octetString, snmpsysname,strlen(snmpsysname));
				  *valueLen = strlen(snmpsysname);
					break;
				case 2:
					value->integer = ser;	
				  break;
				case 3:
					if(baud==0) value->integer = 1200;
					else if(baud==1) value->integer = 2400;
					else if(baud==2) value->integer = 4800;
					else if(baud==3) value->integer = 9600;
					else if(baud==4) value->integer = 19200;
					else if(baud==5) value->integer = 38400;
					else value->integer = 9600;
//					value->integer = baud;
				  break;
				case 4:
					value->integer = LINE_NUM;
				  break;				
				default:
					break;	
				
			} 
	 }
   //ledColor object?  判断名字
   else if(!strcmp(object->name, "ElectricParameter"))             //10.2.2.1
	 {
		  switch(index)
			{
				case 1:
					value->integer = Tvol[0][0];
				  break;
				case 2:
					value->integer = Tvol[1][0];
					break;
				case 3:
					value->integer = Tvol[2][0];
					break;
				case 4:
					value->integer = Tcur[0][0];
					break;
				case 5:
					value->integer = Tcur[1][0];	
					break;
				case 6:
					value->integer = Tcur[2][0];	
					break;
				case 7:
					if(cur_dc_ac==0) value->integer = Tvol[0][0]*Tcur[0][0]/10;                       //dc
					else value->integer = Tvol[0][0]*Tcur[0][0]/10;  	                //ac		
					break;
				case 8:
					value->integer = Tvol[1][0]*Tcur[1][0]/10; 
					break;
				case 9:
					value->integer = Tvol[2][0]*Tcur[2][0]/10; 
					break;
				case 10:
					if(cur_dc_ac==0) value->integer = Energy8207_dc;	       //dc
					else value->integer = Energy8207[0];	  	       //ac		
					break;
				case 11:
					value->integer = Energy8207[1];	
					break;
				case 12:
					value->integer = Energy8207[2];	
					break;
				case 13:
					value->integer = tem[0];	
					break;
				case 14:
					value->integer = hum[0];
					break;
				default:
					break;	
						
			}			  	 
	 } 
   else if(!strcmp(object->name, "SettingParameter"))             //10.2.3.1
	 {
		  switch(index)
			{
				case 1:
					value->integer = Tvol[0][1];
				  break;
				case 2:
					value->integer = Tvol[0][2];
					break;
				case 3:
					value->integer = Tvol[1][1];
					break;
				case 4:
					value->integer = Tvol[1][2];
					break;
				case 5:
					value->integer = Tvol[2][1];	
					break;
				case 6:
					value->integer = Tvol[2][2];	
					break;
				case 7:
					value->integer = Tcur[0][1];
				  break;
				case 8:
					value->integer = Tcur[0][2];
					break;
				case 9:
					value->integer = Tcur[1][1];
					break;
				case 10:
					value->integer = Tcur[1][2];
					break;
				case 11:
					value->integer = Tcur[2][1];	
					break;
				case 12:
					value->integer = Tcur[2][2];	
					break;
				default:
					break;				
			}			  	 
	 } 
   else if(!strcmp(object->name, "AlarmParameter"))             //10.2.4.1
	 {
		  switch(index)
			{
				case 1:
					if(Tvol[0][0]<Tvol[0][1]) value->integer = 1;
					else if(Tvol[0][0]>Tvol[0][2]) value->integer = 2;
					else value->integer = 0;
				  break;
				case 2:
					if(Tvol[1][0]<Tvol[1][1]) value->integer = 1;
					else if(Tvol[1][0]>Tvol[1][2]) value->integer = 2;
					else value->integer = 0;
					break;
				case 3:
					if(Tvol[2][0]<Tvol[2][1]) value->integer = 1;
				  else if(Tvol[2][0]>Tvol[2][2]) value->integer = 2;
					else value->integer = 0;
					break;
				case 4:
					if(Tcur[0][0]<Tcur[0][1]) value->integer = 1;
					else if(Tcur[0][0]>Tcur[0][2]) value->integer = 2;
					else value->integer = 0;
				  break;
				case 5:
					if(Tcur[1][0]<Tcur[1][1]) value->integer = 1;
					else if(Tcur[1][0]>Tcur[1][2]) value->integer = 2;
					else value->integer = 0;
					break;
				case 6:
					if(Tcur[2][0]<Tcur[2][1]) value->integer = 1;
				  else if(Tcur[2][0]>Tcur[2][2]) value->integer = 2;
					else value->integer = 0;
					break;
				default:
					break;				
			}			  	 
	 }		 
   //Unknown object?
   else
   {
      //The specified object does not exist
      return ERROR_OBJECT_NOT_FOUND;
   }

   //Successful processing
   return NO_ERROR;
}



/**
 * @brief Get next ledEntry object
 * @param[in] object Pointer to the MIB object descriptor
 * @param[in] oid Object identifier
 * @param[in] oidLen Length of the OID, in bytes
 * @param[out] nextOid OID of the next object in the base
 * @param[out] nextOidLen Length of the next object identifier, in bytes
 * @return Error code
 **/

error_t privateMibGetNextLedEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, uint8_t *nextOid, size_t *nextOidLen)
{
   uint_t index;

   //Make sure the buffer is large enough to hold the entire OID
   if(*nextOidLen < (object->oidLen + 1))
      return ERROR_BUFFER_OVERFLOW;

   //Copy object identifier
   memcpy(nextOid, object->oid, object->oidLen);

   //Loop through LED table
   for(index = 1; index <= PRIVATE_MIB_LED_COUNT; index++)
   {
      //Select instance
      nextOid[object->oidLen] = index;

      //Compare object identifiers
      if(oidComp(oid, oidLen, nextOid, object->oidLen + 1) < 0)
      {
         //Save the length of the next object identifier
         *nextOidLen = object->oidLen + 1;
         //The specified OID lexicographically precedes the name of the current object
         return NO_ERROR;
      }
   }

   //The specified OID does not lexicographically precede the name of some object
   return ERROR_OBJECT_NOT_FOUND;
}
