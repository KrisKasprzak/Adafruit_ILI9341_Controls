#include <Adafruit_ILI9341.h>
#include <Adafruit_ILI9341_Controls.h>
#include <Fonts\FreeSans18pt7b.h>
#include <Fonts\FreeSans9pt7b.h>

// you must create and pass fonts to the function
#define FONT_TITLE FreeSans18pt7b
#define FONT_DATA FreeSans9pt7b
// For the Adafruit shield, these are the default.
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED   26

// defines for locations
#define BXCENTER 80
#define BYCENTER 120
#define BDIAMETER 75
#define BLOWSCALE 0
#define BHIGHSCALE 1200
#define BSCALEINC 200
#define BSWEEPANGLE 300

#define VXCENTER 240
#define VYCENTER 120
#define VDIAMETER 75
#define VLOWSCALE 0
#define VHIGHSCALE 4
#define VSCALEINC .5
#define VSWEEPANGLE 300

// defines for colors
#define BNEEDLECOLOR C_ORANGE
#define BDIALCOLOR C_DKBLUE
#define BTEXTCOLOR C_WHITE
#define BTICCOLOR C_GREY

#define VNEEDLECOLOR C_WHITE
#define VDIALCOLOR C_DKBLUE
#define VTEXTCOLOR C_WHITE
#define VTICCOLOR C_GREY

// create the display object
Adafruit_ILI9341 Display(TFT_CS, TFT_DC, TFT_RST);

int bBits;
float bVolts;
float bData;

// create the dial object(s)
Dial Bits(&Display, BXCENTER, BYCENTER, BDIAMETER, BLOWSCALE , BHIGHSCALE, BSCALEINC, BSWEEPANGLE);
Dial Volts(&Display, VXCENTER, VYCENTER, VDIAMETER, VLOWSCALE , VHIGHSCALE, VSCALEINC, VSWEEPANGLE);

void setup() {

  Serial.begin(9600);

  // you know the drill
  pinMode(PIN_LED, OUTPUT);

  Display.begin();
  Display.setRotation(3);
  Display.fillScreen(C_BLACK);
  digitalWrite(PIN_LED, 255);

  // initialize the dials
  Bits.init(BNEEDLECOLOR, BDIALCOLOR, BTEXTCOLOR, BTICCOLOR, "Bits", FONT_TITLE, FONT_DATA);
  Volts.init(VNEEDLECOLOR, VDIALCOLOR, VTEXTCOLOR, VTICCOLOR, "Volts", FONT_TITLE, FONT_DATA);

}

void loop() {

  // get some data
  bBits = analogRead(A4);
  bVolts = bBits * 3.3 / 1024;

  // update the dials
  Bits.draw(bBits);
  Volts.draw(bVolts);

  delay(150);


}