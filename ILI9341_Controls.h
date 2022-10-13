/*
The MIT License (MIT)

library writen by Kris Kasprzak

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

On a personal note, if you develop an application or product using this library
and make millions of dollars, I'm happy for you!

rev		date			author				change
1.0		9/2019			kasprzak			initial code
2.0		9/2020			kasprzak			added shapes and sizes for handles
3.0		10/2020			kasprzak			fixed some repaint issues in CGraph, added marker support, added Button class with tons of methods
4.0		11/2020			kasprzak			fixed bugs added Button, Checkbox, OptionButton classes
5.0		11/2020			kasprzak			modified sliders, option and check to return true/false if pressed, and actual value stored in value property
5.1		11/2020			kasprzak			added automatic "blank out" old handle support insided draw() method in sliderH and SliderV (really needed when a slide is redrawn based on input other than a finger slide (encoder)

*/



#ifndef ILI9341_CONTROLS_H
#define ILI9341_CONTROLS_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#ifdef __cplusplus
#include "Arduino.h"
#endif

#include <Adafruit_ILI9341.h>   

#define G_REPAINT 0
#define G_DRAWOVER 1
#define BELOW 0
#define ABOVE 1

#define SLIDER_HANDLE_SIZE 16
#define HANDLE_NONE 0
#define HANDLE_CIRCLE 1
#define HANDLE_SQUARE 2
#define HANDLE_TRIANGLE_1 3
#define HANDLE_TRIANGLE_2 4
#define HANDLE_TRIANGLE_3 5

#ifndef C_BLACK

#define	C_BLACK   		0x0000
#define	C_BLUE    		0x001F
#define	C_RED     		0xF800
#define	C_GREEN   		0x07E0
#define C_CYAN    		0x07FF
#define C_MAGENTA 		0xF81F
#define C_YELLOW  		0xFFE0  
#define C_WHITE   		0xFFFF

#define C_LTBLUE		0xB6DF    
#define C_LTTEAL		0xBF5F  
#define C_LTGREEN     	0xBFF7
#define C_LTCYAN		0xC7FF
#define C_LTRED       	0xFD34
#define C_LTMAGENTA   	0xFD5F
#define C_LTYELLOW    	0xFFF8
#define C_LTORANGE    	0xFE73
#define C_LTPINK      	0xFDDF
#define C_LTPURPLE		0xCCFF
#define C_LTGREY      	0xE71C  

#define C_TEAL			0x0438       
#define C_ORANGE      	0xFD20          
#define C_PINK        	0xF81F
#define C_PURPLE		0x801F
#define C_GREY       	0xC618
 
#define C_DKBLUE      	0x000D
#define C_DKTEAL		0x020C
#define C_DKGREEN     	0x03E0      
#define C_DKCYAN      	0x03EF      
#define C_DKRED       	0x6000
#define C_DKMAGENTA   	0x8008
#define C_DKYELLOW    	0x8400
#define C_DKORANGE   	0x8200         
#define C_DKPINK      	0x9009
#define C_DKPURPLE    	0x4010
#define C_DKGREY      	0x3186

#define C_MDGREY      	0x7BCF
#endif


#define B_PRESSED true
#define B_RELEASED false
#define TFT_DEBOUNCE 100  // debounce delay to minimize screen repress

#define CORNER_AUTO   -1
#define CORNER_SQUARE  0

#define  MAX_OPTION 20
#define OPTION_BUTTON_RADIUS 10

#define CHECKBOX_SIZE 20

#define C_DISABLE_LIGHT 0xC618
#define C_DISABLE_MED	0x7BCF
#define C_DISABLE_DARK	0x3186

class CGraph {

public:

	CGraph(Adafruit_ILI9341 *disp, float GraphXLoc, float GraphYLoc, float GraphWidth, float GraphHeight, float XAxisLow, float XAxisHigh, float XAxisInc, float YAxisLow, float YAxisHigh, float YAxisInc);

	void init(const char *Title, const char *XAxis, const char *YAxis, uint16_t TextColor, uint16_t GridColor, uint16_t AxisColor, uint16_t BackColor,uint16_t PlotColor, const GFXfont &TitleFont , const GFXfont &AxisFont );

