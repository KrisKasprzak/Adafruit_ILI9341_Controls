/*

  MCU                       https://www.amazon.com/Teensy-3-2-with-pins/dp/B015QUPO5Y/ref=sr_1_2?s=industrial&ie=UTF8&qid=1510373806&sr=1-2&keywords=teensy+3.2
  Display                   https://www.amazon.com/Wrisky-240x320-Serial-Module-ILI9341/dp/B01KX26JJU/ref=sr_1_10?ie=UTF8&qid=1510373771&sr=8-10&keywords=240+x+320+tft

  // required
  CheckBox(Adafruit_ILI9341 *Display) {d = Display; }
  void init(int16_t ButtonX, uint16_t ButtonY, uint16_t OutlineColor, uint16_t UPColor, uint16_t DownColor, uint16_t TextColor, uint16_t BackgroundColor, int TextOffsetX,int TextOffsetY, const char *Text, const ILI9341_t3_font_t &TextFont ) {
  void draw(int val) {
  int press(int16_t SceenX, int16_t ScreenY) // returns if control was clicked. use value property to get the state

  // optional button methods
  void show() {
  void hide() {
  void disable() {
  void enable() {
  void resize(int16_t ButtonX, int16_t ButtonY, uint8_t Size) {
  void setColors(uint16_t OutlineColor, uint16_t UPColor, uint16_t DownColor, uint16_t BackgroundColor, uint16_t DisableOutlineColor,  uint16_t DisableTextColor, uint16_t DisableUPColor, uint16_t DisableDownColor) {
  void setText(int TextOffsetX,int TextOffsetY, const char *Text, const ILI9341_t3_font_t &TextFont) {
  void setCornerRadius(int val) {
  bool isEnabled() {
  bool isVisibled() {
  void setPressDebounce(byte Debounce) {
  bool value;

*/

/*

  Implementing this library is done in 5 lines of code, look for Step xxx below

*/

#include <Adafruit_ILI9341.h>          
#include <Adafruit_ILI9341_Controls.h>
#include <Fonts\FreeSans24pt7b.h>          
#include <Fonts\FreeSans18pt7b.h>
#include <Fonts\FreeSans12pt7b.h>
#include <XPT2046_Touchscreen.h>

// you must create and pass fonts to the function
#define FONT_TITLE FreeSans24pt7b
#define FONT_TEXT FreeSans12pt7b
// For the Adafruit shield, these are the default.
#define T_CS   12
#define T_IRQ  27
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED   26


#define LONG_PRESS_DURATION 1000
#define NO_PRESS 0
#define SHORT_PRESS 1
#define LONG_PRESS 2

#define ROW1 55
#define ROW2 90
#define ROW3 125
#define ROW4 160
#define ROW5 215

#define OUTLINECOLOR  C_GREY
#define CHECKEDCOLOR      C_GREEN
#define UNCHECKEDCOLOR    C_BLACK
#define BACKCOLOR    C_BLACK
#define TEXTCOLOR C_WHITE

int BtnX, BtnY;

Adafruit_ILI9341 Display(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);
TS_Point TP;

// Step 2 create an object for each check box
CheckBox CB1(&Display);
CheckBox CB2(&Display);
CheckBox CB3(&Display);
CheckBox CB4(&Display);
CheckBox CB5(&Display);

void setup() {

  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);

  // Step 3 create each each check box, passing in the location, colors, text offsets (to let you control text location
  // text and ILI9341 text font, note size and disable colors have defaults that can be overridded before draw
  // method or change the #define in the .h file
  CB1.init(50, ROW1, OUTLINECOLOR, CHECKEDCOLOR, UNCHECKEDCOLOR, TEXTCOLOR, BACKCOLOR, 0, 0, "Bananas", FONT_TEXT );
  CB2.init(50, ROW2, OUTLINECOLOR, CHECKEDCOLOR, UNCHECKEDCOLOR, TEXTCOLOR, BACKCOLOR, 0, 0, "Apples", FONT_TEXT );
  CB3.init(50, ROW3, OUTLINECOLOR, CHECKEDCOLOR, UNCHECKEDCOLOR, TEXTCOLOR, BACKCOLOR, 0, 0, "Cherries", FONT_TEXT );
  CB4.init(50, ROW4, OUTLINECOLOR, CHECKEDCOLOR, UNCHECKEDCOLOR, TEXTCOLOR, BACKCOLOR, 0, 0, "Pickles", FONT_TEXT );
  CB5.init(50, ROW5, OUTLINECOLOR, CHECKEDCOLOR, UNCHECKEDCOLOR, TEXTCOLOR, BACKCOLOR, 0, 0, "Only allow fruit", FONT_TEXT );


CB5.setCheckBoxSize(30);

  // fire up the display
  Display.begin();

  // fire up the touch display
  Touch.begin();

  Display.setRotation(3);

  // turn the brightness up
  digitalWrite(PIN_LED, HIGH);

  Display.fillScreen(C_BLACK);
  Display.fillRect(0, 0, 480, 50, C_DKBLUE);
  Display.setTextColor(C_WHITE);
  Display.setFont(&FONT_TITLE);
  Display.setCursor(10 , 40 );
  Display.print(F("Checkbox"));

  // Step 4 draw the check box controls
  // optional, you can set other parameters before the draw method (size for example)
  CB1.draw(true);
  CB2.draw(true);
  CB3.draw(true);
  CB4.draw(true);
  CB5.draw(false);

}

void loop() {

  if (Touch.touched()) {
    ProcessTouch();

    // Step 5 upon press of the checkbox process accordingly
    // optional, you can set other parameters upon pressing a check box
    // such as setting color or text (could be useful in re-drawing the control
    // with different text, enabling /disabling a control
    // just call the draw event after chaning parameters

    CB1.press(BtnX, BtnY);
    CB2.press(BtnX, BtnY);
    CB3.press(BtnX, BtnY);
    CB4.press(BtnX, BtnY);
    // if you really need to monitor if the control was clicked
    // here's how, this may be needed if you have a complicated UI
    // and don't need to automatically change things--code here automatically
    // updates items based on check box value (see if else sections, these
    // run even of check box was not pressed
    // do not use the return value as check box state
    // only use Checkbox.value for the state
    bool changed = CB5.press(BtnX, BtnY);

    // as mentioned above, you code processes regardless if checkbox was clicked
    if (CB1.value) {
      // un checked your code goes here
    }
    else {
      // checked, your code goes here
    }


    if (CB2.value) {
      // un checked your code goes here
    }
    else {
      // checked, your code goes here
    }
    if (CB3.value) {
      // un checked your code goes here
    }
    else {
      // checked, your code goes here
    }
    if (CB4.value) {
      // un checked your code goes here
    }
    else {
      // checked, your code goes here
    }

    // as mentioned above, you you don't want to process code unless checkbox was clicked
    // wrap a change test around checkbox values
    if (changed) {
      if (CB5.value) {
        CB4.disable();
        CB4.draw(false); // your call, but if option disabled, maybe force state to false
      }
      else {
        CB4.enable();
        CB4.draw(CB4.value);
      }
    }
  }
}

// my own processing function to handle press and convert to proper screen
// coordinates
// i've found so many differences between different screens, i needed an easy
// way to handle returning screen calcualtions
// my code uses global button x and button y locations
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