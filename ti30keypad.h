/***************************************************
 Filename: ti30keypad.h

 ***************************************************/

#ifndef ti30keypad_h
#define ti30keypad_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sr595.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/keysymdef.h>
#include <X11/extensions/XTest.h>

// WiringPi Pins, not GPIOs
#define CLOCK_PIN   25//??? prolly display
#define DATA_PIN    27//???
#define LATCH_PIN   26//???
#define ONKEY_PIN   9//???
#define BACKLIGHT_PIN   1//for display backlight brightness pin

// Event Types
#define EVENT_PRESS 1
#define EVENT_RELEASE 2

// Delays
#define SCAN_DELAY      5 // In Milliseconds
#define BOUNCE_DELAY    250 // In MilliSeconds

// Mode corresponds to the keyboard layout used as well as the icon displayed
#define MODE_LETTER 1       // letter.png
#define MODE_SYMBOL 2       // symbol.png
#define MODE_GAME 3       // game.png


// None of the defined KeySymbols are in the 0x8000 range
//#define SPECIAL_BRIGHT_UP_KEY         0x8005  //???
//#define SPECIAL_BRIGHT_DOWN_KEY       0x8006  //???
#define SPECIAL_CONTROL_LOCK          	0x8007  //???
#define SPECIAL_SHIFT_LOCK          	0x8008  //???
#define SPECIAL_ALT_LOCK          	0x8009  //???
#define SPECIAL_POWER          		0x8001  //???



#define SHIFT_SYMBOL_SIZE 39  //???
#define MAX_BRIGHTNESS   10

GtkStatusIcon *tray;
Display *display;

//column 24 and 25 are messed up
/*0 1 2 3 4 5 6 7
0 . . . . - - . .
1 . . . . - - . .
2 . . . . - - . .
3 . . . . - - . .
4 . . . . - - . .


*/

//Power Pins (PC 0-1, PD 0-2 on the pcb)
int rowPins[] = {5,4,3,2,1}; // Rows A, B, C, D, E
//Read Pins (PA 0-7 on the calculators pcb)
int colPins[] = {29,28,27,26,25,24,23,22}; // Columns I, J, K, L, M, N, O, P

KeySym letterLayout[5][8] = {
// Static 10 buttons
    {XK_F11, SPECIAL_CONTROL_LOCK, SPECIAL_SHIFT_LOCK, SPECIAL_ALT_LOCK, XK_asterisk, XK_asterisk, XK_Home, SPECIAL_POWER},  // Row A: ...
    {XK_Tab, XK_Escape, NoSymbol, // Row B (start 2)
// Dynamic 29 buttons
     XK_BackSpace, XK_space, XK_KP_Enter, XK_q, XK_w}, // Row B: ...
    {XK_e, XK_r, XK_t, XK_y, XK_u, XK_i, XK_o, XK_p},  // Row C: ...
    {XK_a, XK_s, XK_d, XK_f, XK_g, XK_h, XK_j, XK_k},  // Row D: ...
    {XK_l, XK_z, XK_x, XK_c, XK_v, XK_b, XK_n, XK_m}   // Row E: ...
};

//++symbol layout
//`1234567890-=[];'\,./~!@#$%^&*()+{}:"|<>?
KeySym symbolLayout[5][8] = {
// Static 10 buttons
    {XK_F11, SPECIAL_CONTROL_LOCK, SPECIAL_SHIFT_LOCK, SPECIAL_ALT_LOCK, XK_asterisk, XK_asterisk, XK_Home, SPECIAL_POWER},  // Row A: ...
    {XK_Tab, XK_Escape, NoSymbol, // Row B (start 2)
// Dynamic 29 buttons
     XK_BackSpace, XK_space, XK_KP_Enter, XK_ampersand, XK_1}, // Row B: ...
    {XK_2, XK_3, XK_4, XK_5, XK_6, XK_7, XK_8, XK_9},  // Row C: ...
    {XK_0, XK_minus, XK_equal, XK_bracketleft, XK_bracketright, XK_semicolon, XK_apostrophe, XK_backslash},  // Row D: ...
    {XK_less, XK_comma, XK_period, XK_slash, XK_0, XK_0, XK_0, XK_0}   // Row E: ...
};

//int keyMap[8][5][2]={
//{{0,1},{},{},{1,0},{4,0}},
//{{1,1},{},{},{},{}},
//{{2,1},{},{},{},{}},
//{{3,1},{},{},{},{}},
//{{4,1},{},{},{},NULL},
//{{},{},{},{},{}},
//{{},{},{},{},{}},
//{{},{},{},{},{}},
//}

//++game layout
//WASD="arrows" Esc, Space, idk, ...

int mode = MODE_LETTER;
int lastMode = MODE_SYMBOL;
gboolean ShiftLock = FALSE;
gboolean ControlLock = FALSE;
gboolean AltLock = FALSE;
gboolean isKeyPressed = FALSE;
int colCount = 0;
int rowCount = 0;
int brightness = MAX_BRIGHTNESS;
GString * executable;


int getColCount(void);
void setValue(int outputValue);
void setBit(int bit);
gchar * getImagePath(char * imageFile);
gchar * getModeIconImage(void);
gboolean specialKey(KeySym keySym, int eventType);
void brightnessUp(void);
void brightnessDown(void);
void changeControlLock(void);
void changeShiftLock(void);
void changeAltLock(void);
void updateStatusIcon(void);
void changeMode(int newMode);
void cycleModes(void);
void destroy(GtkWidget *widget, gpointer data);
void setup(void);
void powerDown(void);
void emulateKeyPress(KeySym keySym);
void emulateKeyRelease(KeySym keySym);
KeySym getKeySymbol(int row, int col);
gboolean loop(gpointer data);
int main(int argc, char *argv[]);

#endif /* ti30keypad_h */