	void plot(int ID, float y);

	void setX(float x);

	int add(const char * DataLabel, uint16_t DataColor );

	void setYAxis(float Ylow, float YHigh, float YInc);

	void setXAxis(float Xlow, float XHigh, float XInc);

	void showTitle(bool val);

	void showLegend(bool val);

	void showXScale(bool val);

	void showYScale(bool val);

	void setMarkerSize(int ID, byte val);

	void showCurrentBar(float val);

	void drawGraph();

private:

		Adafruit_ILI9341	*d;
		GFXfont	tf;
		GFXfont	af;
		int		ID = 0;
		float	x, y;
		float	i, j;
		bool	st, sl, sxs, sys;
		float	Delta;
		int		k;
		float	XLow, XHigh, XInc;
		float	YLow, YHigh, YInc;
		bool	RedrawGraph = true;
		bool	HaveFirstPoint[10];
		bool	showcb = false;
		float	XPoint, YPoint, oXPoint[10], oYPoint[10], TextHeight, oPoint;
		float	XDec = 0.0, YDec = 0.0;
		char	text[30];
		byte	oOrientation = 0;
		float	gx, gy, gw, gh;
		int		StartPointX, StartPointY;
		char	buf0[20], buf1[20], buf2[20], buf3[20], buf4[20], buf5[20], buf6[20], buf7[20], buf8[20], buf9[20];
		char    *dl[20] = {buf0, buf1, buf2, buf3, buf4, buf5, buf6, buf6, buf8, buf9};
		char	t[25];
		char	xa[20];
		char	ya[20];
		uint16_t	tc;
		uint16_t	dc[10];
		uint16_t	ac;
		uint16_t	gc;
		uint16_t	bc;
		uint16_t	pc;
		byte		pdia[20];

		float MapFloat(float x, float in_min, float in_max, float out_min, float out_max);


};

class SliderH {

 public:

	SliderH(Adafruit_ILI9341 *Display);		// class constructor
		
	void init(uint16_t SliderX, uint16_t SliderY, uint16_t SliderW, float ScaleLow, float ScaleHi, float Scale, float Snap, uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);		// initializer
  
	void draw(float val);					// method to draw complete slider
		
	bool slide(float ScreenX, float ScreenY);			// method to move handle as user drags finger over handle, this method automatically looks for a valid range press
  
	void setColors(uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);		// way to reset colors (useful for drawing enabled or disabled)

	void setHandleColor(uint16_t HandleColor);	// method to just draw the handle (useful for showing handle in green for OK value

	void setDisableColor(uint16_t HandleColor, uint16_t SliderColor);	// method to just draw the handle (useful for showing handle in green for OK value

	void setHandleSize(int size);

	void disable();

	void enable();

	void show();

	void hide();

	void setHandleShape(byte shape);

	void drawSliderColor(bool color);

	void setPressDebounce(byte Debounce);

	float value;

private:

	Adafruit_ILI9341 *d;			// the display object
	uint16_t sColor;		// the slider color
	uint16_t bColor;		// the slider background color
	uint16_t hColor;		// the sliders drag handle
	uint16_t dsColor;
	uint16_t dhColor;
	uint16_t tsColor;
	uint16_t ssColor;
	uint16_t thColor;
	float x;
	float y;
	uint16_t l;			// the left coordinate of the scale
	uint16_t t;			// the top coordinate of the scale
	uint16_t w;			// the width of the scale
	float ox;			// the old screen x value where user pressed
	bool enabled;
	float sl;				// the scale lower value
	float sh;				// the scale upper value
	float pos;				// the position on the scale
	float sn;				// the snap increment
	float sc;				// the scale increment
	float ce;				// the tick mark where zero is (for drawing heavy line on +/- scales
	float i;				// loop counter
	int handlesize;
	byte handleshape;
	bool visible;
	bool colorscale;		// flag to draw slider in handle color
	float MapFloat(float x, float fromLow, float fromHigh, float toLow, float toHigh); // why Arduino has no mapping for floats is beyond me, here it is...
	byte debounce;
	
  };

