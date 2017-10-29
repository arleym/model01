// Arley's M01 firmware
#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "1.0"
#endif

// includes
#include "Kaleidoscope.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Numlock.h"
#include "LED-Off.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
// Support for One Shot modifiers
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <kaleidoscope/hid.h>


// index of macros
enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
  MACRO_TOGGLER,
  MACRO_HYPER,
  MACRO_MEH
};


// keymaps
enum { COLEMAK, QWERTY, FNLEFT, FNRIGHT, NUMPAD };

// *INDENT-OFF*
const Key keymaps[][ROWS][COLS] PROGMEM = {

  [COLEMAK] = KEYMAP_STACKED
  (M(MACRO_TOGGLER),    Key_1,    Key_2,    Key_3,    Key_4,    Key_5,    M(MACRO_HYPER),
  Key_Backtick,         Key_Q,    Key_W,    Key_F,    Key_P,    Key_G,    Key_Tab,
  Key_PageUp,           Key_A,    Key_R,    Key_S,    Key_T,    Key_D,
  Key_PageDown,         Key_Z,    Key_X,    Key_C,    Key_V,    Key_B,    Key_Escape,
  OSM(LeftControl),    Key_Backspace,    OSM(LeftGui),    OSM(LeftShift),
  //  Key_LeftControl,    Key_Backspace,    Key_LeftGui,    Key_LeftShift,
  ShiftToLayer(FNLEFT),

  M(MACRO_MEH),      Key_6,    Key_7,    Key_8,        Key_9,         Key_0,            Key_KeypadNumLock,
  Key_Enter,         Key_J,    Key_L,    Key_U,        Key_Y,         Key_Semicolon,    Key_Equals,
                     Key_H,    Key_N,    Key_E,        Key_I,         Key_O,            Key_Quote,
  M(MACRO_HYPER),    Key_K,    Key_M,    Key_Comma,    Key_Period,    Key_Slash,        Key_Minus,
  OSM(RightShift),    Key_LeftAlt,    Key_Spacebar,    OSM(RightControl),
  // Key_RightShift,    OSM(LeftAlt),    Key_Spacebar,    OSM(RightControl),
  ShiftToLayer(FNRIGHT)),


  [QWERTY] = KEYMAP_STACKED
  (___,    ___,      ___,      ___,      ___,      ___,      ___,
  ___,     Key_Q,    Key_W,    Key_E,    Key_R,    Key_T,    ___,
  ___,     Key_A,    Key_S,    Key_D,    Key_F,    Key_G,
  ___,     Key_Z,    Key_X,    Key_C,    Key_V,    Key_B,    ___,
  ___,     ___,    ___,    ___,
  ___,

  ___,    ___,      ___,      ___,      ___,      ___,              ___,
  ___,    Key_Y,    Key_U,    Key_I,    Key_O,    Key_P,            ___,
          Key_H,    Key_J,    Key_K,    Key_L,    Key_Semicolon,    ___,
  ___,    Key_N,    Key_M,    ___,      ___,      ___,              ___,
  ___,    ___,    ___,    ___,
  ___),


  [FNLEFT] =  KEYMAP_STACKED
  (LGUI(LCTRL(Key_Space)),    Key_F1,        Key_F2,         Key_F3,        Key_F4,           Key_F5,              Key_LEDEffectNext,
  Key_Enter,                  ___,           Key_mouseUp,    ___,           Key_mouseBtnR,    Key_mouseWarpEnd,    Key_mouseWarpNE,
  Key_mouseScrollDn,          Key_mouseL,    Key_mouseDn,    Key_mouseR,    Key_mouseBtnL,    Key_mouseWarpNW,
  Key_mouseScrollUp,          ___,           ___,            ___,           Key_mouseBtnM,    Key_mouseWarpSW,     Key_mouseWarpSE,
  ___,    Key_Delete,    ___,    ___,
  ___,

  M(MACRO_ANY),               Key_F6,           Key_F7,                  Key_F8,                   Key_F9,             Key_F10,             Key_F11,
  Consumer_PlaySlashPause,    ___,              Key_LeftCurlyBracket,    Key_RightCurlyBracket,    Key_LeftBracket,    Key_RightBracket,    Key_F12,
                              Key_LeftArrow,    Key_DownArrow,           Key_UpArrow,              Key_RightArrow,     ___,                 ___,
  ___,    Key_Mute,           Key_F18,          Key_F19,                 ___,                      Key_Backslash,      Key_Pipe,
  ___,    ___,    Key_Enter,    ___,
  ___),


  [FNRIGHT] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
  ___, ___, Key_UpArrow, ___, ___, ___, ___,
  ___, Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___, ___,
  ___, ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___,
  ___,

  ___, ___, ___, ___, ___, ___, ___,
  Consumer_PlaySlashPause, ___, ___, ___, ___, ___, ___,
                           ___, ___, ___, ___, ___, ___,
  ___, Key_Mute,    Consumer_VolumeDecrement,    Consumer_VolumeIncrement,    ___,    Consumer_ScanPreviousTrack,    Consumer_ScanNextTrack,
  ___,    ___,    Key_Enter,    ___,
  ___),



  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, Key_UpArrow, ___, ___, ___, ___,
   ___, Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___)
};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

