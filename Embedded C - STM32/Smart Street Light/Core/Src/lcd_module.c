#include "lcd_module.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"

#define I2C_ADDRESS_LCD 0x27 << 1

extern I2C_HandleTypeDef hi2c1;
extern volatile uint8_t relay1_state;
extern volatile uint8_t relay2_state;
extern volatile uint8_t relay3_state;
extern volatile uint8_t relay4_state;

void lcd_send_cmd(char cmd) {
    // Implementation for sending commands to the LCD
	char data_u, data_l;
	    uint8_t data_t[4];
	    data_u = (cmd & 0xf0);
	    data_l = ((cmd << 4) & 0xf0);
	    data_t[0] = data_u | 0x0C;  // en=1, rs=0
	    data_t[1] = data_u | 0x08;  // en=0, rs=0
	    data_t[2] = data_l | 0x0C;  // en=1, rs=0
	    data_t[3] = data_l | 0x08;  // en=0, rs=0
	    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void lcd_send_data(char data) {
    // Implementation for sending data to the LCD
	char data_u, data_l;
	    uint8_t data_t[4];
	    data_u = (data & 0xf0);
	    data_l = ((data << 4) & 0xf0);
	    data_t[0] = data_u | 0x0D;  // en=1, rs=1
	    data_t[1] = data_u | 0x09;  // en=0, rs=1
	    data_t[2] = data_l | 0x0D;  // en=1, rs=1
	    data_t[3] = data_l | 0x09;  // en=0, rs=1
	    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDRESS_LCD, (uint8_t *)data_t, 4, 100);
}

void lcd_init(void) {
    lcd_send_cmd(0x02);  // initialize LCD in 4-bit mode
    lcd_send_cmd(0x28);  // 2 line, 5*7 matrix
    lcd_send_cmd(0x0c);  // display on, cursor off
    lcd_send_cmd(0x80);  // force cursor to beginning (1st line)
}

void lcd_send_string(char *str) {
    while (*str) lcd_send_data(*str++);
}

void UpdateLCD(void) {
    char buffer[32];

    // Set cursor to the first line and print SL1 and SL2 states
    lcd_send_cmd(0x80);  // move cursor to the first line
    snprintf(buffer, sizeof(buffer), "SL1:%s  SL2:%s",
             relay1_state ? " on" : "off",
             relay2_state ? " on" : "off");
    lcd_send_string(buffer);

    // Set cursor to the second line and print SL3 and SL4 states
    lcd_send_cmd(0xC0);  // move cursor to the second line
    snprintf(buffer, sizeof(buffer), "SL3:%s  SL4:%s",
             relay3_state ? " on" : "off",
             relay4_state ? " on" : "off");
    lcd_send_string(buffer);
}