class SliderV {

 public:

	SliderV(Adafruit_ILI9341 *Display); // class constructor
  
	void init(uint16_t SliderX, uint16_t SliderY, uint16_t SliderH, float ScaleLow, float ScaleHi, float scale, float snap, uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);	// initializer
   
	void draw(float val);						// method to draw complete slider
   
	bool slide(uint16_t ScreenX, uint16_t ScreenY);	   // method to move handle as user drags finger over handle, this method automatically looks for a valid range press
    
	void setColors(uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);	// way to reset colors (useful for drawing enabled or disabled)

	void setHandleColor(uint16_t HandleColor);		// method to just draw the handle (useful for showing handle in green for OK value

	void setHandleSize(int val);
	
	void setHandleShape(byte val);

	void drawSliderColor(bool val);

	void setDisableColor(uint16_t HandleColor, uint16_t SliderColor);	// method to just draw the handle (useful for showing handle in green for OK value

	void setScale(float ScaleLow, float ScaleHi, float scale = 0.0, float snap= 0.0);

	void disable();

	void enable();

	void show();

	void hide();

	void setPressDebounce(byte Debounce);

	float value;

private:

	Adafruit_ILI9341 *d;			// the display object
	uint16_t sColor;		// the slider color
	uint16_t bColor;		// the slider background color
	uint16_t hColor;		// the sliders drag handle
	uint16_t dsColor;
	uint16_t dhColor;
	uint16_t tsColor;
	uint16_t thColor;
	uint16_t x;			// the left coordinate of the scale
	uint16_t y;			// the top coordinate of the scale
	uint16_t l;			// the left coordinate of the scale
	uint16_t t;			// the top coordinate of the scale
	uint16_t w;			// the with of the scale
	uint16_t h;			// the with of the scale
	float oy;			// the old screen y value where user pressed
	float sl;				// the scale lower value
	float sh;				// the scale upper value
	float pos;				// the screen coordinate position
	float sn;				// the snap increment
	float sc;				// the scale increment
	float ce;				// the tick mark where zero is (for drawing heavy line on +/- scales
	float i;				// loop counter
	byte tl;
	bool colorscale;		// flag to draw slider in handle color
	float MapFloat(float x, float fromLow, float fromHigh, float toLow, float toHigh);// why Arduino has no mapping for floats is beyond me, here it is...
	int tLen, tHi;
	int handlesize;
	byte handleshape;
	bool enabled;
	bool visible;
	byte debounce;
  };

class SliderOnOff {

 public:
	
	SliderOnOff(Adafruit_ILI9341 *Display, uint16_t SliderX, uint16_t SliderY, uint16_t SliderW, uint16_t SliderH, uint16_t SliderColor, uint16_t BackColor, uint16_t OnColor, uint16_t OffColor);// class constructor
  
	void draw(bool state);			// method to draw complete slider
   
	bool slide(float ScreenX,float ScreenY);	// method to move handle as user drags finger over handle, this method automatically looks for a valid range press

	bool changed();						// method to return if state change, useful for determining if a something should be done but not done unless state change

	bool getValue();
     
private:

	Adafruit_ILI9341 *_d;			// the display object
	uint16_t _sColor;		// the slider color
	uint16_t _bColor;		// the slider background color
	uint16_t _onColor;		// the sliders on color
	uint16_t _offColor;		// the sliders on color
	uint16_t _l;				// the left coordinate of the scale
	uint16_t _t;				// the top coordinate of the scale
	uint16_t _w;				// the with of the scale
	uint16_t _h;				// the with of the scale
	bool _pos;				// the screen coordinate position
	bool _changed;			//flag to track if button was just changed
  };

/*

Checkbox class

*/


class CheckBox {
public:
	CheckBox(Adafruit_ILI9341 *Display) {d = Display; }

