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

#define DISPLAY_ON              0xAF
#define DISPLAY_RESET           0x7F
#define DISPLAY_CONTRAST        0x81    //Followed by 0xNN for contrast level
#define DISPLAY_OFF             0xAE

#define DISPLAY_ALL_ON_RESUME   0xA4    //RAM content displayed
#define DISPLAY_ALL_ON          0xA5    //Display all white

#define DISPLAY_NORMAL          0xA6
#define DISPLAY_INVERSE         0xA7





/* [] END OF FILE */
