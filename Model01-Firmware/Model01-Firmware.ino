// Arley's M01 firmware
#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "1.0"
#endif

// includes
#include "Kaleidoscope.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-NumPad.h"
#include "LED-Off.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-Steno.h"
#include <Kaleidoscope-LED-ActiveModColor.h>
//#include <kaleidoscope/hid.h> // not sure what this is or if it's broken

// index of macros
enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
  MACRO_HYPER,
  MACRO_MEH
};


// keymaps
enum { COLEMAK, KAMELOC, QWERTY, STENO, FNLEFT, FNRIGHT, NUMPAD };

// *INDENT-OFF*
const Key keymaps[][ROWS][COLS] PROGMEM = {

  [COLEMAK] = KEYMAP_STACKED
  (M(MACRO_MEH),        Key_1,    Key_2,    Key_3,    Key_4,    Key_5,    M(MACRO_HYPER),
  Key_Backtick,         Key_Q,    Key_W,    Key_F,    Key_P,    Key_G,    Key_Tab,
  Key_mouseScrollDn,    Key_A,    Key_R,    Key_S,    Key_T,    Key_D,
  Key_mouseScrollUp,    Key_Z,    Key_X,    Key_C,    Key_V,    Key_B,    Key_Escape,
  ShiftToLayer(KAMELOC),    Key_Backspace,    Key_LeftGui,    OSM(LeftShift),
  ShiftToLayer(FNLEFT),

  M(MACRO_MEH),      Key_6,    Key_7,    Key_8,        Key_9,         Key_0,            M(MACRO_HYPER),
  Key_RightShift,    Key_J,    Key_L,    Key_U,        Key_Y,         Key_Semicolon,    Key_Equals,
                     Key_H,    Key_N,    Key_E,        Key_I,         Key_O,            Key_Quote,
  Key_Enter,         Key_K,    Key_M,    Key_Comma,    Key_Period,    Key_Slash,        Key_Minus,
  OSM(LeftControl),    Key_LeftAlt,    Key_Spacebar,    ShiftToLayer(KAMELOC),
  ShiftToLayer(FNRIGHT)),



  [KAMELOC] = KEYMAP_STACKED
  (M(MACRO_HYPER),    Key_0,            Key_9,         Key_8,        Key_7,    Key_6,    M(MACRO_MEH),
  Key_Equals,         Key_Semicolon,    Key_Y,         Key_U,        Key_L,    Key_J,    Key_RightShift,
  Key_Quote,          Key_O,            Key_I,         Key_E,        Key_N,    Key_H,
  Key_Minus,          Key_Slash,        Key_Period,    Key_Comma,    Key_M,    Key_K,    Key_Enter,
  ___,    Key_Spacebar,    Key_LeftAlt,    OSM(LeftControl),
  ShiftToLayer(FNRIGHT),

  M(MACRO_HYPER),    Key_5,    Key_4,    Key_3,    Key_2,    Key_1,    M(MACRO_MEH),
  Key_Tab,           Key_G,    Key_P,    Key_F,    Key_W,    Key_Q,    Key_Backtick,
                     Key_D,    Key_T,    Key_S,    Key_R,    Key_A,    Key_PageUp,
  Key_Escape,        Key_B,    Key_V,    Key_C,    Key_X,    Key_Z,    Key_PageDown,
  OSM(LeftShift),    OSM(LeftGui),    Key_Backspace,    ___,
  ShiftToLayer(FNLEFT)),


  
  [QWERTY] = KEYMAP_STACKED
  (___,            Key_1,    Key_2,    Key_3,    Key_4,    Key_5,    Key_LEDEffectNext,
  Key_Backtick,    Key_Q,    Key_W,    Key_E,    Key_R,    Key_T,    Key_Tab,
  Key_PageUp,      Key_A,    Key_S,    Key_D,    Key_F,    Key_G,
  Key_PageDown,    Key_Z,    Key_X,    Key_C,    Key_V,    Key_B,    Key_Escape,
  Key_LeftControl, Key_Backspace, OSM(LeftShift), Key_LeftAlt,
  ShiftToLayer(FNLEFT),

  Key_Home,     Key_6,    Key_7,    Key_8,        Key_9,         Key_0,            LockLayer(NUMPAD),
  Key_End,      Key_Y,    Key_U,    Key_I,        Key_O,         Key_P,            Key_Equals,
                Key_H,    Key_J,    Key_K,        Key_L,         Key_Semicolon,    Key_Quote,
  Key_Enter,    Key_N,    Key_M,    Key_Comma,    Key_Period,    Key_Slash,        Key_Minus,
  Key_LeftGui, OSM(RightShift), Key_Spacebar, Key_RightControl,
  ShiftToLayer(FNRIGHT)),



  [STENO] = KEYMAP_STACKED
  (XXX,    XXX,   XXX,   XXX,   XXX,   XXX,   S(N6),
  XXX,    S(N1), S(N2), S(N3), S(N4), S(N5), S(ST1),
  S(FN),  S(S1), S(TL), S(PL), S(HL), S(ST1),
  S(PWR), S(S2), S(KL), S(WL), S(RL), S(ST2), S(ST2),
  S(RE1), XXX, S(A), S(O),
  ___,

  S(N7),  XXX,    XXX,   XXX,   XXX,   XXX,   XXX,
  S(ST3), S(N8),  S(N9), S(NA), S(NB), S(NC), XXX,
  S(ST3), S(FR),  S(PR), S(LR), S(TR), S(DR),
  S(ST4), S(ST4), S(RR), S(BR), S(GR), S(SR), S(ZR),
  S(E), S(U), XXX, S(RE2),
  ___),



  [FNLEFT] =  KEYMAP_STACKED
  (___,           Key_F1,        Key_F2,         Key_F3,        Key_F4,           Key_F5,              Key_LEDEffectNext,
  Key_F11,        Key_F12,       Key_mouseUp,    ___,           Key_mouseBtnR,    Key_mouseWarpEnd,    Key_mouseWarpNE,
  Key_PageUp,     Key_mouseL,    Key_mouseDn,    Key_mouseR,    Key_mouseBtnL,    Key_mouseWarpNW,
  Key_PageDown,   ___,           ___,            ___,           Key_mouseBtnM,    Key_mouseWarpSW,     Key_mouseWarpSE,
  (LGUI(Key_LeftAlt)),    Key_Delete,    ___,    ___,
  ___,

  M(MACRO_ANY),               Key_F6,           Key_F7,                  Key_F8,                   Key_F9,             Key_F10,             ___,
  Consumer_PlaySlashPause,    ___,              Key_LeftCurlyBracket,    Key_RightCurlyBracket,    Key_LeftBracket,    Key_RightBracket,    ___,
                              Key_LeftArrow,    Key_DownArrow,           Key_UpArrow,              Key_RightArrow,     ___,                 ___,
  LGUI(LCTRL(Key_Space)),     Key_Mute,           ___,              Key_F19,                 Key_F18,                  Key_Backslash,      Key_Pipe,
  ___,    ___,    Key_Enter,    ___,
  ___),



  [FNRIGHT] =  KEYMAP_STACKED
  (___,     LockLayer(QWERTY),    LockLayer(STENO),    ___, ___, ___, ___,
  ___,      ___,                  Key_UpArrow,           ___, ___, ___, ___,
  ___,      Key_LeftArrow,        Key_DownArrow,         Key_RightArrow, ___, ___,
  ___, ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___,
  ___,

  ___,                      (LGUI(LSHIFT(LCTRL(Key_4)))),  ___,            ___,                       ___,                       ___,                         LockLayer(NUMPAD),
  Consumer_PlaySlashPause,  ___,                           ___,            ___,                       ___,                       ___,                         ___,
                            Key_LeftArrow,                 Key_DownArrow,  Key_UpArrow,               Key_RightArrow,            ___,                         ___,
  ___,                      Key_Mute,                      ___,            Consumer_VolumeIncrement,  Consumer_VolumeDecrement,  Consumer_ScanPreviousTrack,  Consumer_ScanNextTrack,
  ___,    ___,    Key_Enter,    (LGUI(Key_LeftAlt)),
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

  case MACRO_HYPER:
    OneShotHyper(keyState);
    break;

  case MACRO_MEH:
    OneShotMeh(keyState);
    break;

  }
  return MACRO_NONE;
}