	void init(int16_t ButtonX, uint16_t ButtonY, uint16_t OutlineColor, uint16_t UPColor, uint16_t DownColor, uint16_t TextColor, uint16_t BackgroundColor, int TextOffsetX,int TextOffsetY, const char *Text, const GFXfont &TextFont) {

		x = ButtonX ;
		y = ButtonY + CHECKBOX_SIZE;
		s = CHECKBOX_SIZE;
		ct = 3;
		oc = OutlineColor;
		uc = UPColor;
		dc = DownColor;
		tc = TextColor;
		bc = BackgroundColor;
		doc = C_DISABLE_LIGHT;
		duc = C_DISABLE_MED;
		ddc = C_DISABLE_DARK;
		dtc = C_DISABLE_MED;
		strncpy(label,Text, 60);
		tox = TextOffsetX;
		toy = TextOffsetY;
		f = TextFont;
		enabled = true;
		state = true; // true=up, false=down
		visible = true;
		value = -1;
		debounce = TFT_DEBOUNCE;

	}

	void draw(bool val) {

		uint16_t fill, outline, tcolor;

		if (!visible) {
			d->fillRoundRect(x, y-s, s, s, ct, bc);
			return;
		}
		if (val){
			// last exit was no press so restore val from internal saved state
			val = state;
		}
		state = val;
		// store the variable in the public variable
		value = val;
		if (state) {
			fill = uc;
			outline = oc;
			tcolor = tc;
		} 
		else {
			fill =  dc;
			outline = oc;
			tcolor = tc;
		}

		if (!enabled){
			if (state) {
				fill = duc;
				outline = doc;
				tcolor = dtc;
			} 
			else {
				fill =  ddc;
				outline = doc;
				tcolor = dtc;
			}
		}
	
		d->fillRoundRect(x, y-s, s, s, ct, fill);
		d->drawRoundRect(x, y-s, s, s, ct, outline);

		d->setCursor(x + tox+(s/2), y -(s/2)+ toy);
		d->setFont(&f);
		d->setTextColor(tcolor);
		d->print(label);
	}

	bool press(int16_t SceenX, int16_t ScreenY) {
		bool pressed = false;
		if ((!visible) || (!enabled)) {
			return pressed;
		}

		if (   ( (SceenX >= x) && (SceenX <= (x + s) )) && ((ScreenY >= y-s) && (ScreenY <= (y)))   ) {	
			state = !state;
			draw(state);
			delay(debounce);
			// store the variable in the public variable
			value = state; 
			pressed = true;
		}
		return pressed;
	}

	void show() {
		visible = true;
	}


	void hide() {
		visible = false;
	}

	void disable() { 
		enabled = false;
	}
	void enable() { 
		enabled = true;
	}


	void resize(int16_t ButtonX, int16_t ButtonY, uint8_t Size) {
		hide();
		draw(state);
		x = ButtonX;
		y = ButtonY;
		s = Size;
		show();
		draw(state);
		
	}

	void setColors(uint16_t OutlineColor, uint16_t UPColor, uint16_t DownColor, uint16_t BackgroundColor, uint16_t DisableOutlineColor,  uint16_t DisableTextColor, uint16_t DisableUPColor, uint16_t DisableDownColor) {
		
		oc = OutlineColor;
		uc = UPColor;
		dc = DownColor;
		bc = BackgroundColor;
		doc = DisableOutlineColor;
		duc = DisableUPColor;
		ddc = DisableDownColor;
		dtc = DisableTextColor;
		
	}




	void setText(int TextOffsetX,int TextOffsetY, const char *Text, const GFXfont &TextFont) {

		tox = TextOffsetX;
		toy = TextOffsetY;
		strncpy(label,Text, 60);
		f = TextFont;

	}

	void setCornerRadius(int val) {
		ct = val;

	}
		
	bool isEnabled() { 
		return enabled;
	}
	
	bool isVisibled() { 
		return visible;
	}

	void setPressDebounce(byte Debounce) { 
		debounce = Debounce;
	}


	bool value;

private:
	Adafruit_ILI9341 *d;
	char label[60];
	GFXfont f;
	int16_t x, y;
	uint16_t s, ct;
	uint16_t oc, uc, dc, bc, doc, duc, ddc, dtc, tc;
	bool state;
	int tox, toy;
	bool enabled;
	bool visible;
	byte debounce;
};

#endif