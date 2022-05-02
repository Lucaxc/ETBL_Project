/* ========================================================================
 *
 * ELECTRONIC TECHNOLOGIES AND BIOSENSORS LABORATORY
 * Academic year 2021/22, II Semester
 * Final Project

 * Authors: Group 2
 *
 * ------------------------ OLED Driver (source) --------------------------
 * 
 * ------------------------------------------------------------------------
 * 
 * ========================================================================
*/

#include <project.h>
#include <stdlib.h>

#include "OLED_Driver.h"

/*------------------------------------------------------------------------
*                        OLED DISPLAY REGISTERS
-------------------------------------------------------------------------*/
// DEVICE ADDRESS
#define DISPLAY_ADDRESS                 0x3D    //It can be also 0x3C

// DISPLAY DIMENSIONS
#define DISPLAY_WIDTH                    128
#define DISPLAY_HEIGHT                   64

// FUNDAMENTAL COMMANDS
#define DISPLAY_ON                      0xAF
#define DISPLAY_RESET                   0x7F
#define DISPLAY_CONTRAST                0x81    //Followed by 0xNN for contrast level (value between 0 and 255)
#define DISPLAY_OFF                     0xAE

#define DISPLAY_ALL_ON_RESUME           0xA4    //RAM content displayed
#define DISPLAY_ALL_ON                  0xA5    //Display all white

#define DISPLAY_NORMAL                  0xA6
#define DISPLAY_INVERSE                 0xA7

// ADDRESSING SETTING COMMANDS
#define DISPLAY_LOWER_NIBBLE            0x00    //Followed by 0x0F
#define DISPLAY_UPPER_NIBBLE            0x10    //Followed by 0x1F
#define DISPLAY_SET_MEMORY              0x20    //Followed by: 00b Horizontal addressing, 01b Vertical addressing, 10b Page addressing
#define DISPLAY_SET_MEMORY_HORIZONTAL   0x00
#define DISPLAY_SET_MEMORY_VERTICAL     0x01
#define DISPLAY_SET_MEMORY_PAGE         0x02
#define DISPLAY_SET_COLUMN_ADDR         0x21    //2 bytes param 0-127 for start and 0-127 for end addresses
#define DISPLAY_SET_PAGE_ADDR           0x22    //2 bytes param 0-7 for start and 0-7 for end addresses

// HARDWARE SETTING COMMANDS
#define DISPLAY_START_LINE              0x40   
#define DISPLAY_SEGREMAP                0xA0    //Segment to column address 0
#define DISPLAY_MULTIPLEX               0xA8
#define DISPLAY_COM_OUTPUT              0xC0    //From COM0 to COM(N-1)
#define DISPLAY_COM_OUTPUT_INV          0xC8    //From COM(N-1) to COM0
#define DISPLAY_COM_PINS                0xDA
#define DISPLAY_OFFSET                  0xD3

// TIMING SETTINGS
//Non so se serva mettere il refresh rate ecc
#define DISPLAY_PRECHARGE               0xD9

// CHARGE PUMP SETTINGS
#define DISPLAY_CHARGEPUMP              0x8D
#define DISPLAY_CHARGEPUMP_ON           0x14
#define DISPLAY_CHARGEPUMP_OFF          0x10

// I2C TRANSFER RESULT STATUS
#define TRANSFER_CMPLT                  0x00u
#define TRANSFER_ERROR                  0xFFu

/*------------------------------------------------------------------------
*                         STATIC VARIABLES
-------------------------------------------------------------------------*/
static uint8_t oled_i2c_address;
static uint8_t DISPLAY_buffer[DISPLAY_HEIGHT * DISPLAY_WIDTH / 8 + 1] = {0x40};     //Dimension increased by 1 with respect to pixel number to include 0x40 to submit data in position [0]
static uint8_t* display_buf = DISPLAY_buffer+1;                                     //Pointer to next memory cell
static uint8_t display_buf_size = sizeof(display_buf)-1;                            //-1 because we have to subtract the starting command 0x40

// RAM SETTINGS
#define GDDRAM_ADDRESS(X,Y)             ((display_buf)+((Y)/8)*(DISPLAY_WIDTH)+(X))

#define GDDRAM_PIXMASK(Y)               (1 << ((Y)&0x07))

#define PIXEL_ON(X,Y)                   (*GDDRAM_ADDRESS(x,y) |= GDDRAM_PIXMASK(y))
#define PIXEL_OFF(X,Y)                  (*GDDRAM_ADDRESS(x,y) &= ~GDDRAM_PIXMASK(y))
#define PIXEL_TOGGLE(X,Y)               (*GDDRAM_ADDRESS(x,y) ^= GDDRAM_PIXMASK(y))


/*------------------------------------------------------------------------
*                       STATIC FUNCTIONS DECLARATION
-------------------------------------------------------------------------*/
static uint32 display_write_buffer(uint8_t* buffer, uint16_t size);

/*------------------------------------------------------------------------
*                       FUNCTIONS IMPLEMENTATION
-------------------------------------------------------------------------*/

