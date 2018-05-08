/*
    File Name:        :  main.c

    Device            :  PIC32MM0256GPM048
    Compiler          :  XC32 2.05
    MPLAB             :  MPLAB X 4.15
    Created by        :  http://strefapic.blogspot.com
*/

#include "mcc_generated_files/mcc.h"
#include "xc.h" /* wykrywa rodzaj procka i includuje odpowiedni plik naglowkowy "pic32mm0256gpm048.h"*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /*definicje uint8_t itp*/
#include "delay.h"
#include "dogm162.h"
#include "i2c3.h"
#include "mcp9808.h"


int main(void)
{
      
    // initialize the device
    SYSTEM_Initialize();
    i2c3_Initialize(); /*od tego momentu mozemy dzialac z I2C na kanale nr 3*/
    lcd_Initialize();
    TMR2_Initialize();
    
    TRISBbits.TRISB6 = 0 ; /*ustaw RB6 jako wyjscie cyfrowe tu mamy LED-a*/
    /*When using interrupts, you need to set the Global Interrupt Enable bits
    Use the following macros to:*/

   /*Enable the Global Interrupts
    INTERRUPT_GlobalEnable();*/

   /*Disable the Global Interrupts
    INTERRUPT_GlobalDisable();*/
    
    WpiszSwojeZnaki(); /*definjujemy znak stopien celciusza czyli male koleczko*/
    lcd_Locate(1,1);
    lcd_String("  Temperatura");
    lcd_Locate(2,8);
    lcd_String("/ MCP9808");
    
    
    while (1)
    {
        if(!TimerA_Programowy) {
              TimerA_Programowy = 10 ; /*Timer1 sprzetowy x Timer1_Programowy = 25ms x 10 = 250ms*/
              read_Temp(); /*odczytaj z MCP9808 temperature i wyswietl ja na LCD*/
          }
    }
}
