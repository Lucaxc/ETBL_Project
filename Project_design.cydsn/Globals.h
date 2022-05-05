/* ========================================================================
 *
 * ELECTRONIC TECHNOLOGIES AND BIOSENSORS LABORATORY
 * Academic year 2021/22, II Semester
 * Final Project

 * Authors: Group 2
 *
 * ------------------------ GLOBALS (header) --------------------------
 * 
 * ------------------------------------------------------------------------
 * 
 * ========================================================================
*/
#include "project.h"

// OLED GRAPHIC LOGOS
const uint8_t epd_bitmap_cropped_POLIMI_bianco [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x6d, 0xdb, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0xc0, 0x01, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x10, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x03, 0x71, 0x11, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xc3, 0xf8, 0x02, 0x2c, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x8a, 0x44, 0x3c, 0xef, 0xa0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0x24, 0x84, 0x1d, 0xfd, 0x80, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x60, 0x07, 0xa3, 0x23, 0x18, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x13, 0x0d, 0xa0, 0x8f, 0xf0, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x19, 0xd4, 0xc0, 0xc2, 0x81, 0x1c, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x31, 0x81, 0x0a, 0x54, 0x43, 0xfd, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x21, 0x8c, 0x13, 0x63, 0xac, 0x55, 0x03, 0x0e, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x71, 0x80, 0x90, 0x73, 0x88, 0x56, 0x84, 0x04, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x63, 0xa0, 0xc0, 0x81, 0x20, 0x19, 0xe0, 0x87, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x63, 0x20, 0x28, 0xa3, 0x2f, 0xa8, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xe3, 0x20, 0x2f, 0xc0, 0xc8, 0x41, 0x41, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x63, 0x00, 0x68, 0x41, 0x49, 0x8e, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xe3, 0x24, 0x00, 0x3b, 0x49, 0x0c, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x05, 0x26, 0x08, 0x52, 0x51, 0x0c, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xf4, 0xa0, 0x10, 0x42, 0x38, 0x41, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x88, 0x62, 0x61, 0xe6, 0x28, 0xc1, 0x86, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x70, 0xb0, 0x07, 0xa4, 0x6a, 0x62, 0x41, 0x83, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x10, 0x60, 0x09, 0x24, 0x52, 0xdc, 0xc1, 0x0e, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x0f, 0xe8, 0xe4, 0x10, 0x50, 0x31, 0x08, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x18, 0x10, 0x26, 0x9a, 0x74, 0x88, 0x11, 0x1c, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x14, 0x1f, 0x00, 0x73, 0x23, 0x11, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x07, 0x80, 0x40, 0x70, 0x12, 0x98, 0x38, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0x38, 0x70, 0x80, 0x7f, 0x10, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0x88, 0x3a, 0x4c, 0x4e, 0xc0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x01, 0x8d, 0xf6, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x0f, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x40, 0x00, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x6c, 0xd9, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0xda, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xfe, 0x01, 0xf8, 0x1c, 0x03, 0x1f, 0xf3, 0xfe, 0x07, 0xf0, 0xc0, 0x71, 0xc0, 0xfe, 0x03, 0xf0, 
	0xff, 0x87, 0xfe, 0x1c, 0x07, 0x1f, 0xf3, 0xfe, 0x1f, 0xf8, 0xe0, 0x71, 0xc3, 0xff, 0x1f, 0xfc, 
	0xe3, 0xcf, 0x0f, 0x1c, 0x07, 0x03, 0x83, 0x80, 0x3c, 0x10, 0xf0, 0x71, 0xc7, 0x82, 0x3c, 0x1e, 
	0xe1, 0xdc, 0x03, 0x9c, 0x07, 0x03, 0x83, 0x80, 0x78, 0x00, 0xfc, 0x71, 0xcf, 0x00, 0x38, 0x07, 
	0xff, 0x9c, 0x03, 0x9c, 0x07, 0x03, 0x83, 0xfc, 0x70, 0x00, 0xee, 0x71, 0xce, 0x00, 0x38, 0x07, 
	0xff, 0x1c, 0x03, 0x9c, 0x07, 0x03, 0x83, 0xfc, 0x70, 0x00, 0xe7, 0xf1, 0xce, 0x00, 0x38, 0x07, 
	0xe0, 0x1e, 0x07, 0x9c, 0x07, 0x03, 0x83, 0x80, 0x38, 0x00, 0xe3, 0xf1, 0xcf, 0x00, 0x3c, 0x0f, 
	0xe0, 0x0f, 0x9f, 0x1c, 0x07, 0x03, 0x83, 0x80, 0x3e, 0x38, 0xe0, 0xf1, 0xc7, 0xcf, 0x1f, 0x3e, 
	0xe0, 0x07, 0xfe, 0x1f, 0xf7, 0x03, 0x83, 0xfe, 0x0f, 0xf8, 0xe0, 0x71, 0xc1, 0xff, 0x0f, 0xfc, 
	0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x38, 0x00, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x86, 0x33, 0x00, 0xc1, 0x86, 0x3f, 0xc0, 0xe3, 0xf1, 0xc7, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x8e, 0x33, 0x01, 0xe1, 0xc6, 0x60, 0x60, 0xe3, 0x33, 0x00, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xcf, 0x33, 0x03, 0x21, 0x76, 0x60, 0x60, 0x63, 0xe7, 0xe3, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x7b, 0x33, 0x03, 0x31, 0x1e, 0x60, 0x60, 0x63, 0xf6, 0x30, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x73, 0x33, 0x07, 0xf9, 0x0e, 0x70, 0xe0, 0x62, 0x36, 0x30, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x33, 0x33, 0xfc, 0x09, 0x06, 0x1f, 0x81, 0xf3, 0xf3, 0xe7, 0xc0, 0x00, 0x00
};

