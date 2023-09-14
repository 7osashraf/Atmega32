/*
 * lcd.h
 *
 * Created: 9/13/2023 1:44:27 AM
 *  Author: ENG HOSAM
 */ 


#ifndef LCD_H_
#define LCD_H_

/* ------------------Includes------------------*/
#include "../../MCAL/DIO/dio.h"

/* ------------------Macro Declarations------------------*/
#define _LCD_CLEAR                              0X01
#define _LCD_RETURN_HOME                        0X02
#define _LCD_ENTRY_MODE                         0X06
#define _LCD_CURSOR_OFF_DISPLAY_ON              0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF             0X08
#define _LCD_CURSOR_ON							0X0E
#define _LCD_CURSOR_OFF							0X0C
#define _LCD_CURSOR_ON_BLINK_ON                 0X0F
#define _LCD_DIPLAY_SHIFT_RIGHT                 0X14
#define _LCD_DIPLAY_SHIFT_LEFT                  0X18
#define _LCD_8BIT_MODE_2_LINE                   0X38
#define _LCD_4BIT_MODE_2_LINE                   0X28
#define _LCD_CGRAM_START                        0X40
#define _LCD_DDRAM_START                        0X80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef struct{
	ST_Pin_Config_t lcd_rs;
	ST_Pin_Config_t lcd_en;
	ST_Pin_Config_t lcd_data[4];
}ST_chr_lcd_4bit_t;



/* ------------------Software Interface Declarations------------------*/
EN_errorReturn_t lcd_4bit_initialize(const ST_chr_lcd_4bit_t *lcd);
EN_errorReturn_t lcd_4bit_send_command(const ST_chr_lcd_4bit_t *lcd, uint8 command);
EN_errorReturn_t lcd_4bit_send_char_data(const ST_chr_lcd_4bit_t *lcd, uint8 data);
EN_errorReturn_t lcd_4bit_send_char_data_pos(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 data);
EN_errorReturn_t lcd_4bit_send_string(const ST_chr_lcd_4bit_t *lcd, uint8 *str);
EN_errorReturn_t lcd_4bit_send_string_pos(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 *str);
EN_errorReturn_t lcd_4bit_send_custome_char(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 col,
const uint8 _chr[], uint8 mem_pos) ;



EN_errorReturn_t convert_uint8_to_string(uint8 value, uint8 *str);
EN_errorReturn_t convert_uint16_to_string(uint16 value, uint8 *str);
EN_errorReturn_t convert_uint32_to_string(uint32 value, uint8 *str);

#endif /* LCD_H_ */