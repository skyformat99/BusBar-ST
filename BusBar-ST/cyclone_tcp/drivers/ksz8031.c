/**
 * @file ksz8031.c
 * @brief KSZ8031 Ethernet PHY transceiver
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
#define TRACE_LEVEL NIC_TRACE_LEVEL

//Dependencies
#include "core/net.h"
#include "drivers/ksz8031.h"
#include "debug.h"


/**
 * @brief KSZ8031 Ethernet PHY driver
 **/

const PhyDriver ksz8031PhyDriver =
{
   ksz8031Init,
   ksz8031Tick,
   ksz8031EnableIrq,
   ksz8031DisableIrq,
   ksz8031EventHandler,
};


/**
 * @brief KSZ8031 PHY transceiver initialization
 * @param[in] interface Underlying network interface
 * @return Error code
 **/

error_t ksz8031Init(NetInterface *interface)
{
   //Debug message
   TRACE_INFO("Initializing KSZ8031...\r\n");

   //Initialize external interrupt line driver
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->init();

   //Reset PHY transceiver
   ksz8031WritePhyReg(interface, KSZ8031_PHY_REG_BMCR, BMCR_RESET);
   //Wait for the reset to complete
   while(ksz8031ReadPhyReg(interface, KSZ8031_PHY_REG_BMCR) & BMCR_RESET);

   //Dump PHY registers for debugging purpose
   ksz8031DumpPhyReg(interface);

   //The PHY will generate interrupts when link status changes are detected
   ksz8031WritePhyReg(interface, KSZ8031_PHY_REG_ICSR, ICSR_LINK_DOWN_IE | ICSR_LINK_UP_IE);

   //Force the TCP/IP stack to poll the link state at startup
   interface->phyEvent = TRUE;
   //Notify the TCP/IP stack of the event
   osSetEvent(&netEvent);

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief KSZ8031 timer handler
 * @param[in] interface Underlying network interface
 **/

void ksz8031Tick(NetInterface *interface)
{
   uint16_t value;
   bool_t linkState;

   //No external interrupt line driver?
   if(interface->extIntDriver == NULL)
   {
      //Read basic status register
      value = ksz8031ReadPhyReg(interface, KSZ8031_PHY_REG_BMSR);
      //Retrieve current link state
      linkState = (value & BMSR_LINK_STATUS) ? TRUE : FALSE;

      //Link up event?
      if(linkState && !interface->linkState)
      {
         //Set event flag
         interface->phyEvent = TRUE;
         //Notify the TCP/IP stack of the event
         osSetEvent(&netEvent);
      }
      //Link down event?
      else if(!linkState && interface->linkState)
      {
         //Set event flag
         interface->phyEvent = TRUE;
         //Notify the TCP/IP stack of the event
         osSetEvent(&netEvent);
      }
   }
}


/**
 * @brief Enable interrupts
 * @param[in] interface Underlying network interface
 **/

void ksz8031EnableIrq(NetInterface *interface)
{
   //Enable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->enableIrq();
}


/**
 * @brief Disable interrupts
 * @param[in] interface Underlying network interface
 **/

void ksz8031DisableIrq(NetInterface *interface)
{
   //Disable PHY transceiver interrupts
   if(interface->extIntDriver != NULL)
      interface->extIntDriver->disableIrq();
}


/**
 * @brief KSZ8031 event handler
 * @param[in] interface Underlying network interface
 **/

void ksz8031EventHandler(NetInterface *interface)
{
   uint16_t value;

   //Read status register to acknowledge the interrupt
   value = ksz8031ReadPhyReg(interface, KSZ8031_PHY_REG_ICSR);

   //Link status change?
   if(value & (ICSR_LINK_DOWN_IF | ICSR_LINK_UP_IF))
   {
      //Any link failure condition is latched in the BMSR register... Reading
      //the register twice will always return the actual link status
      value = ksz8031ReadPhyReg(interface, KSZ8031_PHY_REG_BMSR);
      value = ksz8031ReadPhyReg(interface, KSZ8031_PHY_REG_BMSR);

      //Link is up?
      if(value & BMSR_LINK_STATUS)
      {
         //Read PHY control register
         value = ksz8031ReadPhyReg(interface, KSZ8031_PHY_REG_PHYCON1);

         //Check current operation mode
         switch(value & PHYCON1_OP_MODE_MASK)
         {
         //10BASE-T
         case PHYCON1_OP_MODE_10BT:
            interface->linkSpeed = NIC_LINK_SPEED_10MBPS;
            interface->duplexMode = NIC_HALF_DUPLEX_MODE;
            break;
         //10BASE-T full-duplex
         case PHYCON1_OP_MODE_10BT_FD:
            interface->linkSpeed = NIC_LINK_SPEED_10MBPS;
            interface->duplexMode = NIC_FULL_DUPLEX_MODE;
            break;
         //100BASE-TX
         case PHYCON1_OP_MODE_100BTX:
            interface->linkSpeed = NIC_LINK_SPEED_100MBPS;
            interface->duplexMode = NIC_HALF_DUPLEX_MODE;
            break;
         //100BASE-TX full-duplex
         case PHYCON1_OP_MODE_100BTX_FD:
            interface->linkSpeed = NIC_LINK_SPEED_100MBPS;
            interface->duplexMode = NIC_FULL_DUPLEX_MODE;
            break;
         //Unknown operation mode
         default:
            //Debug message
            TRACE_WARNING("Invalid Duplex mode\r\n");
            break;
         }

         //Update link state
         interface->linkState = TRUE;

         //Adjust MAC configuration parameters for proper operation
         interface->nicDriver->updateMacConfig(interface);
      }
      else
      {
         //Update link state
         interface->linkState = FALSE;
      }

      //Process link state change event
      nicNotifyLinkChange(interface);
   }
}


/**
 * @brief Write PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address Register address
 * @param[in] data Register value
 **/

void ksz8031WritePhyReg(NetInterface *interface, uint8_t address, uint16_t data)
{
   uint8_t phyAddr;

   //Get the address of the PHY transceiver
   if(interface->phyAddr < 32)
      phyAddr = interface->phyAddr;
   else
      phyAddr = KSZ8031_PHY_ADDR;

   //Write the specified PHY register
   interface->nicDriver->writePhyReg(phyAddr, address, data);
}


/**
 * @brief Read PHY register
 * @param[in] interface Underlying network interface
 * @param[in] address PHY register address
 * @return Register value
 **/

uint16_t ksz8031ReadPhyReg(NetInterface *interface, uint8_t address)
{
   uint8_t phyAddr;

   //Get the address of the PHY transceiver
   if(interface->phyAddr < 32)
      phyAddr = interface->phyAddr;
   else
      phyAddr = KSZ8031_PHY_ADDR;

   //Read the specified PHY register
   return interface->nicDriver->readPhyReg(phyAddr, address);
}


/**
 * @brief Dump PHY registers for debugging purpose
 * @param[in] interface Underlying network interface
 **/

void ksz8031DumpPhyReg(NetInterface *interface)
{
   uint8_t i;

   //Loop through PHY registers
   for(i = 0; i < 32; i++)
   {
      //Display current PHY register
      TRACE_DEBUG("%02" PRIu8 ": 0x%04" PRIX16 "\r\n", i, ksz8031ReadPhyReg(interface, i));
   }

   //Terminate with a line feed
   TRACE_DEBUG("\r\n");
}