/*  DISPLAY INIT
*   \brief: Display initialization function.
            NB: if configuration commands has to be sent, the buffer must
                start with 0x00. Otherwise, if data has to be sent, with
                0x40.
*   \parameters:
*       @param oled_address: 8-bit address identifing the OLED screen
*/
void display_init(uint8_t oled_address) {
    
    oled_i2c_address = oled_address;
    
    uint8_t cmdbuffer[] = {
        0x00,                           //Every time a command sequence is sent the buffer has to start with 0x00
        DISPLAY_OFF,
        DISPLAY_MULTIPLEX,
        0x3F,                           //Reset value 0b00111111
        DISPLAY_OFFSET,
        0x00,                           //No offset
        DISPLAY_START_LINE | 0x0,
        DISPLAY_CHARGEPUMP,
        0x14,                           //Charge pump enabled. 0x10 to disable
        DISPLAY_SET_MEMORY,
        0x00,                           //Horizontal addressing
        DISPLAY_SEGREMAP | 0x1,
        DISPLAY_COM_OUTPUT_INV,
        DISPLAY_COM_PINS,
        0x12,
        DISPLAY_CONTRAST,
        0x7F,                           //Reset value
        DISPLAY_PRECHARGE,
        0xF1,
        DISPLAY_ALL_ON_RESUME,
        DISPLAY_NORMAL,
        DISPLAY_ON
    };
    
    display_write_buffer(cmdbuffer, sizeof(cmdbuffer));
}

/*  DISPLAY WRITE BUFFER
*   \brief: Sends the addresses and content to OLED screen to set it up.
*   \Parameters:
*       @param buffer: data to be sent to the OLED screen
*       @param size: size of @param(buffer)
*   \Return: Transfer result
*/
static uint32 display_write_buffer(uint8_t* buffer, uint16_t size) {
    
    uint32 status = TRANSFER_ERROR;
    I2COLED_MasterSendStart(oled_i2c_address, I2COLED_WRITE_XFER_MODE);
    
    for(int i=0; i<size; i++){  
        status=I2COLED_MasterWriteByte(buffer[i]);
    }
    I2COLED_MasterSendStop();
    return status;
}

/*  DISPLAY SET PIXEL
*   \brief: Function that changes the pixel status (ON/OFF).
*   \Parameters:
*       @param x: x coordinate of the pixel
*       @param y: y coordinate of the pixel
*       @param color: color to be set. Black, white or change with respect to the previous
*/
void display_setPixel(int16_t x, int16_t y, uint16_t color) {
    
    if((x < 0) || (x >= DISPLAY_WIDTH) || (y < 0) || (y >= DISPLAY_HEIGHT))
        return;

    switch(color) {
        case WHITE: 
            PIXEL_ON(x,y);
        break;
            
        case BLACK:
            PIXEL_OFF(x,y);
        break;
            
        case INVERSE: 
            PIXEL_TOGGLE(x,y);
        break;
    }
}

/*  DISPLAY RESET
*   \brief: Function that reset the display buffer content.
*   \Parameters: NONE
*/
void display_clear() {
    memset(display_buf, 0, display_buf_size);       
    DISPLAY_buffer[0] = 0x40;                       //Rewriting 0x40 to send data
}

/*  DISPLAY SET CONTRAST
*   \brief: Function that sets the display contrast.
*   \Parameters:
*       @param contrast: value comprised between 0 and 255 corresponding
*                        to screen contrast value
*/
void set_display_contrast(uint8_t contrast) {
        
    uint8 cmdbuffer[] = {
        0x00,  
        DISPLAY_CONTRAST,
        contrast
    };
    
    display_write_buffer(cmdbuffer, sizeof(cmdbuffer)); 
}

/*  DISPLAY SET STATUS
*   \brief: Function that inverts the pixel values.
*   \Parameters:
*       @param status: defines if the screen has to be normal (0)
*                      or inverted (1)
*/
void display_status(char status) {
    
    uint8_t cmdbuffer[2] = {0x00, 0x00};
    
    switch (status) {
    case 0:
        cmdbuffer[1] = DISPLAY_NORMAL;
    break;
        
    case 1:
        cmdbuffer[1] = DISPLAY_INVERSE;
    break;
    }
    
    display_write_buffer(cmdbuffer, sizeof(cmdbuffer));
}

/*  DISPLAY UPDATE
*   \brief: Function that reset the indexes for column and page
*           and rewrites memory value in the DISPLAY_buffer on
*           the display.
*   \Parameters: NONE
*/
void display_update() {
      
    uint8 cmdbuffer[] = {
        0x00,
        DISPLAY_SET_COLUMN_ADDR,
        0,                      
        DISPLAY_WIDTH-1,
        DISPLAY_SET_PAGE_ADDR,
        0,                      
        7                               //Total of 8 pages in the screen (end)                
    };
    display_write_buffer(cmdbuffer, sizeof(cmdbuffer)); 
    display_write_buffer(DISPLAY_buffer, sizeof(DISPLAY_buffer));
}
/* [] END OF FILE */
