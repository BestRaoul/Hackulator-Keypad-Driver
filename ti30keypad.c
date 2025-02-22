/***************************************************
  Filename: ti30keypad.c

***************************************************/
// My ToDo:
// adapt specialKeys ()
// fix emulateKeyPress/Release with shift and control Locks


// To Do:
// Add Screen to Black for Shutdown
// Add functionality so that if you rightclick the status icon, it shows the about dialog (optional)
// Remove any unused functions
// Remove Debugging Messages (Search for g_print)
// Polish up any other small details

#include "ti30keypad.h"

int getColCount(void)
{
    return sizeof(colPins) / sizeof(colPins[0]);
}

int getRowCount(void)
{
    return sizeof(rowPins) / sizeof(rowPins[0]);
}

//works
void setValue(int outputValue)
{
    int bit;
    for (bit = 0 ; bit < rowCount; ++bit) {
        digitalWrite (rowPins[bit], outputValue & (1 << bit));
    }
}

//works
void setBit(int bit)
{
    setValue(1 << bit);
}

//fix adapt to my code case
/*
// gboolean specialKey(KeySym keySym, int eventType)
// {
//     // If Special Key, respond and return true
//     if (eventType == EVENT_RELEASE) {
//         if (keySym == SPECIAL_ALPHA_UPPER_KEY) {
//             changeMode(MODE_ALPHA_UPPER);
//         } else if (keySym == SPECIAL_ALPHA_LOWER_KEY) {
//             changeMode(MODE_ALPHA_LOWER);
//         } else if (keySym == SPECIAL_2ND_KEY) {
//             changeMode(MODE_SECOND);
//         } else if (keySym == SPECIAL_NORMAL_KEY) {
//             changeMode(MODE_NORMAL);
//         } else if (keySym == SPECIAL_LOCK_KEY) {
//             changeAlphaLock();
//         } else if (keySym == SPECIAL_BRIGHT_UP_KEY) {
//             brightnessUp();
//         } else if (keySym == SPECIAL_BRIGHT_DOWN_KEY) {
//             brightnessDown();
//         } else if (keySym == SPECIAL_CONTROL_LOCK) {
//             changeControlLock();
//         }
//     }
//
//     if (keySym == SPECIAL_ALPHA_UPPER_KEY ||
//         keySym == SPECIAL_ALPHA_LOWER_KEY ||
//         keySym == SPECIAL_2ND_KEY ||
//         keySym == SPECIAL_LOCK_KEY ||
//         keySym == SPECIAL_NORMAL_KEY ||
//         keySym == SPECIAL_BRIGHT_UP_KEY ||
//         keySym == SPECIAL_BRIGHT_DOWN_KEY ||
//         keySym == SPECIAL_CONTROL_LOCK) {
//         return TRUE;
//     }
//
//     return FALSE;
// }
*/

gboolean specialKey(KeySym keySym, int eventType)
{
    // If Special Key, respond and return true
    if (eventType == EVENT_RELEASE) {
        if (keySym == SPECIAL_CONTROL_LOCK) {
            changeControlLock();
        } else if (keySym == SPECIAL_SHIFT_LOCK) {
	    changeShiftLock();
	} else if (keySym == SPECIAL_ALT_LOCK) {
	    changeAltLock();
	} else if (keySym == SPECIAL_POWER) {
	    shutdown();
	}
    }

    if (keySym == SPECIAL_CONTROL_LOCK
	|| keySym == SPECIAL_SHIFT_LOCK
	|| keySym == SPECIAL_ALT_LOCK
	|| keySym == SPECIAL_POWER
	) {
        return TRUE;
    }
    return FALSE;
}
//??? not used
/*
void brightnessUp(void)
{
    if (brightness < MAX_BRIGHTNESS) {
        brightness += 1;
        softPwmWrite (BACKLIGHT_PIN, brightness);
    }
    g_print("Brightness Up [%i/%i]", brightness, MAX_BRIGHTNESS);
    changeMode(MODE_NORMAL);
}
//??? not used
void brightnessDown(void)
{
    if (brightness > 0) {
        brightness -= 1;
        softPwmWrite (BACKLIGHT_PIN, brightness);
    }
    g_print("Brightness Down [%i/%i]", brightness, MAX_BRIGHTNESS);
    changeMode(MODE_NORMAL);
}
*/

// This function handles lock status for the non-special keys

void changeControlLock(void)
{
    if (ControlLock) {
        ControlLock = FALSE;
    } else {
        ControlLock = TRUE;
    }
}

void changeShiftLock(void)
{
    if (ShiftLock) {
        ShiftLock = FALSE;
    } else {
        ShiftLock = TRUE;
    }
}

