/* ========================================================================
 *
 * ELECTRONIC TECHNOLOGIES AND BIOSENSORS LABORATORY
 * Academic year 2021/22, II Semester
 * Final Project

 * Authors: Group 2
 *
 * ------------------------- RTC Driver (source) --------------------------
 * 
 * ------------------------------------------------------------------------
 * 
 * ========================================================================
*/

#include <project.h>
#include <stdlib.h>
#include <math.h>

#include "RTC_Driver.h"
#include "ErrorCodes.h"

/*------------------------------------------------------------------------
*                       STATIC VARIABLES DECLARATION
-------------------------------------------------------------------------*/
static uint8_t rtc_i2c_address;

/*------------------------------------------------------------------------
*                       FUNCTIONS IMPLEMENTATION
-------------------------------------------------------------------------*/
/*  RTC SET UP
*   \brief: Function that, given the user-inserted values, sets the RTC.
*   \Parameters:
*       @param current_seconds: real time seconds
*       @param current_minutes: real time minutes
*       @param current_hours: real time hours
*       @param current_date: real time date
*       @param current_month: real time month
*       @param current_year: real time year
*   \Return: NONE
*/
void set_RTC(uint8_t current_seconds, uint8_t current_minutes, uint8_t current_hours, uint8_t current_date, 
             uint8_t current_month, uint8_t current_year) {
    
    ErrorCode error = RTC_WriteRegister(RTC_ADDRESS, RTC_SECONDS, current_seconds);
    if(error == ERROR) {
        UART_1_PutString("Error in setting the RTC seconds");
    }
    
    error = RTC_WriteRegister(RTC_ADDRESS, RTC_MINUTES, current_minutes);
    if(error == ERROR) {
        UART_1_PutString("Error in setting the RTC minutes");
    }
    
    error = RTC_WriteRegister(RTC_ADDRESS, RTC_HOURS, current_hours);
    if(error == ERROR) {
        UART_1_PutString("Error in setting the RTC hours");
    }
    
    error = RTC_WriteRegister(RTC_ADDRESS, RTC_DATE, current_date);
    if(error == ERROR) {
        UART_1_PutString("Error in setting the RTC date");
    }
    
    error = RTC_WriteRegister(RTC_ADDRESS, RTC_MONTH, current_month);
    if(error == ERROR) {
        UART_1_PutString("Error in setting the RTC month");
    }
    
    error = RTC_WriteRegister(RTC_ADDRESS, RTC_YEAR, current_year);
    if(error == ERROR) {
        UART_1_PutString("Error in setting the RTC year");
    }               
 }

/*  RTC INIT
*   \brief: Function that initializes the pheripheral
*   \Parameters:
*       @param rtc_address: I2C RTC slave address
*   \Return: NONE
*/
void rtc_init(uint8_t rtc_address) {
    
    rtc_i2c_address = rtc_address;
}

/*  RTC READ REGISTER
*   \brief: Function that reads slave register content
*   \Parameters:
*       @param device_address: 8-bit slave device address
*       @param register_address: 8-bit address of the register where content is stored
*       @param data: pointer to array where to store read value
*   \Return: error (if reading is successfull or not)
*/
ErrorCode RTC_ReadRegister(uint8_t device_address, uint8_t register_address, uint8_t* data) {
    
    // Start Condition: we pass the macro I2C_Master_WRITE_XFER_MODE embedded in the API to write into the accelerometer
    //The function returns an ACK or NACK.
    uint8_t error = I2COLED_MasterSendStart(device_address, I2COLED_WRITE_XFER_MODE);                                        
    if (error == I2COLED_MSTR_NO_ERROR)
    {
        //Write the register address to be read
        error = I2COLED_MasterWriteByte(register_address);
        if (error == I2COLED_MSTR_NO_ERROR)
        {
            // Send a restart condition: this function is like r 08 x p put in the bridge control panel.
            error = I2COLED_MasterSendRestart(device_address, I2COLED_READ_XFER_MODE);
            if (error == I2COLED_MSTR_NO_ERROR)
            {
                *data = I2COLED_MasterReadByte(I2COLED_NAK_DATA); //The NACK is needed otherwise the I2C keeps reading
            }
        }
    }
    // Stop Comunication
    I2COLED_MasterSendStop();
    //Return
    return error ? ERROR : NO_ERROR;   
}

