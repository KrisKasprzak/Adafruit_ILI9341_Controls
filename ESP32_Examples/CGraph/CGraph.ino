#include <Adafruit_ILI9341.h>           
#include <Adafruit_ILI9341_Controls.h>
#include <Fonts\FreeSans24pt7b.h>          
#include <Fonts\FreeSans18pt7b.h>
#include <Fonts\FreeSans9pt7b.h>

#define FONT_TEXT FreeSans24pt7b
#define FONT_TITLE FreeSans18pt7b
#define FONT_DATA FreeSans9pt7b

#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED   26

// defines for graph location and scales
#define X_ORIGIN    60
#define Y_ORIGIN    190
#define X_WIDE 		  250
#define Y_HIGH 		  140
#define X_LOSCALE 	0
#define X_HISCALE 	10
#define X_INC 	    2
#define Y_LOSCALE 	-1
#define Y_HISCALE 	1
#define Y_INC 	    0.5

#define TEXTCOLOR C_WHITE
#define GRIDCOLOR C_GREY
#define AXISCOLOR C_YELLOW
#define BACKCOLOR C_BLACK
#define PLOTCOLOR C_DKGREY
#define VOLTSCOLOR C_RED
#define SINCOLOR C_GREEN
#define COSCOLOR C_BLUE

// used to monitor elaspsed time
unsigned long oldTime;

// create a variable for each data data point
float x, volts;

// create an ID for each data to be plotted
int VoltID, SinID, CosID;

// create the display object
Adafruit_ILI9341 Display(TFT_CS, TFT_DC, TFT_RST);

// create the cartesian coordinate graph object
CGraph MyGraph(&Display, X_ORIGIN, Y_ORIGIN, X_WIDE, Y_HIGH, X_LOSCALE, X_HISCALE, X_INC, Y_LOSCALE, Y_HISCALE, Y_INC);

void setup() {

  Serial.begin(57600);

  // fire up the display
  Display.begin();
  Display.setRotation(3);
  Display.fillScreen(C_BLACK);

  // initialize the graph object
  MyGraph.init("Teensy Graph", "Time [sec]", "Volts", TEXTCOLOR, GRIDCOLOR, AXISCOLOR, BACKCOLOR, PLOTCOLOR, FONT_TITLE, FONT_DATA);

  // use the add method to create a plot for each data
  // PlotID = MyGraph.Add(data title, data color);
  //
  VoltID = MyGraph.add("Volts", VOLTSCOLOR);
  SinID = MyGraph.add("sin(x)", SINCOLOR);

  // optional
  MyGraph.setMarkerSize(VoltID, 0);
  MyGraph.setLineThickness(VoltID, 4);
  MyGraph.setMarkerSize(SinID, 2);

  MyGraph.drawLegend(LOCATION_BOTTOM);

  // these call are all optional
  // MyGraph.setYAxis(-1.5, 2.5, 0.5);  // reset the y axis at any time in your program
  // MyGraph.showTitle(false);          //  hide the title--good for big graph in tight space
  // MyGraph.showLegend(false);         //  hide the legend--good for big graph in tight space
  // MyGraph.showXScale(false);         //  hide the x scale--good for big graph in tight space
  // MyGraph.showYScale(false);         //  hide the y scale--good for big graph in tight space

  MyGraph.drawGraph();		// draw empty graph if you have a long delay before any plottable data


}

void loop() {

  // set the x value, should be in order and match the x scale (again you will
  // need to do your own math to get the plot to match the updte time in this loop

  volts = analogRead(A0) / 1024.0;
  MyGraph.setX(x);

  MyGraph.plot(VoltID, volts);
  MyGraph.plot(SinID, sin(x));


  // bump the x value
  x += .01;
  delay(10);

}