const uint8_t epd_bitmap_CV1[] = {
	0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x47, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0x80, 0x1c, 0x7f, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0x00, 0x1e, 0x07, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x02, 0x0f, 0x1e, 0x00, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x05, 0x00, 0x04, 0x7f, 0x86, 0x00, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x04, 0xff, 0xc2, 0x00, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x0e, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0x00, 0xff, 0xfe, 0xf8, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10, 0x62, 0x00, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x32, 0x00, 0x1f, 0xf9, 0x90, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf6, 0x00, 0x1b, 0xfc, 0x18, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xf6, 0x00, 0x03, 0xff, 0xf8, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xe6, 0x00, 0x0f, 0xf9, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0xc3, 0xe6, 0x30, 0x07, 0xec, 0x7c, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x07, 0xf8, 0x7c, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x80, 0x0f, 0xc0, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x02, 0x00, 0x00, 0x70, 0x03, 0x00, 0x07, 0xf8, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x07, 0xfc, 0x7c, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x64, 0x10, 0x00, 0x03, 0xf8, 0x48, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x18, 0x36, 0x00, 0x01, 0xe8, 0x18, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0xcc, 0x60, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x40, 0x70, 0x00, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x00, 0x01, 0xc0, 0x20, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3c, 0xff, 0xfe, 0x00, 0x03, 0x80, 0x30, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x21, 0xe0, 0x7f, 0xf1, 0x80, 0x03, 0xc0, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0x80, 0x1f, 0xe1, 0xf0, 0x07, 0xd8, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x38, 0x07, 0x3c, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x00, 0xc0, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0xf4, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x20, 0x60, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x98, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x60, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x02, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x02, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x4e, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x0f, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x4f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x5f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7b, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x10, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7b, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x33, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x83, 0xc0, 0x01, 0xf8, 0x00, 0x00, 0xf9, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x83, 0xe0, 0x01, 0xf0, 0x00, 0x00, 0xb2, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff
};

const uint8_t epd_bitmap_teo[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x40, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x04, 0x20, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x38, 0x60, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x20, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0xa0, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x12, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc8, 0x00, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x44, 0x00, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x1e, 0x24, 0x00, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0xc2, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x72, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x0e, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfd, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x30, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x01, 0xe1, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x01, 0x80, 0x00, 0x80, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x04, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0x06, 0x20, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x87, 0x03, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x06, 0x1f, 0xff, 0x03, 0x80, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0x8e, 0x07, 0x20, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x67, 0x06, 0x0f, 0x60, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x40, 0x00, 0x67, 0xff, 0x3f, 0xc2, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x30, 0x00, 0x2f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x32, 0x00, 0x27, 0xff, 0xff, 0x60, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x02, 0x3f, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x01, 0x9e, 0x00, 0x17, 0xff, 0xff, 0x80, 0x00, 0x00, 0x04, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x20, 0x9c, 0x00, 0x13, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x20, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x98, 0x00, 0x03, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0xd0, 0x00, 0x03, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x01, 0xb0, 0x00, 0x03, 0xef, 0x9f, 0x00, 0x00, 0x00, 0x40, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x11, 0x70, 0x00, 0x01, 0xe7, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x01, 0xf0, 0x00, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x01, 0xc0, 0x00, 0x00, 0xff, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x09, 0x80, 0x00, 0x00, 0x7f, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x8d, 0x80, 0x00, 0x01, 0x3f, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x08, 0x00, 0x00, 0x01, 0x8f, 0xce, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xc2, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x10, 0x00, 0x80, 0x07, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xdc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x80, 0x00, 0x0f, 0xef, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x02, 0x5f, 0xf7, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x18, 0x00, 0x0f, 0xff, 0xf3, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0x13, 0x07, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xfc, 0x07, 0xc3, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff
};

