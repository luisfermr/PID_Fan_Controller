#include <xc.h>
#include <pic18f4550.h>
#include "pin_manager.h"
#include "mcc.h"

void PIN_MANAGER_Initialize(void)
{
    //LATB = 0x0;
    //LATA = 0x0;
    //LATE = 0x0;
    //LATD = 0x0; //belong to LCD
    //LATC = 0x0;
    //TRISD = 0xFF; //belong to LCD
    //TRISE = 0x7;
    TRISB = 0xF0;
    TRISC = 0xC0;
    //TRISA = 0xFF;
    TRISAbits.TRISA0 = 1; //RA/0AN0 is an input
    
    //INT0, INT1 and INT2 are sensitive to positive edges
//    INTCON2bits.INTEDG0 = 1;
//    INTCON2bits.INTEDG1 = 1;
//    INTCON2bits.INTEDG2 = 1;
//
//    INTCON2bits.nRBPU = 0x1; //pull-ups disabled
//
//    INTCONbits.RBIE = 1; // Enable IOCI interrupt 
//    
//    INTCONbits.INT0IE = 1;
//    
//    INTCON3bits.INT1IE = 1;
//    
//    INTCON3bits.INT2IE = 1;

    ADCON1bits.PCFG = 0xE; //RA0/AN0 is the only analog pin
}

void PIN_MANAGER_IOC(void)
{
    
    
}

void PIN_MANAGER_INT0(void)
{
    
}

void PIN_MANAGER_INT1(void)
{
    
}

void PIN_MANAGER_INT2(void)
{
    
}