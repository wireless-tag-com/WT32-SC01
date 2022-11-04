#pragma once
#include "screen_driver.h"

#define INTERFACE_I2S_8

#define LCD_RESET_PIN 22

#define LCD_WIDTH 320
#define LCD_HIGHT 480

#define LCD_SPI_CS  15
#define LCD_SPI_MOSI  13
#define LCD_SPI_SCLK  14
#define LCD_DC 21

//backlight pwm I/O
#define LCD_BL_PIN 23

#define TP_SDA  18
#define TP_SCL  19

#define LCD_LVGL_BUF_SIZE   (480 * 40)