/*  RTC WRITE REGISTER
*   \brief: Function that sets slave register content
*   \Parameters:
*       @param device_address: 8-bit slave device address
*       @param register_address: 8-bit address of the register where content has to be written
*       @param data: pointer to array containing values to be written
*   \Return: error (if reading is successfull or not)
*/
ErrorCode RTC_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data) {
                                        
    uint8_t error = I2COLED_MasterSendStart(device_address, I2COLED_WRITE_XFER_MODE);
    if (error == I2COLED_MSTR_NO_ERROR)
    {
        // Write Register Address (to be overwritten)
        error = I2COLED_MasterWriteByte(register_address);
        if (error == I2COLED_MSTR_NO_ERROR)
        {
            // Write Byte
            error = I2COLED_MasterWriteByte(data);
        }
    }
    // Close Communication
    I2COLED_MasterSendStop();
    // Return
    return error ? ERROR : NO_ERROR;
}

/*------------------------------------------------------------------------
*                        RTC AUXILIARY FUNCTIONS
-------------------------------------------------------------------------*/
/*  RTC CONVERT SECOND
*   \brief: converts the seconds buffer in int
*   \Parameters:
*       @param buffer: 8-bit buffer with information
*   \Return: seconds
*/
uint8_t RTC_convert_seconds(uint8_t* buffer) {
    
    uint8_t seconds = 0;
    
    //Bits 0-3 that converts for units
    for(int i = 0; i < 4; i++) {
        if(*(buffer+i) & (0b00000001<<i)) {
            seconds += pow(2,i);
        }
    }
    
    //Bits 4-7 that converts for units
    for(int j = 4; j < 8; j++) {
        if(*(buffer+j) & (0b00000001<<j)) {
            seconds += 10*pow(2,j-4);
        }
    }
    
    return seconds;
}

/*  RTC CONVERT MINUTES
*   \brief: converts the minute buffer in int
*   \Parameters:
*       @param buffer: 8-bit buffer with information
*   \Return: minutes
*/
uint8_t RTC_convert_minutes(uint8_t* buffer) {
    
    uint8_t minutes = 0;
    
    //Bits 0-3 that converts for units
    for(int i = 0; i < 4; i++) {
        if(*(buffer+i) & (0b00000001<<i)) {
            minutes += pow(2,i);
        }
    }
    
    //Bits 4-7 that converts for units
    for(int j = 4; j < 8; j++) {
        if(*(buffer+j) & (0b00000001<<j)) {
            minutes += 10*pow(2,j-4);
        }
    }
    
    return minutes;
}                                    

/*  RTC CONVERT HOURS
*   \brief: converts the hours buffer in int
*   \Parameters:
*       @param buffer: 8-bit buffer with information
*   \Return: hours
*/
uint8_t RTC_convert_hours(uint8_t* buffer) {
    
    uint8_t hours = 0;
    
    for(int i = 0; i < 4; i++) {
        if(*(buffer+i) & (0b00000001<<i)) {
            hours += pow(2,i);
        }
    }
    
    hours += 10*(*(buffer+4));
    
    return hours;
}


/*  RTC CONVERT DAY
*   \brief: converts the day buffer in int
*   \Parameters:
*       @param buffer: 8-bit buffer with information
*   \Return: day
*/
uint8_t RTC_convert_day(uint8_t* buffer) {
    
    uint8_t day = 0;
    
    for(int i = 0; i < 3; i++) {
        if(*(buffer+i) & (0b00000001<<i)) {
            day += pow(2,i);
        }
    }
    
    return day;
}

/*  RTC CONVERT MONTH
*   \brief: converts the month buffer in int
*   \Parameters:
*       @param buffer: 8-bit buffer with information
*   \Return: month
*/
uint8_t RTC_convert_month(uint8_t* buffer) {
    
    uint8_t month = 0;
    
    for(int i = 0; i < 3; i++) {
        if(*(buffer+i) & (0b00000001<<i)) {
            month += pow(2,i);
        }
    }
    
    month += 10*(*(buffer+4));
    
    return month;
}

/*  RTC CONVERT YEAR
*   \brief: converts the year buffer in int
*   \Parameters:
*       @param buffer: 8-bit buffer with information
*   \Return: year
*/
uint8_t RTC_convert_year(uint8_t* buffer) {
    
    uint8_t year = 0;
    
    //Bits 0-3 that converts for units
    for(int i = 0; i < 4; i++) {
        if(*(buffer+i) & (0b00000001<<i)) {
            year += pow(2,i);
        }
    }
    
    //Bits 4-7 that converts for units
    for(int j = 4; j < 8; j++) {
        if(*(buffer+j) & (0b00000001<<j)) {
            year += 10*pow(2,j-4);
        }
    }
    
    return year;
} 

/* [] END OF FILE */