void changeAltLock(void)
{
    if (AltLock) {
        AltLock = FALSE;
    } else {
        AltLock = TRUE;
    }
}


//idk remove idk
// gchar * getImagePath(char * imageFile)
// {
//     // Can't get it working with autostart, so just using Absolute path for now
//     //char currentFolder[256];
//     //char pathSave[256];
//     const char* imageFolder = "/images/";
//     GString * imagePath = g_string_new("/home/pi/ti30keypad");
// /*
//     gchar * result = g_strstr_len (executable->str, 1, "/");
//     if (result == NULL) {
//         if (getcwd(currentFolder, sizeof(currentFolder)) == NULL) {
//             g_print ("Error getting Current Working Directory\n");
//         }
//     } else {
//         getcwd(pathSave, sizeof(pathSave));
//         chdir(executable->str);
//         getcwd(currentFolder, sizeof(currentFolder));
//         chdir(pathSave);
//     }*/
//
//     //g_string_append(imagePath, (char*) currentFolder);
//     g_string_append(imagePath, imageFolder);
//     g_string_append(imagePath, imageFile);
//
//     return imagePath->str;
// }
// //idk
// gchar * getModeIconImage(void)
// {
//     if (mode == MODE_SECOND) {
//         return "2nd.png";
//     } else if (mode == MODE_ALPHA_LOWER) {
//         return "lowercase.png";
//     } else if (mode == MODE_ALPHA_UPPER) {
//         return "uppercase.png";
//     } else if (mode == MODE_TI30) {
//         return "ti30mode.png";
//     }
//
//     return "numbers.png";
// }
// //idk
// void updateStatusIcon(void)
// {
//     gtk_status_icon_set_from_file (tray, getImagePath(getModeIconImage()));
// }

//works i guess
void changeMode(int newMode)
{
    lastMode = mode;
    mode = newMode;
//    if (newMode == MODE_NORMAL || newMode == MODE_TI30) {
//        isAlphaLockActive = FALSE;
//        isControlLockActive = FALSE;
//    }
//    if (newMode == MODE_SECOND) {
//        isControlLockActive = FALSE;
//    }
//    updateStatusIcon();
}
//works
void cycleModes(void)
{
     if (mode == MODE_LETTER) {
         changeMode(MODE_SYMBOL);
     } else if (mode == MODE_SYMBOL) {
         changeMode(MODE_GAME);
     } else {
     	 changeMode(MODE_LETTER);
     }
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit ();
}
//fix shift and control shenenigans
//seems like buttons that require shift will automatically respond with the non-shift key
//seems like you can combo key + shift + control by simulatingKey(shift,contrl);

void emulateKeyPress(KeySym keySym)
{
    KeyCode modcode = 0; //init value
    isKeyPressed = TRUE;

    if (specialKey(keySym, EVENT_PRESS)) {
        return;
    }/* else {
        handleLockStatus(keySym);
    }*/

    if (keySym == NoSymbol) {
        return;
    }

    modcode = XKeysymToKeycode(display, keySym);

    if (ShiftLock) {
        //g_print("Event: Shift Pressed\n");
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), True, 0);
        XFlush(display);
    }

    if (ControlLock) {
        //g_print("Event: Control Pressed\n");
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Control_L), True, 0);
        XFlush(display);
    }

    if (AltLock) {
        //g_print("Event: Alt Pressed\n");
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Alt_L), True, 0);
        XFlush(display);
    }

    //g_print("Event: Key Pressed\n");

    XTestFakeKeyEvent(display, modcode, True, 0);
    XFlush(display);
}
// check phys
void emulateKeyRelease(KeySym keySym)
{
    KeyCode modcode = 0; //init value
    isKeyPressed = FALSE;

    if (specialKey(keySym, EVENT_RELEASE)) {
        return;
    }

    if (keySym == NoSymbol) {
        return;
    }

    modcode = XKeysymToKeycode(display, keySym);

    //g_print("Event: Key Released\n");
    XTestFakeKeyEvent(display, modcode, False, 0);
    XFlush(display);

    if (ControlLock) {
        //g_print("Event: Control Pressed\n");
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Control_L), False, 0);
        XFlush(display);
//        ControlLock = FALSE;
    }

    if (ShiftLock) {
        //g_print("Event: Shift Released\n");
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), False, 0);
        XFlush(display);
    }

    if (AltLock) {
        //g_print("Event: Shift Released\n");
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Alt_L), False, 0);
        XFlush(display);
    }

}