const uint8_t epd_bitmap_Squarda_ginew[] = {
	0xfe, 0x00, 0x00, 0x0c, 0x7f, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xf4, 0x00, 0x06, 0x07, 0xff, 0xff, 
	0xfe, 0x00, 0x00, 0x5c, 0x3f, 0xff, 0xfc, 0x81, 0x1f, 0xff, 0xfd, 0x43, 0x00, 0xc1, 0xd7, 0xff, 
	0xfe, 0x00, 0x00, 0x7c, 0x3f, 0xff, 0xfc, 0x06, 0x1f, 0xfe, 0xa9, 0x4c, 0x00, 0x11, 0x7a, 0xff, 
	0xfe, 0x00, 0x00, 0xf8, 0x1f, 0xff, 0xfe, 0x03, 0xfe, 0x56, 0xaa, 0xb8, 0x00, 0x09, 0x6a, 0xff, 
	0xfe, 0x00, 0x01, 0xc4, 0x0f, 0xff, 0xff, 0x1f, 0xfc, 0x00, 0x6a, 0xb0, 0x00, 0x04, 0xaa, 0xff, 
	0xfe, 0x00, 0x01, 0x1e, 0x07, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7a, 0x90, 0x00, 0x04, 0xa0, 0xff, 
	0xfe, 0x00, 0x01, 0x5c, 0x07, 0x9b, 0xff, 0x7f, 0xe0, 0x02, 0x7a, 0x90, 0x02, 0x04, 0x00, 0xff, 
	0xff, 0x80, 0x00, 0x7f, 0x07, 0xa1, 0xff, 0xef, 0x10, 0x0f, 0x00, 0x10, 0x00, 0x04, 0x00, 0xff, 
	0xff, 0xe0, 0x00, 0x7f, 0x0d, 0x87, 0xff, 0xff, 0xff, 0x88, 0x80, 0x10, 0x00, 0x04, 0x00, 0xff, 
	0xff, 0xf0, 0x00, 0x7f, 0x3d, 0x0f, 0x03, 0x16, 0xff, 0xfe, 0x00, 0x18, 0x00, 0x0c, 0x00, 0xff, 
	0xff, 0xfc, 0x00, 0x3f, 0x36, 0x0d, 0xfe, 0x77, 0xff, 0xff, 0xc0, 0x08, 0x00, 0x08, 0x00, 0xff, 
	0xff, 0xff, 0x80, 0x3e, 0x04, 0x0d, 0xf3, 0x9f, 0xff, 0xff, 0xe0, 0x04, 0x00, 0x10, 0x17, 0xff, 
	0xff, 0xff, 0x40, 0x1d, 0xf8, 0x05, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0x00, 0x60, 0x3f, 0xff, 
	0xff, 0xff, 0xf0, 0x6b, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xc1, 0x80, 0x3f, 0xff, 
	0xff, 0xdf, 0xf8, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x40, 0x00, 0x36, 0x00, 0x7f, 0xff, 
	0xff, 0xff, 0xfb, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0x64, 0x00, 0x18, 0x00, 0x7f, 0xff, 
	0xff, 0xff, 0xf7, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe2, 0x00, 0x08, 0x00, 0xff, 0xff, 
	0xff, 0xf6, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x81, 0x80, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xe4, 0xef, 0xff, 0xc8, 0x07, 0xff, 0xff, 0xff, 0xfd, 0xc1, 0xe0, 0x00, 0x01, 0xff, 0xff, 
	0xff, 0xef, 0x1f, 0xff, 0x98, 0x27, 0xff, 0xff, 0xff, 0xff, 0x00, 0xe1, 0x80, 0x03, 0xff, 0xff, 
	0xff, 0x74, 0x6f, 0xff, 0xb0, 0x17, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xe1, 0x80, 0x03, 0xff, 0xff, 
	0xff, 0xf0, 0x2f, 0xfd, 0x0c, 0x17, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xc0, 0x00, 0x03, 0xfc, 0xff, 
	0xff, 0xc0, 0x23, 0xbe, 0x3c, 0x17, 0xff, 0xff, 0xff, 0x60, 0xa0, 0xf0, 0x00, 0x03, 0xe0, 0xff, 
	0xff, 0xb0, 0x00, 0x7c, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 0x00, 0x03, 0x00, 0xff, 
	0xff, 0xe0, 0x1f, 0x05, 0x1c, 0x1f, 0xff, 0xff, 0xff, 0xcc, 0x00, 0x78, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xe0, 0x04, 0x06, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0x7c, 0xb0, 0xfc, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xd0, 0x0f, 0xfb, 0xcc, 0x3f, 0xff, 0xff, 0xff, 0xf9, 0xf0, 0xfe, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0x78, 0x3c, 0x02, 0x7c, 0x3f, 0xff, 0xff, 0xff, 0xe7, 0x30, 0x7c, 0x00, 0x00, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe4, 0x1f, 0xff, 0xff, 0xfc, 0x0f, 0x22, 0x7e, 0x00, 0x04, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xc1, 0x18, 0x1f, 0xff, 0xff, 0xdf, 0xef, 0x72, 0x7c, 0x00, 0x04, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x80, 0x27, 0xff, 0xfe, 0x1c, 0x67, 0x73, 0x3c, 0x01, 0x88, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x80, 0x41, 0xf8, 0x40, 0x0c, 0x00, 0xf7, 0x3c, 0x01, 0xf8, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0xff, 0x00, 0xfc, 0x00, 0x00, 0x2a, 0x07, 0x3c, 0x01, 0xf8, 0x00, 0xff, 
	0xfe, 0x00, 0xff, 0xff, 0xf8, 0x0a, 0xaa, 0x00, 0x00, 0x2a, 0x83, 0xbc, 0x01, 0xf0, 0x00, 0xff, 
	0xfe, 0x00, 0x00, 0x60, 0x01, 0x32, 0xaa, 0x00, 0x40, 0x2c, 0x01, 0xbc, 0x00, 0xf0, 0x00, 0xff, 
	0xfe, 0x00, 0x00, 0x20, 0x00, 0xa8, 0xaa, 0x03, 0xc0, 0x38, 0x10, 0xb8, 0x01, 0xe0, 0x00, 0xff, 
	0xfe, 0x00, 0x00, 0xc0, 0x00, 0x40, 0x0a, 0x01, 0x08, 0x00, 0x02, 0xb0, 0x01, 0xe0, 0x00, 0xff, 
	0xfe, 0x00, 0x00, 0x80, 0x07, 0x20, 0x00, 0x00, 0x20, 0x00, 0x80, 0x30, 0x01, 0xe0, 0x00, 0xff, 
	0xfe, 0x00, 0x01, 0x00, 0x0f, 0x08, 0x00, 0x4f, 0xc4, 0x01, 0xc0, 0x10, 0x01, 0xe0, 0x00, 0xff, 
	0xfe, 0x00, 0x01, 0x00, 0x0a, 0x05, 0xc0, 0x0a, 0x00, 0x01, 0xc0, 0x08, 0x00, 0x00, 0x00, 0xff, 
	0xfe, 0x00, 0x02, 0x00, 0x1a, 0x01, 0x10, 0x02, 0x00, 0x39, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0xff, 
	0xfe, 0x00, 0x02, 0x00, 0x7f, 0x81, 0xf8, 0x00, 0x00, 0x3c, 0x80, 0x0c, 0x1f, 0x40, 0x00, 0xff, 
	0xfe, 0x00, 0x04, 0x10, 0x9c, 0x03, 0xf6, 0x00, 0xc0, 0x7e, 0x80, 0x30, 0x0f, 0xff, 0x00, 0xff, 
	0xfe, 0x00, 0x04, 0x00, 0x80, 0x07, 0xef, 0x80, 0x00, 0xff, 0x40, 0x78, 0x0f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x08, 0xc0, 0x00, 0x0d, 0xcf, 0xc0, 0x00, 0xff, 0x60, 0x7c, 0x0f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x08, 0xf4, 0x00, 0x3c, 0x0d, 0x60, 0x01, 0xff, 0x68, 0x3a, 0x0f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x0c, 0xf4, 0x3e, 0x3d, 0x1f, 0xb0, 0x00, 0xf8, 0x73, 0xdc, 0x0f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x00, 0x5c, 0x3e, 0x1f, 0xff, 0x90, 0x00, 0x51, 0xe3, 0xec, 0x1f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x1f, 0xbc, 0x38, 0x0f, 0xff, 0xd0, 0x00, 0x20, 0xc1, 0xfc, 0x1f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0x7f, 0xee, 0x3d, 0x87, 0xff, 0xc0, 0x00, 0x00, 0x81, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
	0xfe, 0x00, 0xff, 0x1f, 0x33, 0x8f, 0xef, 0xc0, 0x08, 0x00, 0xc3, 0xfe, 0x0f, 0xff, 0xff, 0xff, 
	0xfe, 0x01, 0xfd, 0x7f, 0xc7, 0x5f, 0xfe, 0xf8, 0x00, 0x00, 0xfd, 0xff, 0xc7, 0xff, 0xff, 0xff, 
	0xfe, 0x03, 0xfc, 0xe3, 0xde, 0x7f, 0xfe, 0xd8, 0x0f, 0x80, 0xfb, 0x1f, 0xe7, 0xff, 0xff, 0xff, 
	0xfe, 0x1f, 0xfd, 0xe0, 0x29, 0x1f, 0xff, 0xd0, 0x1f, 0xc0, 0xfe, 0x3f, 0xe7, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x07, 0xf0, 0x18, 0x1f, 0xcf, 0xfe, 0xbf, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x03, 0xf0, 0x10, 0x2f, 0xd7, 0xff, 0xfb, 0xfb, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0x3f, 0xe0, 0x00, 0x01, 0xf0, 0x3f, 0xfd, 0xfb, 0xff, 0xb3, 0xdf, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0xbf, 0xe0, 0x00, 0x01, 0xf0, 0x3f, 0xed, 0xeb, 0xff, 0xf1, 0xfd, 0xff, 0xff, 0xff, 
	0xff, 0xfe, 0xff, 0xc0, 0x7e, 0x01, 0x78, 0x1f, 0xe5, 0xeb, 0xff, 0xc1, 0xef, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe1, 0xfd, 0x83, 0xf8, 0x3f, 0xe9, 0xe3, 0xff, 0x41, 0xe3, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xf8, 0x7f, 0xe8, 0xdb, 0xff, 0x83, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x1b, 0xff, 0xff, 0xf0, 0xf3, 0xfe, 0x82, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xbf, 0xff, 0xe0, 0x39, 0xf0, 0xff, 0xf0, 0x7f, 0xfe, 0x00, 0x00, 0x5f, 0xff, 0xff, 
	0xff, 0xff, 0x9f, 0xff, 0xc0, 0x15, 0xfe, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xff
};

