#ifndef __NEOPIXEL_DRIVE_H__
#define __NEOPIXEL_DRIVE_H__

#define PIN_NEOPIXEL 11
#define NUMPIXELS 20

//mode
#define NEOPIXEL_STOP           0x00
#define NEOPIXEL_FORWARD        0x01
#define NEOPIXEL_LEFT           0x02
#define NEOPIXEL_RIGHT          0x03
#define NEOPIXEL_BACKWARD       0x04
#define NEOPIXEL_RIGHT_ROTATE   0x05
#define NEOPIXEL_LEFT_ROTATE    0x06
#define NEOPIXEL_MAX            0x07

void neopixel_setup(void);
void neopixel_setMode(uint8_t mode);
void neopixel_loop(void);

#endif /* __NEOPIXEL_DRIVE_H__ */
