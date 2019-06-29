
/*
	TMC2208.cpp - Support for TMC2208 Stepper Drivers SPI Mode
  Part of Grbl_ESP32  

  Copyright (c) 2019 Barton Dring for Buildlog.net LLC   	
  TMC2208 support (c) 2019 Wolfgang Lienbacher

  GrblESP32 is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

#define R_SENSE 0.11 // Match to your driver
                     // SilentStepStick series use 0.11
                     // UltiMachine Einsy and Archim2 boards use 0.2
                     // Panucatt BSD2660 uses 0.1
                     // Watterott TMC5160 uses 0.075

#ifdef X_UART_RX
    #define RX2 X_UART_RX
#endif 

#ifdef X_UART_TX
    #define TX2 X_UART_TX
    TMC2208Stepper TMC2208_X = TMC2208Stepper(&Serial2, R_SENSE); // Hardware Serial0
#endif 

void TMC2208_Init()
{
		#ifdef X_UART_TX
            Serial.println("[MSG:Initializing TMC2208]\r\n");
            Serial2.begin(115200);      // Init used serial port
            while(!Serial2);             // Wait for port to be ready
            TMC2208_X.pdn_disable(true);     // Use PDN/UART pin for communication
            TMC2208_X.mstep_reg_select(1);  // necessary for TMC2208 to set microstep register with UART
            TMC2208_X.I_scale_analog(false); // Use internal voltage reference
			TMC2208_X.begin();          // Initiate pins and registries
			TMC2208_X.microsteps(64);
			TMC2208_X.rms_current(500);
		#endif
}