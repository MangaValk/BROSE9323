#ifndef BROSE9323_H
#define BROSE9323_H

#include <Adafruit_GFX.h>

//#define FLIPDOT_PLCC_ADAPTER

const uint8_t _hannio_splash[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x70,
  0x3e, 0x00, 0x39, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x70, 0xff, 0x00, 0x39, 0xff, 0xff, 0xff, 0xff,
  0xfe, 0x71, 0xf7, 0xc0, 0x39, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x73, 0xc1, 0xc0, 0x38, 0x1f, 0x87,
  0xf0, 0x7f, 0x06, 0x73, 0x80, 0xe0, 0x38, 0x0f, 0x01, 0xc0, 0x3c, 0x02, 0x77, 0x7f, 0x60, 0x38,
  0xc7, 0x78, 0xc6, 0x1c, 0x60, 0x77, 0x7f, 0x70, 0x39, 0xe3, 0xfc, 0xcf, 0x9c, 0xf8, 0x76, 0x00,
  0x30, 0x39, 0xf3, 0xfc, 0xcf, 0x9c, 0xf8, 0x77, 0x7f, 0x70, 0x39, 0xf3, 0x80, 0xcf, 0x9c, 0xf8,
  0x77, 0x7f, 0x60, 0x39, 0xf3, 0x00, 0xcf, 0x9c, 0xf8, 0x73, 0x80, 0xe0, 0x39, 0xf2, 0x3c, 0xcf,
  0x9c, 0xf8, 0x73, 0xc1, 0xc0, 0x39, 0xf2, 0x7c, 0xcf, 0x9c, 0xf8, 0x71, 0xf7, 0xc0, 0x39, 0xf2,
  0x3c, 0xcf, 0x9c, 0xf8, 0x70, 0xff, 0x80, 0x39, 0xf3, 0x00, 0xcf, 0x9c, 0xf8, 0x70, 0x3e, 0x00
};

class BROSE9323 : public Adafruit_GFX {
  private:
    uint16_t _flip_time;
    const uint8_t _panel_width;
    const uint8_t _buffer_width;
    const uint16_t _buffer_size;
    uint8_t* _old_buffer = NULL;
    uint8_t* _new_buffer = NULL;
    bool _direct_mode = false;

#ifdef ESP8266
    Stream* stream;
#else
    uint8_t _active_panel = 255;
    uint8_t _active_col = 255;
    uint8_t _active_row = 255;
    bool _active_data;

#ifndef FLIPDOT_PLCC_ADAPTER
    const uint8_t ENABLE    =  7,
                  ADDR_0    =  3,
                  ADDR_1    =  5,
                  ADDR_2    =  6,
                  COL_DATA  =  4,
                  COL_0     =  8,
                  COL_1     = 10,
                  COL_2     =  9,
                  COL_3     = 11,
                  COL_4     = 12,
                  ROW_0     = A3,
                  ROW_1     = A4,
//                  ROW_2     = A2,
                  ROW_2     = A6,
                  ROW_3     = A0,
//                  ROW_4     = A1,
                  ROW_4     = A7,
                  ROW_RESET = 13,
                  ROW_SET   = A5;
#else
    const uint8_t RELAY     =  2,
                  ENABLE    =  3,
                  ADDR_0    =  7,
                  ADDR_1    =  6,
                  ADDR_2    =  5,
                  COL_DATA  =  4,
                  COL_0     = 12,
                  COL_1     = 11,
                  COL_2     = 10,
                  COL_3     =  9,
                  COL_4     =  8,
                  ROW_0     = 13, //1 A1 CHECK
                  ROW_1     = A0, //2 A2
                  ROW_2     = A1, //4 A3
                  ROW_3     = A2, //8 13 CHECK
                  ROW_4     = A3, //F A0
                  ROW_RESET = A4,
                  ROW_SET   = A5;
#endif

    void _selectColumn(uint8_t);
    void _selectPanel(uint8_t);
    void _selectRow(uint8_t);
    void _setData(bool);
    void _strobe(void);
#endif
  public:
    BROSE9323(uint8_t, uint8_t, uint8_t, uint16_t ft = 280);
#ifdef ESP8266
    void begin(Stream* = &Serial);
#endif
    void begin(void);
    void display(bool force = false);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void fillScreen(uint16_t);
    void setDirect(bool);
    void setTiming(uint16_t);
#ifndef ESP8266
    void printBuffer(void);
#endif
};
#endif //BROSE9323_H
