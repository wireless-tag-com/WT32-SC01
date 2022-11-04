#include <stdio.h>
#include "sdkconfig.h"

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_heap_caps.h"
#include "screen_driver.h"
#include "board.h"
#include "driver/gpio.h"

extern esp_err_t lcd_st7796_set_invert(bool is_invert);

void screen_init(scr_driver_t* s_lcd, SemaphoreHandle_t semaphore) {
    spi_config_t bus_conf = {
        .miso_io_num = -1,
        .mosi_io_num = LCD_SPI_MOSI,
        .sclk_io_num = LCD_SPI_SCLK,
        .max_transfer_sz = LCD_LVGL_BUF_SIZE * 2,
    };
    void *s_spi2_bus_handle = spi_bus_create(SPI2_HOST, &bus_conf);
    scr_interface_spi_config_t spi_lcd_cfg = {
        .spi_bus = s_spi2_bus_handle,
        .pin_num_cs = LCD_SPI_CS,
        .pin_num_dc = LCD_DC,
        .clk_freq = 26000000,
        .swap_data = true,
    };
    scr_interface_driver_t *iface_drv = NULL;
    scr_interface_create(SCREEN_IFACE_SPI, &spi_lcd_cfg, &iface_drv);
    extern scr_driver_t lcd_st7796_default_driver;
    *s_lcd = lcd_st7796_default_driver;

    scr_controller_config_t lcd_cfg = {
        .interface_drv = iface_drv,
        .pin_num_rst = LCD_RESET_PIN,
        .pin_num_bckl = LCD_BL_PIN,
        .rst_active_level = 0,
        .bckl_active_level = 1,
        .offset_hor = 0,
        .offset_ver = 0,
        .width = 320,
        .height = 480,
        .rotate =  SCR_DIR_TBLR,
    };
    s_lcd->init(&lcd_cfg);
    
    lcd_st7796_set_invert(false);
}
