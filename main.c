/**
 PBL_3 Control PID con Menu
*/

/*
 Luis Fernando Mendez Rodriguez A01730944
*/

#include "mcc.h"
#include "stdio.h"
#include "stdlib.h"
#include <xlcd.h>
#include "math.h"

/*
                         Main application
 */

void putch(unsigned char data);
int dutyCycleInPercentage(double duty);
void MENU(void);
void PID(void);
void getNumber(void);

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //printf("Hello World \n");
    
    //while(BusyUSART());
    //putrsUSART( "\r\nHello World!" );
    
    //start first ADC conversion with AN0
    //ADC_StartConversion(0);
    
    SetPoint = 1.0;
    
    SetPoint_Int = dutyCycleInPercentage(SetPoint);
    
    PWM2_LoadDutyValue( SetPoint_Int ); //
    
    while (1){
        
        if(!PID_MENU)
            MENU();
        else
            PID();
    }
}

void MENU (void)
{
    /////////////////////////////////////////////DISPLAY DEL MENU/////////////////////////////////////////////////
    sprintf(bufferimpresion, " kp: %.3f \n \r ki: %.3f \n \r kf: %.3f \n \r", kp, ki, kd);
    while(BusyUSART());
    putsUSART((unsigned char *)bufferimpresion);

    while(BusyUSART());
    putrsUSART("Escoge una opcion \n \r Modificar kp: (1) \n \r Modificar ki: (2) \n \r Modificar kd: (3) \n \r ENCENDER PID: (4) \n \r");

    while(!EUSART_Flag);
    EUSART_Flag = 0;

    seleccion = EUSART_Data - 48;
    ////////////////////////////////////////////PROCESAMIENTO DE SELECCION////////////////////////////////////////

    switch(seleccion)
    {
        case 1:
            while(BusyUSART());
            putrsUSART("Seleccionaste cambiar kp, introduce su dato \n \r");

            while(!EUSART_Flag);
            EUSART_Flag = 0;

            kp = EUSART_Data;
            kp = kp - 48;

            break;
        case 2:
            while(BusyUSART());
            putrsUSART("Seleccionaste cambiar ki, introduce su dato \n \r");

            while(!EUSART_Flag);
            EUSART_Flag = 0;

            ki = EUSART_Data;
            ki = ki - 48;
            break;
        case 3:
            while(BusyUSART());
            putrsUSART("Seleccionaste cambiar kd, introduce su dato \n \r");

            while(!EUSART_Flag);
            EUSART_Flag = 0;

            kd = EUSART_Data;
            kd = kd - 48;
            break;
        case 4:
            while(BusyUSART());
            putrsUSART("Volviendo a PID \n \r");

            PID_MENU = 1;
            break;
        default:
            while(BusyUSART());
            putrsUSART("Please select one valid number \n \r");
            break;
    }
}

void PID (void)
{
        
        ADC_HallEffect = ADC_GetConversion(0); //esta es la lectura de mi sensor de efecto hall
        ADC_HallEffect = 1024 - ADC_HallEffect; //Se invierten los valores

        actual_voltage = (double)((ADC_HallEffect)*5/1024); //Se convierte el valor a voltage
        
        getNumber(); // se espera un setpoint nuevo

//////////PID CONTROL /////////////////////////////////////U

        error = SetPoint - actual_voltage;
        
        //Incaseof errortoosmall then stop integration
        if(abs(error)> epsilon)
            integral = integral + error*dt;
        
        derivative= (error - pre_error)/dt;
        
        cont_proporcional = kp * error;
        
        cont_integral = ki * integral;
        
        cont_derivativo = kd * derivative;
        
        ctrl = cont_proporcional + cont_integral + cont_derivativo;
               
        //Saturation Filter
        if(ctrl > MAX)
            ctrl = MAX;
        else if(ctrl < MIN)
            ctrl = MIN;

        //Update error
        pre_error = error;
        
//        ctrl = abs(ctrl);
//        counter_flag++;
//        if(counter_flag >= 50){
            
            SetPoint_Int = dutyCycleInPercentage(ctrl);
            
            PWM2_LoadDutyValue( SetPoint_Int );
//        }

        /////////////////////////////////////////////////////IMPRESION///////////////////////////////////////////////////////////////
        putty++;
        if(putty >= 50){
        putty = 0;
        sprintf(bufferimpresion, "Setpoint: %.3f \r \nPosicion Actual: %.5f \r \nError: %.5f \r \nkp: %.3f \r \nki: %.3f \r \nkd: %.3f \r \nCP: %.5f \r \nCI: %.5f \r \nCD: %.5f\r \nControl: %.5f \n \r", SetPoint, actual_voltage, error, kp, ki, kd,cont_proporcional ,cont_integral, cont_derivativo, ctrl);
        while(BusyUSART());
        putsUSART((unsigned char *) bufferimpresion);
        while(BusyUSART());
        putrsUSART("Presiona 'a' para ir al menu o 's' para modificar el set point \n \r");
        }

        /////////////////////////////////////////////////////Regreso al Menu///////////////////////////////////////////////////////
        if(EUSART_Flag == 1){
            EUSART_Flag = 0;
            instruction = EUSART_Data;
            if(instruction == 'a')
                PID_MENU = 0;
        }
        

}

int dutyCycleInPercentage(double duty){
    int duty_1;
    duty_1 = (int) ((duty * 100)/4.99);
    return duty_1;
}

void getNumber(void){
    
    if(EUSART_Flag == 1){
            EUSART_Flag = 0;
            instruction = EUSART_Data;
        }

        if(instruction == 's'){
            int USER_Flag = 1;
            while(BusyUSART());
            putrsUSART("Seleciona un set point, introduce su dato para terminar presiona '*' \n \r");

        
            while (USER_Flag){
                if(EUSART_Flag == 1){
                    EUSART_Flag = 0;
                    if(EUSART_Data == '*'){
                      duty = atof(buffer);
                      index = 0;
                      USER_Flag = 0;
                      instruction = ' ';
                      if(duty>= 0 && duty <= 5);
                      SetPoint = duty;
                      for(int i= 0; i <= 5;i++){
                          buffer[i] = ' ';
                      }
                  } else{  
                      buffer[index] = EUSART_Data;
                      index++;
                  }
                }
            }
        }

}

/**
 End of File
*/