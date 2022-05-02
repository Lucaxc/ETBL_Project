/* =====================================================
 *
 * ELECTRONIC TECHNOLOGIES AND BIOSENSORS LABORATORY
 * Academic year 2021/22, II Semester
 * Final Project

 * Authors: Group 2
 *
 * ----------- OLED Driver (source) -------------
 * 
 * -----------------------------------------------------
 * 
 * =====================================================
*/

// DISPLAY DIMENSIONS
#define DISPLAYWIDTH                    128
#define DISPLAYHEIGHT                   64

// FUNDAMENTAL COMMANDS
#define DISPLAY_ON                      0xAF
#define DISPLAY_RESET                   0x7F
#define DISPLAY_CONTRAST                0x81    //Followed by 0xNN for contrast level
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
#define DISPLAU_SET_PAGE_ADDR           0x22    //2 bytes param 0-7 for start and 0-7 for end addresses

// HARDWARE SETTING COMMANDS
#define DISPLAY_START_LINE              0x40   
#define DISPLAY_SEGREMAP                0xA0    //Segment to column address 0
#define DISPLAY_COM_OUTPUT              0xC0
#define DISPLAY_COM_PINS                0xDA

// TIMING SETTINGS
//Non so se serva mettere il refresh rate ecc

// CHARGE PUMP SETTINGS
#define DISPLAY_CHARGEPUMP              0x8D
#define DISPLAY_CHARGEPUMP_ON           0x14
#define DISPLAY_CHARGEPUMP_OFF          0x10



/* [] END OF FILE */
