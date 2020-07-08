#ifndef _GSM_H
#define _GSM_H

extern TaskHandle_t gsmLoopTask;

// Exported Functions
//void rgb_set_color(uint16_t hue);
//void blink_LED(uint16_t set_color, uint16_t set_blinkduration);
void gsmLoop(void *parameter);
//void switch_LED(uint8_t state);
//void switch_LED1(uint8_t state);
int gsm_init(void);

#endif