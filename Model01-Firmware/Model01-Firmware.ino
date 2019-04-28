// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details
// Arley's M01 firmware 1.94

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-Steno.h"
#include <Kaleidoscope-LED-ActiveModColor.h>

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_HYPER,
       MACRO_MEH
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { QWERTY, YTREWQ, COLEMAK, KAMELOC, STENO, FNLEFT, FNRIGHT, NUMPAD };

/**
  * To change your keyboard's layout from QWERTY to DVORAK or COLEMAK, comment out the line
  *
  * #define PRIMARY_KEYMAP_QWERTY
  *
  * by changing it to
  *
  * // #define PRIMARY_KEYMAP_QWERTY
  *
  * Then uncomment the line corresponding to the layout you want to use.
  *
  */

//#define PRIMARY_KEYMAP_QWERTY
// #define PRIMARY_KEYMAP_COLEMAK
// #define PRIMARY_KEYMAP_DVORAK
//#define PRIMARY_KEYMAP_CUSTOM



/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(

  // Arley's custom layout
  [QWERTY] = KEYMAP_STACKED
  (M(MACRO_MEH),        Key_1,    Key_2,    Key_3,    Key_4,    Key_5,    M(MACRO_HYPER),
  Key_Backtick,         Key_Q,    Key_W,    Key_E,    Key_R,    Key_T,    Key_Tab,
  Key_mouseScrollDn,    Key_A,    Key_S,    Key_D,    Key_F,    Key_G,
  Key_mouseScrollUp,    Key_Z,    Key_X,    Key_C,    Key_V,    Key_B,    Key_Escape,
  ShiftToLayer(YTREWQ),     Key_Backspace,    OSM(LeftGui),    OSM(LeftShift),
  ShiftToLayer(FNLEFT),

  M(MACRO_MEH),      Key_6,    Key_7,    Key_8,        Key_9,         Key_0,            M(MACRO_HYPER),
  Key_RightShift,    Key_Y,    Key_U,    Key_I,        Key_O,         Key_P,            Key_Equals,
                     Key_H,    Key_J,    Key_K,        Key_L,         Key_Semicolon,    Key_Quote,
  Key_Enter,         Key_N,    Key_M,    Key_Comma,    Key_Period,    Key_Slash,        Key_Minus,
  OSM(LeftControl),    Key_LeftAlt,    Key_Spacebar,    ShiftToLayer(YTREWQ),
  ShiftToLayer(FNRIGHT)),

[YTREWQ] = KEYMAP_STACKED
  (M(MACRO_HYPER),    Key_0,            Key_9,         Key_8,        Key_7,    Key_6,    M(MACRO_MEH),
  Key_Equals,         Key_P,            Key_O,         Key_I,        Key_U,    Key_Y,    Key_RightShift,
  Key_Quote,          Key_Semicolon,    Key_L,         Key_K,        Key_J,    Key_H,
  Key_Minus,          Key_Slash,        Key_Period,    Key_Comma,    Key_M,    Key_N,    Key_Enter,
  ___,    Key_Spacebar,    Key_LeftAlt,    OSM(LeftControl),
  ShiftToLayer(FNRIGHT),

  M(MACRO_HYPER),    Key_5,    Key_4,    Key_3,    Key_2,    Key_1,    M(MACRO_MEH),
  Key_Tab,           Key_T,    Key_R,    Key_E,    Key_W,    Key_Q,    Key_Backtick,
                     Key_G,    Key_F,    Key_D,    Key_S,    Key_A,    Key_PageUp,
  Key_Escape,        Key_B,    Key_V,    Key_C,    Key_X,    Key_Z,    Key_PageDown,
  OSM(LeftShift),    Key_LeftGui,    Key_Backspace,    ___,
  ShiftToLayer(FNLEFT)),



  [COLEMAK] = KEYMAP_STACKED
  (M(MACRO_MEH),        Key_1,    Key_2,    Key_3,    Key_4,    Key_5,    M(MACRO_HYPER),
  Key_Backtick,         Key_Q,    Key_W,    Key_F,    Key_P,    Key_G,    Key_Tab,
  Key_mouseScrollDn,    Key_A,    Key_R,    Key_S,    Key_T,    Key_D,
  Key_mouseScrollUp,    Key_Z,    Key_X,    Key_C,    Key_V,    Key_B,    Key_Escape,
  ShiftToLayer(KAMELOC),    Key_Backspace,    OSM(LeftGui),    OSM(LeftShift),
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
  OSM(LeftShift),    Key_LeftGui,    Key_Backspace,    ___,
  ShiftToLayer(FNLEFT)),



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
  (Key_Enter,     Key_F1,        Key_F2,         Key_F3,        Key_F4,                              Key_F5,              Key_LEDEffectNext,
  Key_F11,        Key_F12,       Key_mouseUp,    ___,           Key_mouseBtnR,                       Key_mouseWarpEnd,    Key_mouseWarpNE,
  Key_PageUp,     Key_mouseL,    Key_mouseDn,    Key_mouseR,    Key_mouseBtnL,                       Key_mouseWarpNW,
  Key_PageDown,   ___,           ___,            ___,           LSHIFT(LALT(LCTRL(LGUI(Key_V)))),    Key_mouseWarpSW,     Key_mouseWarpSE, // Key_mouseBtnM
  (LGUI(Key_LeftAlt)),    Key_Delete,    ___,    ___,
  ___,

  M(MACRO_ANY),               Key_F6,           Key_F7,                  Key_F8,                   Key_F9,             Key_F10,             ___,
  Consumer_PlaySlashPause,    ___,              Key_LeftCurlyBracket,    Key_RightCurlyBracket,    Key_LeftBracket,    Key_RightBracket,    ___,
                              Key_LeftArrow,    Key_DownArrow,           Key_UpArrow,              Key_RightArrow,     ___,                 ___,
  LGUI(LCTRL(Key_Space)),     Key_Mute,           ___,              Key_F19,                 Key_F18,                  Key_Backslash,      Key_Pipe,
  ___,    ___,    ___,    ___,
  ___),



  [FNRIGHT] =  KEYMAP_STACKED
  (___,     LockLayer(COLEMAK),    LockLayer(STENO),    ___,      ___,      ___,      ___,
  ___, ___, LALT(LCTRL(LGUI(Key_W))), ___, ___, ___,                                                       LSHIFT(Key_P),
  ___, Key_1,                 Key_2,               Key_3,    Key_4,    Key_5,
  ___, Key_6,                 Key_7,               Key_8,    Key_9,    Key_0,    Key_Minus,
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
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Arley McBlain - arley@mcblain.ca"));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
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



/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
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



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.

static kaleidoscope::LEDSolidColor arleyblue(46, 114, 185);
static kaleidoscope::LEDSolidColor kristiblue(21, 166, 58);
static kaleidoscope::LEDSolidColor kristigreen(10, 6, 207);

static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE
};

/** A tiny wrapper, to be used by MagicCombo.
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
                 });

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  TestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  arleyblue,
  kristiblue,
  kristigreen,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed, solidOrange, solidYellow, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  ActiveModColorEffect,
  OneShot,
  EscapeOneShot
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // Mousekeys - defaults listed after options https://github.com/keyboardio/Kaleidoscope-MouseKeys
  MouseKeys.speed = 48; // 1
  MouseKeys.accelDelay = 150; // 50
  MouseKeys.wheelDelay = 60; // 50

  // Oneshot
  ActiveModColorEffect.highlight_color = CRGB(0xff, 0xff, 0xff);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command.
  EEPROMKeymap.setup(5, EEPROMKeymap.Mode::EXTEND);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
