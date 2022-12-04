#include <Adafruit_ILI9341.h>
#include <Adafruit_ILI9341_Controls.h>
#include <Fonts\FreeSans18pt7b.h>
#include <Fonts\FreeSans12pt7b.h>
#include <XPT2046_Touchscreen.h>

// you must create and pass fonts to the function
#define FONT_TITLE FreeSans18pt7b
#define FONT_TEXT FreeSans12pt7b
// For the Adafruit shield, these are the default.
#define T_CS   12
#define T_IRQ  27
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED   26

int BtnX, BtnY;  // holders for screen coordinate drawing

Adafruit_ILI9341 Display(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);
TS_Point TP;

SliderD Vol(&Display);
SliderD Mid(&Display);
SliderD Base(&Display);
SliderD Treb(&Display);
// create the // Touch screen object


void setup() {

  Serial.begin(38400);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);


  Display.begin();
  Display.setRotation(3);

  Touch.begin();


  Vol.init (80, 70, 40, 270, 0, 100, C_WHITE, C_BLACK, C_RED);
  Base.init (240, 70, 40, 270, 0, 100, C_WHITE, C_BLACK, C_BLUE);
  Mid.init (80, 190, 40, 270, 0, 100, C_WHITE, C_BLACK, C_GREEN);
  Treb.init (240, 190, 40, 270, 0, 100, C_WHITE, C_BLACK, C_YELLOW);

  Display.fillScreen(C_BLACK);

  // draw the controls with an initial value
  // note that value must be in the scale range
  Vol.draw(0);
  Base.draw(50);
  Mid.draw(70);
  Treb.draw(28);
  Display.setTextColor(C_WHITE, C_BLACK);
  // draw text if you need
  Display.setCursor (65, 55);
  Display.print("Vol");
  Display.setCursor(225, 55);
  Display.print("Bas");
  Display.setCursor  (65, 175);
  Display.print("Mid");
  Display.setCursor  (225, 175);
  Display.print("Trb");

  Display.setCursor (65, 65);
  Display.print(Vol.value, 0);
  Display.setCursor(225, 65);
  Display.print(Base.value, 0);
  Display.setCursor  (65, 185);
  Display.print(Mid.value, 0);
  Display.setCursor  (225, 185);
  Display.print(Treb.value, 0);

}

void loop() {

  if (Touch.touched()) {
    ProcessTouch();
    // if press is in range of the ring, slide will occur

    //example in how to test for a changed state and disable a control
    if (Vol.slide(BtnX, BtnY)) {

      if (Vol.value > 80) {
        Base.disable();
        Base.draw(Base.value);
      }
      else {
        Base.enable();
        Base.draw(Base.value);
      }
    }
    Base.slide(BtnX, BtnY);
    Mid.slide(BtnX, BtnY);
    Treb.slide(BtnX, BtnY);

    // use the value property to report the controls value

    Display.setCursor (65, 65);
    Display.print(Vol.value, 0);
    Display.setCursor(225, 65);
    Display.print(Base.value, 0);
    Display.setCursor  (65, 185);
    Display.print(Mid.value, 0);
    Display.setCursor  (225, 185);
    Display.print(Treb.value, 0);



  }
}


bool ProcessButtonPress(Button TheButton) {

  if (TheButton.press(BtnX, BtnY)) {
    TheButton.draw(B_PRESSED);
    while (Touch.touched()) {
      if (TheButton.press(BtnX, BtnY)) {
        TheButton.draw(B_PRESSED);
      }
      else {
        TheButton.draw(B_RELEASED);
        return false;
      }
      ProcessTouch();
    }

    TheButton.draw(B_RELEASED);
    return true;
  }
  return false;

}

void ProcessTouch() {

  TP = Touch.getPoint();

  BtnX = TP.x;
  BtnY = TP.y;

  // consistency between displays is a mess...
  // this is some debug code to help show
  // where you pressed and the resulting map
  /*
     Serial.print("real: ");
     Serial.print(BtnX);
     Serial.print(",");
     Serial.print(BtnY);
     Display.drawPixel(BtnX, BtnY, C_RED);
  */
  //different values depending on where Touch happened

  // x  = map(x, real left, real right, 0, width-1);
  // y  = map(y, real bottom, real top, 0, height-1);

  // tft with black headers, yellow headers will be different
  BtnX  = map(BtnX, 350, 3700, 0, 320);
  BtnY  = map(BtnY, 500, 3700, 0, 240);
  /*
    Serial.print(", Mapped: ");
    Serial.print(BtnX);
    Serial.print(",");
    Serial.println(BtnY);
    Display.drawPixel(BtnX, BtnY, C_GREEN);
  */
  // cheap debounce
  delay(50);

}