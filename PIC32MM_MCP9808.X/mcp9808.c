/*
    File Name:        :  mcp9808.c

    Device            :  PIC32MM0256GPM048
    Compiler          :  XC32 2.05
    MPLAB             :  MPLAB X 4.15
    Created by        :  http://strefapic.blogspot.com
*/
#include "mcc_generated_files/mcc.h"
#include "xc.h" /* wykrywa rodzaj procka i includuje odpowiedni plik naglowkowy "pic32mm0256gpm048.h"*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> /*definicje uint8_t itp*/
#include "delay.h"
#include "dogm162.h" /*wyswietlacz*/
#include "i2c3.h"
#include "mcp9808.h"

 uint8_t UpperByte ;
 uint8_t LowerByte ;
 float Temperature ;
 char Temperature_bufor[5] ;/*bufor do konwersji z float na char*/
 
void read_Temp(void) {
    
    /*komunikacja i odczyt temperatury MCP9808*/
    i2c3_start();
    i2c3_write(MCP9808_ADDRESS & 0xFE); /*wyslij bajt z adresem i bitem R/W ustawionym na 0*/
    i2c3_write(MCP9808_REG_AMBIENT_TEMP); /*ustawiamy rejestr z ktorym chcemy gadac*/
    i2c3_restart();
    i2c3_write(MCP9808_ADDRESS | 0x01); /*wyslij bajt z adresem i bitem R/W ustawionym na 1*/
    UpperByte = i2c3_read();
    i2c3_ack();
    LowerByte = i2c3_read();
    i2c3_nack();
    i2c3_stop(); /*THE END transmission with MCP9808*/
    /*Convert the temperature data*/
    /*First check flag bits*/
    if ((UpperByte & 0x80) == 0x80){/*tutaj kod do obslugi zdarzenia*/}   //TA >= TCRIT
    if ((UpperByte & 0x40) == 0x40){/*tutaj kod do obslugi zdarzenia*/}   //TA > TUPPER
    if ((UpperByte & 0x20) == 0x20){/*tutaj kod do obslugi zdarzenia*/}   //TA < TLOWER
    
    UpperByte = UpperByte & 0x1F;                //Clear flag bits
    if ((UpperByte & 0x10) == 0x10){             //TA < 0°C
    UpperByte = UpperByte & 0x0F;                //Clear SIGN
    Temperature = 256 - ((float)UpperByte * 16 + (float)LowerByte / 16); 
    } else                                       
    Temperature = ((float)UpperByte * 16 + (float)LowerByte / 16); //TA >= 0°C
    
    /*Temperature = Ambient Temperature (°C)*/
    /*konwersja float na string i zapis wyniku do bufora*/
    sprintf(Temperature_bufor,"%2.1f",Temperature);
    /*wyswietlamy temperature na LCD*/
    lcd_Locate(2,1);
    lcd_String(Temperature_bufor);
    lcd_String("\x01""C");/*wyswietl znak stopnia plus literka C*/
  
    /*tu zerujmy bufor*/
    memset(Temperature_bufor, ' ', 5);
        
}