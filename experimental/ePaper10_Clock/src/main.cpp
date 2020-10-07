#include "main.h"
#include "ep29.h"

// Wiring connections
// Blue - MOSI - PTD2
// Yellow - SCK - PTD1
// Orange - CS - PTD7
// Green - DC Data/Command - PTD6
// White - RST - PTA17
// Purple - BUSY - PTA16
// Black - GND
// Red - 3.3V

//definitions
#define LED_ON 0
#define LED_OFF 1
#define FOREVER 1
#define MODE_TIMEDISPLAY 1
#define MODE_TIMESET 2
#define BTN_SET_PRESSED btn_set.read()==0
#define BTN_SET_RELEASED btn_set.read()==1
#define BTN_DOWN_PRESSED btn_down.read()==0
#define BTN_DOWN_RELEASED btn_down.read()==1
#define BTN_UP_PRESSED btn_up.read()==0
#define BTN_UP_RELEASED btn_up.read()==1
#define SET_NULL 0
#define SET_HOUR 1
#define SET_MIN 2
#define SET_YEAR 3
#define SET_MONTH 4
#define SET_DATE 5

// Constants

// look-up tables, provided by Waveshare
const unsigned char full_mode[] = {
      0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 0x66, 0x69, 
      0x69, 0x59, 0x58, 0x99, 0x99, 0x88, 0x00, 0x00, 0x00, 0x00,
      0xf8, 0xb4, 0x13, 0x51, 0x35, 0x51, 0x51, 0x19, 0x01, 0x00 };