//Simpler version but no shift alt ctrl lock and special keys
/*
void emulateKeyPress(KeySym keySym)
{
    KeyCode modcode = 0; //init value
    isKeyPressed = TRUE;

    if (keySym == NoSymbol) {
        return;
    }

    modcode = XKeysymToKeycode(display, keySym);

    XTestFakeKeyEvent(display, modcode, True, 0);
    XFlush(display);
}
// check phys
void emulateKeyRelease(KeySym keySym)
{
    KeyCode modcode = 0; //init value
    isKeyPressed = FALSE;

    if (keySym == NoSymbol) {
        return;
    }

    modcode = XKeysymToKeycode(display, keySym);

    //g_print("Event: Key Released\n");
    XTestFakeKeyEvent(display, modcode, False, 0);
    XFlush(display);

}
*/

void shutdown(void)
{
    // Would like something to change brightness to 0
    // Maybe it has something to do with system not blacking out screen anymore...
    system ("clear");
    system ("echo Shuting down now...");
    //system ("sudo shutdown -h now");
}
//works but gameLayout not yet
KeySym getKeySymbol(int row, int col)
{
    if (mode == MODE_LETTER) {
        return letterLayout[row][col];
    } else if (mode == MODE_SYMBOL) {
        return symbolLayout[row][col];
    }/* else if (mode == MODE_GAME) {
        return gameLayout[row][col];
    }*/

    return letterLayout[row][col];
}

// does wiringPiSetup
// + OpenXDisplay
// + HIGH on backlight = soft pwm on the backlight pin
// + mode inp on all colPins[i]
//
//works
//figure out what about backlight+data+clock+latch pins
void setup(void)
{
    int i;

    if (wiringPiSetup() == -1) {
        g_print("wiringPiSetup error\n");
        exit(1);
    }

    if ((display = XOpenDisplay(NULL)) == NULL) {
        g_print("XOpenDisplay Initialization Failure\n");
        exit(2);
    }

/*
//sr595Setup (100, 8, DATA_PIN, CLOCK_PIN, LATCH_PIN) ;
//     struct wiringPiNodeStruct *node ;
//
//     node = wiringPiNewNode (pinBase, numPins) ;
//
//     node->data0           = dataPin ;
//     node->data1           = clockPin ;
//     node->data2           = latchPin ;
//     node->data3           = 0 ;		// Output register
//     node->digitalWrite    = myDigitalWrite ;
//
//   // Initialise the underlying hardware
//
//     digitalWrite (dataPin,  LOW) ;
//     digitalWrite (clockPin, LOW) ;
//     digitalWrite (latchPin, HIGH) ;
//
//     pinMode (dataPin,  OUTPUT) ;
//     pinMode (clockPin, OUTPUT) ;
//     pinMode (latchPin, OUTPUT) ;
*///sr595Setup

    //softPwmCreate (BACKLIGHT_PIN, MAX_BRIGHTNESS, MAX_BRIGHTNESS);
    colCount = getColCount();
    rowCount = getRowCount();

    for (i = 0; i < colCount; i++) {   // Set column pins for input, with pullup.
        pinMode(colPins[i], INPUT);
        pullUpDnControl (colPins[i], PUD_DOWN); //???idfk what that does i hope it-s good
    }

    for (i = 0; i < rowCount; i++) {   // Set column pins for input, with pullup.
        pinMode(rowPins[i], OUTPUT);
        pullUpDnControl (rowPins[i], PUD_UP); //???idfk what that does i hope it-s good
    }
}

