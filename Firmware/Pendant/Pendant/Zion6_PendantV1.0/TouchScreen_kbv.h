// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#ifndef _TOUCHSCREEN_KBV_H_
#define _TOUCHSCREEN_KBV_H_
#include <stdint.h>

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin
#define MINPRESSURE 100
#define MAXPRESSURE 1000

//#define TS_MINX 881
//#define TS_MAXX 92
//#define TS_MINY 205
#define TS_MINX 873
#define TS_MAXX 97
#define TS_MINY 214
#define TS_MAXY 880
//uint16_t TS2_MINX = TS_MINX;
//uint16_t TS2_MAXX = TS_MAXX;
//uint16_t TS2_MINY = TS_MINY;
//uint16_t TS2_MAXY = TS_MAXX;

#define TouchScreen TouchScreen_kbv
#define TSPoint TSPoint_kbv

class TSPoint_kbv {
    public:
        TSPoint_kbv(void);
        TSPoint_kbv(int16_t x, int16_t y, int16_t z);

        bool operator==(TSPoint_kbv);
        bool operator!=(TSPoint_kbv);

        int16_t x, y, z;
};

class TouchScreen_kbv {
    public:
        TouchScreen_kbv(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
        TouchScreen_kbv(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);

//        bool isTouching(void);
        uint16_t pressure(void);
        int readTouchY();
        int readTouchX();
        TSPoint_kbv getPoint();
        int16_t pressureThreshhold;

    private:
        uint8_t _yp, _ym, _xm, _xp;
        uint16_t _rxplate;
};

#endif
