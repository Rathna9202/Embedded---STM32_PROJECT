#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include "main.h"

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void UpdateLCD(void);

#endif // LCD_MODULE_H
