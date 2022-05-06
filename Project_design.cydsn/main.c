/* ========================================================================
 *
 * ELECTRONIC TECHNOLOGIES AND BIOSENSORS LABORATORY
 * Academic year 2021/22, II Semester
 * Final Project
 *
 * Authors: Group 2
 *
 * --------------------------------- MAIN ---------------------------------
 * Main file.
 * ------------------------------------------------------------------------
 * 
 * ========================================================================
*/
#include <project.h>
#include <string.h>
#include <stdio.h>

#include "OLED_Driver.h"
#include "RTC_Driver.h"
#include "EEPROM_Driver.h"
#include "ErrorCodes.h"
#include "Globals.h"
#include "time.h"

uint8_t seconds = 0;

char rtc_content[64] = {};
uint8_t rtc_data_register;

int main(void)
{
    CyGlobalIntEnable;
        
    I2CMASTER_Start();
    UART_1_Start();
    
    CyDelay(5);

    display_init(DISPLAY_ADDRESS);
    rtc_init(RTC_ADDRESS);
    
    /*If you want to setup the RTC, uncomment the following line and insert the needed informations, in order.
      Seconds, Minutes, Hours, Date, Month, Year
    */
    //set_RTC(0x10,0x10,0x08,0x06,MAY,Y_2022);
    
    int glucose_concentration = 100;
    char unit[] = "mg/dl";
    
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
 
		rval = I2CMASTER_MasterSendStart(i2caddress, I2CMASTER_WRITE_XFER_MODE);
        
        if( rval == I2CMASTER_MSTR_NO_ERROR ) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_1_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_1_PutString("-- ");
		}
        I2CMASTER_MasterSendStop();
	}
	UART_1_PutString("\n\n");

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
        ErrorCode error = RTC_ReadRegister(RTC_ADDRESS, RTC_SECONDS, &rtc_data_register);
        if(error == NO_ERROR)
        {
            sprintf(message, "Seconds register value: 0x%02X\r\n", rtc_data_register);
            UART_1_PutString(message);
        } else {
            UART_1_PutString("I2C error occurred reading Seconds\r\n");
        }
        
        seconds = RTC_convert_seconds(rtc_data_register);
        //CyDelay(10);
        
        len = snprintf(rtc_content, sizeof(rtc_content), "Secondi: %02x\r\n", rtc_data_register);
        UART_1_PutString(rtc_content);
        //CyDelay(10);
        
        len = snprintf(rtc_content, sizeof(rtc_content), "Secondi: %d\r\n", seconds);
        UART_1_PutString(rtc_content);
        //CyDelay(10);
        
        /*error = RTC_ReadRegister(RTC_ADDRESS, RTC_MINUTES, &rtc_data_register);
        
        CyDelay(10);
        len = snprintf(rtc_content, sizeof(rtc_content), "Minuti: %02x\r\n", rtc_data_register);
        UART_1_PutString(rtc_content);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_HOURS, &rtc_data_register);
        
        CyDelay(10);
        len = snprintf(rtc_content, sizeof(rtc_content), "Ore: %02x\r\n", rtc_data_register);
        UART_1_PutString(rtc_content);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_DATE, &rtc_data_register);
        
        CyDelay(10);
        len = snprintf(rtc_content, sizeof(rtc_content), "Data: %02x\r\n", rtc_data_register);
        UART_1_PutString(rtc_content);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_MONTH, &rtc_data_register);
        
        CyDelay(10);
        len = snprintf(rtc_content, sizeof(rtc_content), "Mese: %02x\r\n", rtc_data_register);
        UART_1_PutString(rtc_content);
        
        error = RTC_ReadRegister(RTC_ADDRESS, RTC_YEAR, &rtc_data_register);

        CyDelay(10);
        len = snprintf(rtc_content, sizeof(rtc_content), "Anno: %04x\r\n", (rtc_data_register));
        UART_1_PutString(rtc_content);*/
        
        rtc_read_time(RTC_ADDRESS);
        len = snprintf(rtc_content, sizeof(rtc_content), "Secondi: %d\r\n", current_seconds);
        UART_1_PutString(rtc_content);
        len = snprintf(rtc_content, sizeof(rtc_content), "Minuti: %d\r\n", current_minutes);
        UART_1_PutString(rtc_content);
        len = snprintf(rtc_content, sizeof(rtc_content), "Ore: %d\r\n", current_hours);
        UART_1_PutString(rtc_content);
        len = snprintf(rtc_content, sizeof(rtc_content), "Giorno: %d\r\n", current_date);
        UART_1_PutString(rtc_content);
        len = snprintf(rtc_content, sizeof(rtc_content), "Mese: %d\r\n", current_month);
        UART_1_PutString(rtc_content);
        len = snprintf(rtc_content, sizeof(rtc_content), "Anno: %d\r\n\n", current_year);
        UART_1_PutString(rtc_content);
        
        len = snprintf(rtc_content, sizeof(rtc_content), "%d-%d-%d %02d:%02d:%02d", current_date, 
                       current_month, current_year, current_hours, current_minutes, current_seconds);
        UART_1_PutString(rtc_content);
        
        display_clear();
        display_update();
        rtx_setTextSize(1);
        rtx_setTextColor(WHITE);
        rtx_setCursor(0,0);
        rtx_println(rtc_content);
        display_update();
        
        CyDelay(1000);
    }
}

/* [] END OF FILE */
