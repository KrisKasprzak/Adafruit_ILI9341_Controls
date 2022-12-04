/*

  MCU                       https://www.amazon.com/Teensy-3-2-with-pins/dp/B015QUPO5Y/ref=sr_1_2?s=industrial&ie=UTF8&qid=1510373806&sr=1-2&keywords=teensy+3.2
  Display                   https://www.amazon.com/Wrisky-240x320-Serial-Module-ILI9341/dp/B01KX26JJU/ref=sr_1_10?ie=UTF8&qid=1510373771&sr=8-10&keywords=240+x+320+tft


    available methods

    // required
  SliderH(ILI9341_t3 *Display);   // class constructor
  void init(uint16_t SliderX, uint16_t SliderY, uint16_t SliderW, float ScaleLow, float ScaleHi, float Scale, float Snap, uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);    // initializer
  void draw(float val);         // method to draw complete slider
  float slide(float ScreenX, float ScreenY);       // method to move handle as user drags finger over handle,
  // automatically looks for a valid range press returns if control was clicked. use value property to get the selected option


  // optional
  bool changed();
  void setColors(uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);   // way to reset colors (useful for drawing enabled or disabled)
  void setHandleColor(uint16_t HandleColor);  // method to just draw the handle (useful for showing handle in green for OK value
  void setDisableColor(uint16_t HandleColor, uint16_t SliderColor); // method to just draw the handle (useful for showing handle in green for OK value
  void setHandleSize(int size);
  void disable();
  void enable();
  void show();
  void hide();
  void setHandleShape(byte shape);
  void drawSliderColor(bool color);
  void setPressDebounce(byte Debounce);
  float value;

*/


/*

  Implementatin is 5 steps

*/
#include <Adafruit_ILI9341.h>           
#include <Adafruit_ILI9341_Controls.h>
#include <Fonts\FreeSans24pt7b.h>          
#include <Fonts\FreeSans18pt7b.h>
#include <Fonts\FreeSans12pt7b.h>
#include <XPT2046_Touchscreen.h>

// you must create and pass fonts to the function
#define FONT FreeSans24pt7b
#define FONT_TEXT FreeSans12pt7b
// For the Adafruit shield, these are the default.
#define T_CS   12
#define T_IRQ  27
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED   26

// defines for locations
#define ROW0 30
#define ROW1 70
#define ROW2 110
#define ROW3 150
#define ROW4 190

byte RedByte = 70, GreenByte = 170, BlueByte = 210, BrightByte = 255;
int BtnX, BtnY;

char buf[22];
uint16_t color, oldcolor;

Adafruit_ILI9341 Display(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);
TS_Point TP;

// step 2 create the objects
//SliderH Red(&Display, left, top, width, bar color, back color, ball color);

SliderH Red(&Display);
SliderH Green(&Display);
SliderH Blue(&Display);


void setup() {

  Serial.begin(9600);

  //you know the drill
  pinMode(PIN_LED, OUTPUT);


  // step 3 initialize each slider
  Red.init    (20, ROW2, 100, 0, 255, 127.5, 0, C_WHITE, C_BLACK, C_RED);
  Green.init  (20, ROW3, 100, 0, 255, 63.75, 0, C_WHITE, C_BLACK, C_GREEN);
  Blue.init   (20, ROW4, 100, 0, 255,     0, 0, C_WHITE, C_BLACK, C_BLUE);

  // fire up the display
  Display.begin();

  // fire up the touch display
  Touch.begin();

  Display.fillScreen(C_BLACK);

  // turn on the display
  digitalWrite(PIN_LED, 255);

  // set some display settings
  Display.setRotation(3);
  Display.setTextColor(C_WHITE, C_BLACK);
  Display.setFont(&FONT);
  Display.setCursor(10 , 40 );
  Display.print(F("Colors"));

  // Step 4 draw each slider
  Red.draw(RedByte);
  Green.draw(GreenByte);
  Blue.draw(BlueByte);

  color = Display.color565(RedByte, GreenByte, BlueByte);

  // draw a color box
  Display.drawRect(140, 80, 100, 100, C_WHITE);
  Display.drawRect(141, 81, 98, 98, C_WHITE);
  Display.fillRect(142, 82, 96, 96, color);
  Display.setFont(&FONT_TEXT);
  sprintf(buf, "(0x%x),%3d,%3d,%3d", color, RedByte, GreenByte, BlueByte);
  Display.setCursor(50 , 230 );
  Display.print(buf);

}


void loop() {

  // wait for touch
  if (Touch.touched()) {
    ProcessTouch();

    // how to enable disable a slider
    // example on how to change slider colors

    // Step 5 allow user to slide the control and proces results
    // if you really need to monitor if the control was clicked
    // here's how, this may be needed if you have a complicated UI
    // and don't need to automatically change things--code here shows 2 cases
    // 1) automatically updates items based on slider (see if else sections, these
    // run even if slider was not pressed
    // and 2) only updating items if the slider was changed
    // do not use the return value as slider value
    // only use SliderV.value for the value

    Red.slide(BtnX, BtnY);
    Green.slide(BtnX, BtnY);
    Blue.slide(BtnX, BtnY);

    // update the color swatch
    // as mentioned above, you you don't want to process code unless slider was moved
    // wrap a change test around checkbox values

    RedByte = Red.value;
    GreenByte = Green.value;
    BlueByte = Blue.value;
    color = Display.color565(RedByte, GreenByte, BlueByte);
    Display.drawRect(140, 80, 100, 100, C_WHITE);
    Display.drawRect(141, 81, 98, 98, C_WHITE);
    Display.fillRect(142, 82, 96, 96, color);
    Display.fillRect(40, 210, 270, 50, C_BLACK);
    Display.setFont(&FONT_TEXT);
    sprintf(buf, "(0x%x),%3d,%3d,%3d", color, RedByte, GreenByte, BlueByte);
    Display.setCursor(50 , 230 );
    Display.print(buf);


  }

}

void ProcessTouch() {

  // depending on the touch library you may need to change methods here
  TP = Touch.getPoint();

  BtnX = TP.x;
  BtnY = TP.y;

  // consistency between displays is a mess...
  // this is some debug code to help show
  // where you pressed and the resulting map

  //Serial.print("real coordinates: ");
  //Serial.print(BtnX);
  //Serial.print(",");
  //Serial.println (BtnY);
  // Display.drawPixel(BtnX, BtnY, C_RED);

  //different values depending on where touch happened

  // x  = map(x, real left, real right, 0, 480);
  // y  = map(y, real bottom, real top, 320, 0);

  // tft with yellow headers
  //BtnX  = map(BtnX, 240, 0, 320, 0);
  //BtnY  = map(BtnY, 379, 0, 240, 0);

  // tft with black headers
  BtnX  = map(BtnX, 350, 3700, 0, 320);
  BtnY  = map(BtnY, 500, 3700, 0, 240);

  //Serial.print(", Mapped coordinates: ");
  //Serial.print(BtnX);
  //Serial.print(",");
  //Serial.println(BtnY);
  //Display.drawPixel(BtnX, BtnY, C_GREEN);

}