//got the gist of it
/*
gboolean loop(gpointer data)
{
    int row, col;
    gboolean keyFound = FALSE;
    KeySym ks;

    if (isKeyPressed) {
        return FALSE;
    }


    // loops through all the pins
    // if any is HIGH -> emulates Key Down -> until LOW
    // if F11 -> Cycle Mode
    for (row = 0; row < 8; row++) {
        setBit(row);
        for (col = 0; col < colCount; col++) {
            if (digitalRead(colPins[col]) == HIGH) {
                ks = getKeySymbol(row, col);
                emulateKeyPress(ks);
                while (keyFound == FALSE && digitalRead(colPins[col]) == HIGH) { //exits if pin gets low or if ks=F11 -> change mode
                    if (ks == XK_F11 && digitalRead(ONKEY_PIN) == LOW) {
                        g_print("Mode Change Key Combo Detected\n");
                        cycleModes();
                        keyFound = TRUE;
                    }
                };
                emulateKeyRelease(ks);
                keyFound = TRUE;                            // Force exit of both for loops.
            }

            if (keyFound) break;
        }
        if (keyFound) {
            delay(BOUNCE_DELAY);
            break;
        }
    }

    // if not PowerButton and not a single pin is HIGH
    // switch(layout):
    // ti30: while loop until ON or F11 	{pin 0,0 pressed wtf??? does not make sense
    // 2nd : shutdown + while loop forever 	(so as not play entire loop again)
    // dflt: while loop until ON or F11		{pin 0,0

    if (digitalRead(ONKEY_PIN) == LOW) {
        if (!keyFound) {
            if (mode == MODE_TI30) {
                // Emulate F12 and Check For Mode Change Combo
                emulateKeyPress(XK_F12);
                while (keyFound == FALSE && digitalRead(ONKEY_PIN) == LOW) {
                    setBit(0);
                    if (digitalRead(colPins[0]) == HIGH) {
                        g_print("Mode Change Key Combo Detected\n");
                        cycleModes();
                        keyFound = TRUE;
                    }
                };
                emulateKeyRelease(XK_F12);
                delay(BOUNCE_DELAY);
            } else if (mode == MODE_SECOND) {
                emulateKeyPress(NoSymbol);
                // Power Down
                g_print("Power Down\n");
                shutdown();
                // So that we don't keep looping
                while (digitalRead(ONKEY_PIN) == LOW);
                emulateKeyRelease(NoSymbol);
            } else {
                // Check For Mode Change Combo
                emulateKeyPress(NoSymbol);
                while (keyFound == FALSE && digitalRead(ONKEY_PIN) == LOW) {
                    setBit(0);
                    if (digitalRead(colPins[0]) == HIGH) {
                        g_print("Mode Change Key Combo Detected\n");
                        cycleModes();
                        keyFound = TRUE;
                    }
                };
                emulateKeyRelease(NoSymbol);
                delay(BOUNCE_DELAY);
            }
        }
    }

    return TRUE;
}
*/

/*//commented out in master too useless then I guess idk
static void show_about( GtkWidget *widget, gpointer data )
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,
                                             "TI-30 Keypad Driver\nBy Melissa LeBlanc-Williams");

    gtk_widget_show_all (dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
*/

//main
//figure out what all the g_stuff does
int main(int argc, char *argv[])
{
    // executable = g_string_new("");
    // g_string_append(executable, argv[0]);
    //
    // gtk_init (&argc, &argv);
    //
    // if (geteuid() != 0) {
      //     fprintf (stderr, "You need to be root to run this program. (sudo?)\n");
      //     exit(0);
    // }
    //
    // tray = gtk_status_icon_new_from_file(getImagePath(getModeIconImage()));
    // gtk_status_icon_set_tooltip_text(tray, "Normal");
    //
    // setup();
    // gint func_ref = g_timeout_add (SCAN_DELAY, loop, FALSE);
    //
    // gtk_main();
    //
    // g_source_remove (func_ref);
    setup();
    fprintf(stderr, "Setup done, input loop started! \n");

    //for later, let-s assume pin 24 and 25 work properly

    while (TRUE){
      int row, col;
      gboolean keyFound = FALSE;
      KeySym ks;

      for (row = 0; row < rowCount; row++) {
          setBit(row);
          for (col = 0; col < colCount; col++) {
              if (digitalRead(colPins[col]) == HIGH) {

                  ks = getKeySymbol(row, col);

		  fprintf(stderr, "[%d,%d] ", row, col);
//                  emulateKeyPress(ks);

		  while (digitalRead(colPins[col]) == HIGH && keyFound==FALSE){
		  	if (ks == XK_F11) {
//			     cycleModes(); keyFound = TRUE;
//             		     fprintf(stderr, "\n Mode Cycle Detected \n"); 
			}
		  };

//                  fprintf(stderr, "Key RELEASE \n");
//                  emulateKeyRelease(ks);

		  keyFound = TRUE;                            // Force exit of both for loops.
              }

              if (keyFound) break;
          }
          if (keyFound) {delay(BOUNCE_DELAY); break; }
      }

      delay(SCAN_DELAY);
    }

    return 0;
}
// ####### FORGOTTEN ABYSS
/*
    int row = 3; int col = 0;
    KeySym ks = getKeySymbol(row, col);

    fprintf(stderr, "Key PRESS (%d,%d)\n", row, col);
    emulateKeyPress(ks);
    delay(10);
    emulateKeyRelease(ks);

    emulateKeyPress(XK_Shift_L);
    emulateKeyPress(XK_s);
    emulateKeyRelease(XK_s);
    emulateKeyPress(XK_s);
    emulateKeyRelease(XK_s);
    emulateKeyPress(XK_s);
    emulateKeyRelease(XK_s);
    delay(2000);
    emulateKeyRelease(XK_s);
    emulateKeyRelease(XK_Shift_L);

    g_print("\n");
    delay(10);

    return 0;

*/