const uint8_t Fan1 [] = {
0x00, 0x3F, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x01, 0xF0, 0x0F, 0x80, 0x07, 0xC0, 0x03, 0xE0,
0x0F, 0x3E, 0x00, 0xF0, 0x1E, 0x7F, 0x80, 0x78, 0x1C, 0x7F, 0x80, 0x3C, 0x38, 0x7F, 0xC0, 0x1C,
0x30, 0x7F, 0xC0, 0x0C, 0x70, 0x7F, 0xC0, 0x0E, 0x60, 0x7F, 0xC0, 0x06, 0xE0, 0x1F, 0xC0, 0x07,
0xE0, 0x0F, 0xC0, 0x07, 0xC0, 0x04, 0x00, 0xC3, 0xC0, 0x03, 0xC3, 0xF3, 0xC0, 0x03, 0xDF, 0xF3,
0xC0, 0x3B, 0xCF, 0xFB, 0xC0, 0x7B, 0xDF, 0xFB, 0xC0, 0xFC, 0x3F, 0xF3, 0xE1, 0xFE, 0x3F, 0xF7,
0xE1, 0xFE, 0x1F, 0xE7, 0x61, 0xFE, 0x07, 0x86, 0x71, 0xFC, 0x00, 0x0E, 0x31, 0xFC, 0x00, 0x0C,
0x39, 0xFC, 0x00, 0x1C, 0x18, 0xFC, 0x00, 0x1C, 0x1C, 0x78, 0x00, 0x38, 0x0F, 0x00, 0x00, 0xF0,
0x07, 0x80, 0x01, 0xE0, 0x03, 0xF0, 0x0F, 0xC0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x3F, 0xFC, 0x00
};

// RTC USER-CHANGING GLOBALS
uint8_t current_seconds;
uint8_t current_minutes;
uint8_t current_hours;
uint8_t current_day;
uint8_t current_month;
uint8_t current_year;

/* [] END OF FILE */
