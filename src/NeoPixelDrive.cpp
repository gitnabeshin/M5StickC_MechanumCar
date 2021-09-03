#include <Adafruit_NeoPixel.h>
#include "NeoPixelDrive.h"

//neopixel
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

uint32_t color = pixels.Color(0, 250, 0);
uint32_t colorOFF = pixels.Color(0, 0, 0);
uint16_t neopixelLoopCount = 0;
uint16_t countInMode = 0;    //Counter in Mode
uint8_t countSkipRate = 0;  //SkipRate in Mode
uint8_t count = 0;
uint8_t mode = NEOPIXEL_STOP;

void neopixel_setup(void){
    //neopixel
    pixels.begin();
    pixels.setBrightness(30);
    pixels.clear();
}

void neopixel_setMode(uint8_t newMode){
    if(mode != newMode){
        mode = newMode;
        pixels.clear();
        countInMode = 0;
        countSkipRate = 0;
    }
}

void neopixel_handle_stop(void){

    if(countSkipRate != 6){
        countSkipRate++;
        return;
    } else {
        countSkipRate = 0;
    }

    //colors
    color = pixels.Color(0, 255, 0);
    colorOFF = pixels.Color(0, 30, 0);
    if(countInMode % 2 == 0){
        for(count = 0; count < NUMPIXELS; count++){
            pixels.setPixelColor(count, color);
        }
    } else {
        for(count = 0; count < NUMPIXELS; count++){
            pixels.setPixelColor(count, colorOFF);
        }
    }
}

void neopixel_handle_forward(void){

    if(countSkipRate != 6){
        countSkipRate++;
        return;
    } else {
        countSkipRate = 0;
    }

    //colors
    color = pixels.Color(255, 0, 0);
    colorOFF = pixels.Color(20, 0, 30);
    if(countInMode % 2 == 0){
        for(count = 0; count < NUMPIXELS; count++){
            pixels.setPixelColor(count, color);
        }
    } else {
        for(count = 0; count < NUMPIXELS; count=count+2){
            pixels.setPixelColor(count, colorOFF);
        }
    }
}

void neopixel_handle_backward(void){

    if(countSkipRate != 6){
        countSkipRate++;
        return;
    } else {
        countSkipRate = 0;
    }

    color = pixels.Color(0, 0, 255);
    colorOFF = pixels.Color(30, 0, 20);
    if(countInMode % 2 == 0){
        for(count = 0; count < NUMPIXELS; count++){
            pixels.setPixelColor(count, color);
        }
    } else {
        for(count = 0; count < NUMPIXELS; count=count+2){
            pixels.setPixelColor(count, colorOFF);
        }
    }
}

void neopixel_handle_left(void){
    //colors
    color = pixels.Color(0, 255, 255);
    colorOFF = pixels.Color(0, 30, 30);

    if(countInMode > NUMPIXELS / 2 + 2 ){
        countInMode = 0;
    } else if(countInMode > NUMPIXELS / 2 ){
        //front
        pixels.setPixelColor(countInMode - 2, colorOFF);
        //rear
        pixels.setPixelColor(NUMPIXELS - countInMode + 2, colorOFF);
    } else {
        //front
        pixels.setPixelColor(countInMode, color);
        pixels.setPixelColor(countInMode - 1, color);
        pixels.setPixelColor(countInMode - 2, colorOFF);
        //rear
        pixels.setPixelColor(NUMPIXELS - countInMode, color);
        pixels.setPixelColor(NUMPIXELS - countInMode + 1, color);
        pixels.setPixelColor(NUMPIXELS - countInMode + 2, colorOFF);
    }
}

void neopixel_handle_right(void){
    //colors
    color = pixels.Color(0, 255, 255);
    colorOFF = pixels.Color(0, 30, 30);

    if(countInMode > NUMPIXELS / 2 + 2 ){
        countInMode = 0;
    } else if(countInMode > NUMPIXELS / 2){
        //front
        pixels.setPixelColor(9 - countInMode + 2, colorOFF);
        //rear
        pixels.setPixelColor(countInMode + 10 - 2, colorOFF);
    } else {
        //front
        pixels.setPixelColor(9 - countInMode, color);
        pixels.setPixelColor(9 - countInMode + 1, color);
        pixels.setPixelColor(9 - countInMode + 2, colorOFF);
        //rear
        pixels.setPixelColor(countInMode + 10, color);
        pixels.setPixelColor(countInMode + 10 - 1, color);
        pixels.setPixelColor(countInMode + 10 - 2, colorOFF);
    }
}

void neopixel_handle_right_rotate(void){
    //colors
    color = pixels.Color(100, 255, 0);
    colorOFF = pixels.Color(255, 0, 100);

    if(countInMode % 2 == 0){
        for(count = 0; count < NUMPIXELS; count=count+2){
            pixels.setPixelColor(count, color);
            pixels.setPixelColor(count + 1, colorOFF);
        }
    } else {
        for(count = 0; count < NUMPIXELS; count=count+2){
            pixels.setPixelColor(count, colorOFF);
            pixels.setPixelColor(count + 1, color);
        }
    }
}

void neopixel_handle_left_rotate(void){
    //colors
    color = pixels.Color(0, 100, 255);
    colorOFF = pixels.Color(100, 255, 0);

    if(countInMode % 2 == 0){
        for(count = 0; count < NUMPIXELS; count=count+2){
            pixels.setPixelColor(count, color);
            pixels.setPixelColor(count + 1, colorOFF);
        }
    } else {
        for(count = 0; count < NUMPIXELS; count=count+2){
            pixels.setPixelColor(count, colorOFF);
            pixels.setPixelColor(count + 1, color);
        }
    }
}

void neopixel_loop(void){
    if(neopixelLoopCount == 8000){
        switch (mode){
            case NEOPIXEL_STOP:
                neopixel_handle_stop();
                break;
            case NEOPIXEL_FORWARD:
                neopixel_handle_forward();
                break;
            case NEOPIXEL_LEFT:
                neopixel_handle_left();
                break;
            case NEOPIXEL_RIGHT:
                neopixel_handle_right();
                break;
            case NEOPIXEL_BACKWARD:
                neopixel_handle_backward();
                break;
            case NEOPIXEL_RIGHT_ROTATE:
                neopixel_handle_right_rotate();
                break;
            case NEOPIXEL_LEFT_ROTATE:
                neopixel_handle_left_rotate();
                break;
            default:
                break;
        }
        pixels.show();
        countInMode++;
        neopixelLoopCount = 0;
    }
    neopixelLoopCount++;
}

