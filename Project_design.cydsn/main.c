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
    eeprom_current_address = 0x0000;
    
    /*If you want to setup the RTC, uncomment the following line and insert the needed informations, in order.
      Seconds, Minutes, Hours, Date, Month, Year
      Then run the program, re-comment the line and re-run the program
    */
    //set_RTC(0x00,0x37,0x15,0x06,MAY,Y_2022);
    
    uint8_t glucose_concentration = 100;
    uint8_t glucose_concentration_from_memory = 0;
    char flag = 0;
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
        OLED_welcome_screen();
        
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
        
        if(flag == 0) {
            flag = 1;
            save_current_measurement(glucose_concentration);
            glucose_concentration_from_memory = get_measurement_from_memory(eeprom_current_address - 7);
        }

        
        display_clear();
        display_update();
        rtx_setTextSize(1);
        rtx_setTextColor(WHITE);
        rtx_setCursor(0,0);
        rtx_println(rtc_content);
        display_update();
        
        CyDelay(2000);
    }
}

/* [] END OF FILE */