// example of printing a message
static void printMsg(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Arley McBlain - arley@mcblain.ca"));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

// fn + any - randomizer and password generator
static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


// Toggle between Colemak and Qwerty
static void toggleFactoryLayout(uint8_t keyState) {
  if (!keyToggledOn(keyState))
    return;

  if (Layer.isOn(COLEMAK)) {
    Layer.move(QWERTY);
    LEDControl.set_mode(2);
  } else {
    Layer.move(COLEMAK);
    LEDControl.set_mode(1);
  }
}

// one shot modifier on hyper
static void OneShotHyper(uint8_t keyState) {
  handleKeyswitchEvent(OSM(LeftShift), UNKNOWN_KEYSWITCH_LOCATION, keyState);
  handleKeyswitchEvent(OSM(LeftControl), UNKNOWN_KEYSWITCH_LOCATION, keyState);
  handleKeyswitchEvent(OSM(LeftAlt), UNKNOWN_KEYSWITCH_LOCATION, keyState);
  handleKeyswitchEvent(OSM(LeftGui), UNKNOWN_KEYSWITCH_LOCATION, keyState);
}

// one shot modifier on meh
static void OneShotMeh(uint8_t keyState) {
  handleKeyswitchEvent(OSM(LeftControl), UNKNOWN_KEYSWITCH_LOCATION, keyState);
  handleKeyswitchEvent(OSM(LeftAlt), UNKNOWN_KEYSWITCH_LOCATION, keyState);
  handleKeyswitchEvent(OSM(LeftGui), UNKNOWN_KEYSWITCH_LOCATION, keyState);
}

// macro switcher
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    printMsg(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;

  case MACRO_TOGGLER:
    toggleFactoryLayout(keyState);
    break;

  case MACRO_HYPER:
    OneShotHyper(keyState);
    break;

  case MACRO_MEH:
    OneShotMeh(keyState);
    break;

  }
  return MACRO_NONE;
}


// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less
// Arley ones are untested

static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);
static kaleidoscope::LEDSolidColor arleyblue(46, 114, 185);
static kaleidoscope::LEDSolidColor arleygreen(95, 150, 19);


void setup() {
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. eg, LED effects are added in the order listed
  Kaleidoscope.use(
    // One Shot modifier
    &OneShot,
    &EscapeOneShot,
    &ActiveModColorEffect,

    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    &BootGreetingEffect,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // first color, called in layout swapper
    &arleyblue,
    &arleygreen,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,
    //&arleyrgreen,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numlock plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumLock,

    // The macros plugin adds support for macros
    &Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys
  );

  // While we hope to improve this in the future, the NumLock plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumLock.numPadLayer = NUMPAD;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // Mousekeys - defaults listed after options
  // https://github.com/keyboardio/Kaleidoscope-MouseKeys
  MouseKeys.speed = 50; // 1
  MouseKeys.speedDelay = 0; // 0
  MouseKeys.accelSpeed = 1; // 1
  MouseKeys.accelDelay = 300; // 50
  MouseKeys.wheelSpeed = 1; // 1
  MouseKeys.wheelDelay = 60; // 50

  // Oneshot
  ActiveModColorEffect.highlight_color = CRGB(0xff, 0xff, 0xff);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  // LEDOff.activate();

}

// run the firmware
void loop() {
  Kaleidoscope.loop();
}