static kaleidoscope::LEDSolidColor kristiblue(21, 166, 58);
static kaleidoscope::LEDSolidColor kristigreen(10, 6, 207);
static kaleidoscope::LEDSolidColor arleyblue(46, 114, 185);
static kaleidoscope::LEDSolidColor arleygreen(95, 150, 19);

void setup() {
  Serial.begin(9600);

  // The plugin call order can be important. eg, LED effects are added in the order listed
  Kaleidoscope.use(
    &GeminiPR,
    &OneShot, &EscapeOneShot, &ActiveModColorEffect,
    &BootGreetingEffect,
    &LEDControl,
    &LEDOff,
    &kristigreen,
    &arleyblue,
    &kristiblue,
    &arleygreen,
    &LEDRainbowEffect,
    &LEDRainbowWaveEffect,
    &LEDChaseEffect,
    &LEDBreatheEffect,
    &StalkerEffect,
    &NumPad,
    &Macros,
    &MouseKeys
  );
  
  Kaleidoscope.setup();

  NumPad.numPadLayer = NUMPAD;
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // For details on other options, see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // Mousekeys - defaults listed after options https://github.com/keyboardio/Kaleidoscope-MouseKeys
  MouseKeys.speed = 48; // 1
  MouseKeys.accelDelay = 150; // 50
  MouseKeys.wheelDelay = 60; // 50

  // Oneshot
  ActiveModColorEffect.highlight_color = CRGB(0xff, 0xff, 0xff);

  LEDOff.activate();
}

// run the firmware
void loop() {
  Kaleidoscope.loop();
}

