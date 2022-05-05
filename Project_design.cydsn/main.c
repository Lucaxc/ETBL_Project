/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "OLED_Driver.h"
#include "string.h"
#include "stdio.h"
#include "RTC_Driver.h"
#include "ErrorCodes.h"
#include "time.h"
#include "Globals.h"

uint8_t seconds = 0;
int get_day_of_year(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_yday;
}

int main(void)
{
    CyGlobalIntEnable;
        
    I2COLED_Start();
    UART_1_Start();
    
    CyDelay(5);

    display_init(DISPLAY_ADDRESS);
    rtc_init(RTC_ADDRESS);
    
    /*If you want to setup the RTC, uncomment the following line and insert the needed informations, in order.
      Seconds, Minutes, Hours, Date, Month, Year
    */
    //set_RTC(0x50,0x08,0x21,0x05,MAY,Y_2022);
    
    int glucose_concentration = 100;
    char unit[] = "mg/dl";
    char str[30] = {};
    uint8_t seconds_reg;
    
    int i=0;
    int j=0;
    int len = 0;
    
    uint8 index=0;
    char str2[9];
    uint32_t rval;
    char message[100] = {'\0'};
    
    //display_clear();
    UART_1_PutString("\r\n**************\r\n");
    UART_1_PutString("** I2C Scan **\r\n");
    UART_1_PutString("**************\r\n");
    
    CyDelay(10);
    
    UART_1_PutString("\n\n   ");
	for(uint8_t i = 0; i<0x10; i++)
	{
        sprintf(message, "%02X ", i);
		UART_1_PutString(message);
	}
 
    
    // SCAN the I2C BUS for slaves
	for( uint8_t i2caddress = 0; i2caddress < 0x80; i2caddress++ ) {
        
		if(i2caddress % 0x10 == 0 ) {
            sprintf(message, "\n%02X ", i2caddress);
		    UART_1_PutString(message);
        }
 
		rval = I2COLED_MasterSendStart(i2caddress, I2COLED_WRITE_XFER_MODE);
        
        if( rval == I2COLED_MSTR_NO_ERROR ) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_1_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_1_PutString("-- ");
		}
        I2COLED_MasterSendStop();
	}
	UART_1_PutString("\n\n");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /*display_clear();
        display_update();
        rtx_setTextSize(2);
        rtx_setTextColor(WHITE);
        rtx_setCursor(15,20);
        rtx_println("Loading..");
        display_update();
        
        for(i=0; i<128; i++) {
            for(j=0; j<64; j++) {
                display_setPixel(i,j,INVERSE); 
            }
            display_update();
        }
        i=0;
        j=0;
        
        display_clear();
        display_update();
        
        rtx_drawBitmap(0, 0, epd_bitmap_cropped_POLIMI_bianco, 128, 64, WHITE, BLACK);
        display_update();
        CyDelay(6000);
        
        display_clear();
        display_update();
        
        rtx_drawBitmap(0, 0, epd_bitmap_CV1, 128, 64, WHITE, BLACK);
        display_update();
        CyDelay(6000);
        
        display_clear();
        display_update();
        
        rtx_drawBitmap(0, 0, epd_bitmap_teo, 128, 64, WHITE, BLACK);
        display_update();
        CyDelay(6000);
        
        display_clear();
        display_update();
        
        rtx_drawBitmap(0, 0, epd_bitmap_Squarda_ginew, 128, 64, WHITE, BLACK);
        display_update();
        CyDelay(6000);
        
        display_clear();
        rtx_setTextSize(1);
        rtx_setTextColor(WHITE);
        rtx_setCursor(0,0);
        rtx_println("Glucose concentration");
        rtx_setCursor(10,25);
        rtx_setTextSize(2);
        len = snprintf(str, sizeof(str), "%d mg/dl", glucose_concentration);
        rtx_println(str);
        display_update();*/
        
        UART_1_PutString("Secondi\r\n");
        ErrorCode error = RTC_ReadRegister(RTC_ADDRESS, RTC_SECONDS, &seconds_reg);
        if(error == NO_ERROR)
        {
            sprintf(message, "Seconds register value: 0x%02X\r\n", seconds_reg);
            UART_1_PutString(message);
        } else {
            UART_1_PutString("I2C error occurred reading Seconds\r\n");
        }
        
        seconds = RTC_convert_seconds(&seconds_reg);
        CyDelay(10);
        
        len = snprintf(str, sizeof(str), "Secondi: %02x\r\n", seconds_reg);
        UART_1_PutString(str);
        CyDelay(10);
        
        display_clear();
        display_update();
        rtx_setTextSize(1);
        rtx_setTextColor(WHITE);
        rtx_setCursor(0,0);
        rtx_println("Seconds");
        rtx_setCursor(10,25);
        rtx_println(str);
        display_update();
        
        CyDelay(10);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_MINUTES, &seconds_reg);
        
        CyDelay(10);
        len = snprintf(str, sizeof(str), "Minuti: %02x\r\n", seconds_reg);
        UART_1_PutString(str);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_HOURS, &seconds_reg);
        
        CyDelay(10);
        len = snprintf(str, sizeof(str), "Ore: %02x\r\n", seconds_reg);
        UART_1_PutString(str);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_DATE, &seconds_reg);
        
        CyDelay(10);
        len = snprintf(str, sizeof(str), "Data: %02x\r\n", seconds_reg);
        UART_1_PutString(str);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_MONTH, &seconds_reg);
        
        CyDelay(10);
        len = snprintf(str, sizeof(str), "Mese: %02x\r\n", seconds_reg);
        UART_1_PutString(str);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_YEAR, &seconds_reg);

        CyDelay(10);
        len = snprintf(str, sizeof(str), "Anno: %04x\r\n", (seconds_reg));
        UART_1_PutString(str);
        
        CyDelay(1000);
    }
}

/* [] END OF FILE */
