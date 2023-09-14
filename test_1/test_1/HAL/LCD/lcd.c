/*
 * lcd.c
 *
 * Created: 9/13/2023 1:44:40 AM
 *  Author: ENG HOSAM
 */ 

#include "lcd.h"

static EN_errorReturn_t lcd_send_4bits(const ST_chr_lcd_4bit_t *lcd, uint8 _data_command);
static EN_errorReturn_t lcd_4bit_send_enable_signal(const ST_chr_lcd_4bit_t *lcd);
static EN_errorReturn_t lcd_4bit_set_cursor(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn);


EN_errorReturn_t lcd_4bit_initialize(const ST_chr_lcd_4bit_t *lcd){
	EN_errorReturn_t ret = E_OK;
    uint8 l_data_pins_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret =  DIO_pin_initialize(&(lcd->lcd_rs));
        ret =  DIO_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter = 0; l_data_pins_counter < 4; l_data_pins_counter++){
            ret =  DIO_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        
        _delay_ms(20);
		
        ret = lcd_4bit_send_command(lcd, 0x33); // Initialize the LCD for 4-bit mode
        ret = lcd_4bit_send_command(lcd, 0x32); // Initialize the LCD for 4-bit mode
		ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
		ret = lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
		ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
		_delay_ms(2);
		ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);

         
    }
    return ret;
}

EN_errorReturn_t lcd_4bit_send_command(const ST_chr_lcd_4bit_t *lcd, uint8 command){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == lcd){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
		ret = lcd_send_4bits(lcd, (command >> 4));
		ret = lcd_4bit_send_enable_signal(lcd);
		ret = lcd_send_4bits(lcd, command);
		ret = lcd_4bit_send_enable_signal(lcd);
	}
	return ret;
}

EN_errorReturn_t lcd_4bit_send_char_data(const ST_chr_lcd_4bit_t *lcd, uint8 data){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == lcd){
		ret = E_NOT_OK;
	}
	else{
		ret = DIO_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
		ret = lcd_send_4bits(lcd, (data >> 4));
		ret = lcd_4bit_send_enable_signal(lcd);
		ret = lcd_send_4bits(lcd, data);
		ret = lcd_4bit_send_enable_signal(lcd);
	}
	return ret;
}

EN_errorReturn_t lcd_4bit_send_char_data_pos(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 data){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == lcd){
		ret = E_NOT_OK;
	}
	else{
		ret = lcd_4bit_set_cursor(lcd, row, col);
		ret = lcd_4bit_send_char_data(lcd, data);
	}
	return ret;
}

EN_errorReturn_t lcd_4bit_send_string(const ST_chr_lcd_4bit_t *lcd, uint8 *str){
	EN_errorReturn_t ret = E_OK;
	if(NULL == lcd){
		ret = E_NOT_OK;
	}
	else{
		while(*str){
			ret = lcd_4bit_send_char_data(lcd, *str++);
		}
	}
	return ret;
}

EN_errorReturn_t lcd_4bit_send_string_pos(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 *str){
	EN_errorReturn_t ret = E_OK;
	
	if(NULL == lcd){
		ret = E_NOT_OK;
	}
	else{
		ret = lcd_4bit_set_cursor(lcd, row, col);
		while(*str){
			ret = lcd_4bit_send_char_data(lcd, *str++);
		}
	}
	return ret;
}

EN_errorReturn_t lcd_4bit_send_custome_char(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 col,
const uint8 _chr[], uint8 mem_pos) {
	EN_errorReturn_t ret = E_OK;
	uint8 l_lcd_counter = 0;
	if(NULL == lcd){
		ret = E_NOT_OK;
	}
	else{
		ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
		for(l_lcd_counter = 0; l_lcd_counter < 8; ++l_lcd_counter){
			ret = lcd_4bit_send_char_data(lcd, _chr[l_lcd_counter]);
		}
		ret = lcd_4bit_send_char_data_pos(lcd, row, col, mem_pos);
	}
	return ret;
}



EN_errorReturn_t convert_uint8_to_string(uint8 value, uint8 *str){
	EN_errorReturn_t ret = E_OK;
	if(NULL == str){
		ret = E_NOT_OK;
	}
	else{
		memset((char *)str, '\0', 4);
		sprintf(str, "%i", value);
	}
	return ret;
}

EN_errorReturn_t convert_uint16_to_string(uint16 value, uint8 *str){
	EN_errorReturn_t ret = E_OK;
	uint8 Temp_String[6] = {0};
	uint8 DataCounter = 0;
	if(NULL == str){
		ret = E_NOT_OK;
	}
	else{
		memset(str, ' ', 5);
		str[5] = '\0';
		sprintf((char *)Temp_String, "%i", value);
		while(Temp_String[DataCounter] != '\0'){
			str[DataCounter] = Temp_String[DataCounter];
			DataCounter++;
		}
	}
	return ret;
}

EN_errorReturn_t convert_uint32_to_string(uint32 value, uint8 *str){
	EN_errorReturn_t ret = E_OK;
	if(NULL == str){
		ret = E_NOT_OK;
	}
	else{
		memset((char *)str, '\0', 11);
		sprintf(str, "%i", value);
	}
	return ret;
}

static EN_errorReturn_t lcd_send_4bits(const ST_chr_lcd_4bit_t *lcd, uint8 _data_command){
	EN_errorReturn_t ret = E_OK;
	ret = DIO_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
	ret = DIO_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
	ret = DIO_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
	ret = DIO_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
	return ret;
}

static EN_errorReturn_t lcd_4bit_send_enable_signal(const ST_chr_lcd_4bit_t *lcd){
	EN_errorReturn_t ret = E_OK;
	ret = DIO_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
	_delay_us(5);
	ret = DIO_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
	return ret;
}

static EN_errorReturn_t lcd_4bit_set_cursor(const ST_chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn){
	EN_errorReturn_t ret = E_OK;
	coulmn--;
	switch(row){
		case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + coulmn)); break;
		case ROW2 : ret = lcd_4bit_send_command(lcd, (0xc0 + coulmn)); break;
		case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94 + coulmn)); break;
		case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4 + coulmn)); break;
		default : ;
	}
	return ret;
}