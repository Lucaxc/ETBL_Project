/* =====================================================
 *
 * ELECTRONIC TECHNOLOGIES AND BIOSENSORS LABORATORY
 * Academic year 2021/22, II Semester
 * Final Project

 * Authors: Group 2
 *
 * ----------- OLED Driver (header) -------------
 * 
 * -----------------------------------------------------
 * 
 * =====================================================
*/
#include <project.h>

#ifndef _OLED_DRIVER_H
#define _OLED_DRIVER_H
    
#define BLACK 0
#define WHITE 1
#define INVERSE 2 
    
void display_init(uint8_t oled_i2c_address);
void display_clear(); 
void display_status(char status);
void display_update();
void display_setPixel(int16_t x, int16_t y, uint16_t color);


#endif
/* [] END OF FILE */