const unsigned char partial_mode[] = {
      0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x13, 0x14, 0x44, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


// Global Variables
DigitalOut myled(LED_RED); // in-built LED
time_t unixtime;
TickType_t sec_ticker;
TickType_t debounce_ticker;
char screen_update_ctr;
char do_screen_update;
DigitalIn btn_set(PTC17);
DigitalIn btn_down(PTC16);
DigitalIn btn_up(PTC13);
char button_inhibit;
unsigned char fbuf[EP_FRAMEMEMSIZE];
char led_state=0;

void sec_handler(void)
{
  unixtime++;
  screen_update_ctr++;
  if (screen_update_ctr>=60)
  {
    do_screen_update=1;
    screen_update_ctr=0;
  }
  led_state=led_state^1;
  myled=led_state;
}

void debounce_handler(void)
{
  button_inhibit=0;
  debounce_ticker.detach();
}

void app_main() {
  char timebuf[6]; // used to store HH:MM time, e.g. 19:20
  char calbuf[32]; // used to store the date, e.g. Fri 29 Dec 2017
  char textbuf[10];
  unsigned int dx, dy;
  char mode=MODE_TIMEDISPLAY;
  char setting=SET_NULL;
  struct tm tset;
  int val;
  int toadd;
  
  btn_set.mode(PullUp);
  btn_down.mode(PullUp);
  btn_up.mode(PullUp);
  
  button_inhibit=0;
  screen_update_ctr=0;
  do_screen_update=1;
  myled = LED_OFF;  

  ep_spi_init();
  ep_init((unsigned char*)full_mode);
  
  ep_setbg(fbuf, ALL_WHITE); 
  // any buttons pressed on startup?
  if (BTN_DOWN_PRESSED)
  {
      ep_setframe(fbuf, 0,0, EP_WIDTH, EP_HEIGHT);
      ep_displayframe();
      ep_setframe(fbuf, 0,0, EP_WIDTH, EP_HEIGHT);
      ep_displayframe();
      while(FOREVER)
      {
          vTaskDelay(20);
          myled=LED_ON;
          vTaskDelay(20);
          myled=LED_OFF;
      }
  }
  if (BTN_UP_PRESSED)
  {
      ep_write_text(fbuf, "E-Paper Clock", 10,50, COL_BLACK, 2.0, 1.0, NULL, PEN_MED);
      ep_setframe(fbuf, 0,0, EP_WIDTH, EP_HEIGHT);
      ep_displayframe();
      while(FOREVER)
      {
          vTaskDelay(20);
          myled=LED_ON;
          vTaskDelay(20);
          myled=LED_OFF;
      }
  }
  
  unixtime=1514583436;  // Set RTC time to some initial value
  sec_ticker.attach(sec_handler, 1.0);
  
  while(FOREVER)
  {
      toadd=0;
      if ((BTN_UP_PRESSED) && (button_inhibit==0))
          toadd=1;
      if ((BTN_DOWN_PRESSED) && (button_inhibit==0))
          toadd=-1;
      if (toadd!=0)
      {
          sec_ticker.detach();
          screen_update_ctr=59;
          sec_ticker.attach(sec_handler, 1.0);
          button_inhibit=1;
          debounce_ticker.attach(debounce_handler, 0.3);
          if (mode==MODE_TIMESET)
          {
              switch(setting)
              {
                  case SET_HOUR:
                      if ((toadd>0) && (tset.tm_hour<23))
                          tset.tm_hour+=1;
                      else if ((toadd<0) && (tset.tm_hour>0))
                          tset.tm_hour-=1;
                      break;
                  case SET_MIN:
                      if ((toadd>0) && (tset.tm_min<59))
                          tset.tm_min+=1;
                      else if ((toadd<0) && (tset.tm_min>0))
                          tset.tm_min-=1;
                      break;
                  case SET_YEAR:
                      if ((toadd>0) && (tset.tm_year<199)) // allow up to 2099
                          tset.tm_year+=1;
                      else if ((toadd<0) && (tset.tm_year>0)) // allow down to 1900
                          tset.tm_year-=1;
                      break;
                  case SET_MONTH:
                      if ((toadd>0) && (tset.tm_mon<11))
                          tset.tm_mon+=1;
                      else if ((toadd<0) && (tset.tm_mon>0))
                          tset.tm_mon-=1;
                      break;
                  case SET_DATE:
                      if ((toadd>0) && (tset.tm_mday<31))
                          tset.tm_mday+=1;
                      else if ((toadd<0) && (tset.tm_mday>1))
                          tset.tm_mday-=1;
                      break;
                  default:
                      break;
              }
          }   
      }
      
      if ((BTN_SET_PRESSED) && (button_inhibit==0))
      {
          if (mode==MODE_TIMEDISPLAY)
          {
              mode=MODE_TIMESET;
              strftime(timebuf, 6, "%H", localtime(&unixtime));
              sscanf(timebuf, "%d", &val);
              tset.tm_hour=val;
              strftime(timebuf, 6, "%M", localtime(&unixtime));
              sscanf(timebuf, "%d", &val);
              tset.tm_min=val;
              strftime(timebuf, 6, "%Y", localtime(&unixtime));
              sscanf(timebuf, "%d", &val);
              tset.tm_year=val-1900;
              strftime(timebuf, 6, "%m", localtime(&unixtime));
              sscanf(timebuf, "%d", &val);
              tset.tm_mon=val-1;
              strftime(timebuf, 6, "%d", localtime(&unixtime));
              sscanf(timebuf, "%d", &val);
              tset.tm_mday=val;
              tset.tm_sec=screen_update_ctr;
              
              setting=SET_HOUR;
              screen_update_ctr=0;
              do_screen_update=1;
              button_inhibit=1;
              debounce_ticker.attach(debounce_handler, 1.0);
          }
          else if (mode==MODE_TIMESET)
          {
              switch(setting)
              {
                  case SET_HOUR:
                      setting=SET_MIN;
                      break;
                  case SET_MIN:
                      setting=SET_YEAR;
                      break;
                  case SET_YEAR:
                      setting=SET_MONTH;
                      break;
                  case SET_MONTH:
                      setting=SET_DATE;
                      break;
                  case SET_DATE:
                      setting=SET_NULL;
                      unixtime = mktime(&tset);
                      mode=MODE_TIMEDISPLAY;
                      break;
                  default:
                      break;
              }
              screen_update_ctr=0;
              do_screen_update=1;
              button_inhibit=1;
              debounce_ticker.attach(debounce_handler, 1.0);
          }
      }
      if (do_screen_update)
      {
          do_screen_update=0;
          ep_setbg(fbuf, ALL_WHITE);
          switch(mode)
          {
              case MODE_TIMEDISPLAY:
                  //unixtime=time(NULL);
                  strftime(timebuf, 6, "%H:%M", localtime(&unixtime));
                  strftime(calbuf, 32, "%a %e %b %Y", localtime(&unixtime));
                  ep_write_text(fbuf, calbuf, 0,103, COL_BLACK, 1.0, 1.0, NULL, PEN_MED);
                  dx=ep_write_text(fbuf, timebuf, 0,5, COL_BLACK, 3.0, 4.0, NULL, PEN_THICK);
                  break;
              case MODE_TIMESET:
                  switch(setting)
                  {
                      case SET_HOUR:
                          ep_write_text(fbuf, "Set Hour:", 0,103, COL_BLACK, 1.0, 1.0, NULL, PEN_MED);
                          sprintf(textbuf, "%02d", tset.tm_hour);
                          ep_write_text(fbuf, textbuf, 0,5, COL_BLACK, 3.0, 4.0, NULL, PEN_THICK);
                          break;
                      case SET_MIN:
                          ep_write_text(fbuf, "Set Min:", 0,103, COL_BLACK, 1.0, 1.0, NULL, PEN_MED);
                          sprintf(textbuf, "%02d", tset.tm_min);
                          ep_write_text(fbuf, textbuf, 0,5, COL_BLACK, 3.0, 4.0, NULL, PEN_THICK);
                          break;
                      case SET_YEAR:
                          ep_write_text(fbuf, "Set Year:", 0,103, COL_BLACK, 1.0, 1.0, NULL, PEN_MED);
                          sprintf(textbuf, "%d", 1900+tset.tm_year);
                          ep_write_text(fbuf, textbuf, 0,5, COL_BLACK, 3.0, 4.0, NULL, PEN_THICK);
                          break;
                      case SET_MONTH:
                          ep_write_text(fbuf, "Set Month:", 0,103, COL_BLACK, 1.0, 1.0, NULL, PEN_MED);
                          sprintf(textbuf, "%d", 1+tset.tm_mon);
                          ep_write_text(fbuf, textbuf, 0,5, COL_BLACK, 3.0, 4.0, NULL, PEN_THICK);
                          break;
                      case SET_DATE:
                          ep_write_text(fbuf, "Set Date:", 0,103, COL_BLACK, 1.0, 1.0, NULL, PEN_MED);
                          sprintf(textbuf, "%d", tset.tm_mday);
                          ep_write_text(fbuf, textbuf, 0,5, COL_BLACK, 3.0, 4.0, NULL, PEN_THICK);
                          break;
                      default:
                          break;
                  }
                  break;
              default:
                  break;
          }
          ep_setframe(fbuf, 0,0, EP_WIDTH, EP_HEIGHT);
          ep_displayframe();
      }
      vTaskDelay(1); // small sleep
  } // end while(FOREVER)
  
}