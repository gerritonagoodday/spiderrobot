// ep29.h.h
// ep29 header file
// rev 1 - December 2017- Shabaz

#ifndef _EP29_H_
#define _EP29_H_

// Definitions
#define EP_WIDTH 128
#define EP_HEIGHT 296
// EP_WIDTH8 is width/8
#define EP_WIDTH8 16
// EP_FRAMEMEMSIZE is (width/8) * height;
#define EP_FRAMEMEMSIZE 4736
#define ALL_WHITE 0xff
#define ALL_BLACK 0x00
#define COL_WHITE 1
#define COL_BLACK 0
#define PEN_THIN 0
#define PEN_MED 1
#define PEN_THICK 2

// Functions
void ep_spi_init(void);
void ep_sleep(void);
void ep_init(unsigned char* lut);

void ep_setbg(unsigned char* frame, unsigned char col8);
void ep_line(unsigned char* frame, int x, int y, int x2, int y2, unsigned char col, char weight=PEN_THIN);
int ep_write_text(unsigned char* frame, char* text, int x, int y, unsigned char col,
                double xscale, double yscale, unsigned int* dy, char weight=PEN_THIN);

void ep_clearframe(unsigned char col8);
void ep_setframe(unsigned char* frame, int x, int y, int width, int height);
void ep_displayframe(void);


#endif // _EP29_H_