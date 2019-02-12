/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MCC_H
#define	MCC_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "adc.h"
#include "tmr0.h"
#include "memory.h"
#include "i2c1.h"
#include "spi1.h"
#include "eusart1.h"
#include "tmr1.h"
#include "user_xlcd.h"
#include "pwm2.h"
#include "tmr2.h"
#include "ccp2.h"
#include "tmr3.h"

#define _XTAL_FREQ  4000000ul

/////////////////global variables of the ADC///////////////////
unsigned char ADC_Flag = 0;
unsigned int  ADC_Value;
unsigned char instruction;       //value from the app
uint16_t actual_duty = 50;       //Current duty clycle 50%

/////////////////   EUSART  ///////////////
unsigned char EUSART_Flag = 0;
unsigned char EUSART_Data = 0;
unsigned char buffer[5];
int putty = 0;
int counter_flag = 0;
unsigned char bufferimpresion[160];
unsigned char seleccion = 0;
int CambioDeK = 0;
double duty = 0;
int index;

////////////////    PID     ///////////////////////////
int ADC_HallEffect = 0;
int SetPoint_Int = 0;
double actual_voltage = 0.0f;
double SetPoint = 0.0f;
double error = 0.0f;
double pre_error = 0.0f;
double integral = 0.0f;
double derivative = 0.0f;
double cont_integral = 0.0f;
double cont_proporcional = 0.0f;
double cont_derivativo = 0.0f;
double ctrl = 0.0f;
float kp = 2.0;
float ki = 0.1;
float kd = 0.01;

//Defineparameter
#define epsilon 0.01
#define dt 1         //100mslooptime
#define MAX 4.99f       //For Voltage Saturation
#define MIN 0.1f
/////////////////////   BANDERA INTERMEDIA  /////////////////////
int PID_MENU = 0;
/////////////////////////////////////////////////////////////////

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

void SYSTEM_Initialize(void);
 

void OSCILLATOR_Initialize(void);

#endif	/* MCC_H */

