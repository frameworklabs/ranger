#ifndef BLECH_RANGER_H_INCLUDED
#define BLECH_RANGER_H_INCLUDED

/*
** This is generated code - do not touch!
*/

/*
** blech types
*/

#include "blech.h"

/*
** all user defined types
*/

struct blc_ranger_Settings {
    blc_bool measureFromBack;
    blc_nat8 brightness;
    blc_bool bleEnabled;
    blc_nat8 measureUnit;
};
struct blc_ranger_BatteryInfo {
    blc_float32 voltage;
    blc_nat8 stateOfCharge;
    blc_bool isCharging;
};
struct blc_ranger_ButtonStates {
    blc_bool aPressed;
    blc_bool aReleased;
    blc_bool bPressed;
    blc_bool bReleased;
};
struct blc_ranger_DialogRequest {
    blc_nat8 kind;
    blc_nat8 info;
};

/*
** activity contexts
*/

struct blc_ranger_Delay {
    blc_nat16 blc_Delay_i;
    blc_pc_t pc_1;
};
struct blc_ranger_DelayOrDidWakeup {
    blc_pc_t pc_2;
    struct blc_ranger_Delay pc_2_blc_ranger_Delay;
};
struct blc_ranger_SettingsPersister {
    struct blc_ranger_Settings blc_SettingsPersister_prevSettings;
    blc_pc_t pc_6;
};
struct blc_ranger_PressRecognizer {
    blc_bool blc_PressRecognizer_wasReleased;
    blc_bool blc_PressRecognizer_wasDouble;
    blc_pc_t pc_8;
    blc_pc_t pc_9;
    blc_pc_t pc_10;
    struct blc_ranger_Delay pc_9_blc_ranger_Delay;
};
struct blc_ranger_DimDown {
    blc_pc_t pc_12;
    struct blc_ranger_Delay pc_12_blc_ranger_Delay;
};
struct blc_ranger_Dimmer {
    blc_bool blc_Dimmer_19_20_0_abortFinished;
    blc_pc_t pc_13;
    blc_pc_t pc_14;
    blc_pc_t pc_15;
    struct blc_ranger_DimDown pc_13_blc_ranger_DimDown;
    struct blc_ranger_Delay pc_14_blc_ranger_Delay;
};
struct blc_ranger_BrightnessController {
    blc_nat8 blc_BrightnessController_prevLevel;
    blc_pc_t pc_16;
};
struct blc_ranger_RotationController {
    blc_nat8 blc_RotationController_prevOrientation;
    blc_float32 blc_RotationController_34_rot;
    blc_pc_t pc_17;
    struct blc_ranger_DelayOrDidWakeup pc_17_blc_ranger_DelayOrDidWakeup;
};
struct blc_ranger_DialogManager {
    struct blc_ranger_DialogRequest blc_DialogManager_nexts[3];
    blc_int8 blc_DialogManager_delIdx;
    blc_int8 blc_DialogManager_48_49_idx;
    struct blc_ranger_DialogRequest blc_DialogManager_48_49_curr;
    blc_bool blc_DialogManager_48_49_51_1_abortFinished;
    blc_pc_t pc_20;
    blc_pc_t pc_21;
    blc_pc_t pc_22;
    blc_pc_t pc_23;
    blc_pc_t pc_24;
    struct blc_ranger_Delay pc_23_blc_ranger_Delay;
    struct blc_ranger_DimDown pc_23_blc_ranger_DimDown;
};
struct blc_ranger_BatteryDialog {
    blc_bool blc_BatteryDialog_seenBelow20;
    blc_bool blc_BatteryDialog_seenBelow10;
    blc_pc_t pc_25;
};
struct blc_ranger_BLEDialog {
    blc_bool blc_BLEDialog_prevBLEEnabled;
    struct blc_ranger_DialogRequest blc_BLEDialog_enabledRequest;
    blc_bool blc_BLEDialog_prevBLEConnected;
    struct blc_ranger_DialogRequest blc_BLEDialog_connectedRequest;
    blc_pc_t pc_26;
    blc_pc_t pc_27;
    blc_pc_t pc_28;
    blc_pc_t pc_29;
};
struct blc_ranger_USBDialog {
    blc_bool blc_USBDialog_prevIsCharging;
    blc_pc_t pc_30;
};
struct blc_ranger_WelcomeScreen {
    blc_pc_t pc_31;
    struct blc_ranger_Delay pc_31_blc_ranger_Delay;
};
struct blc_ranger_HelpSettingsScreen {
    blc_nat8 blc_HelpSettingsScreen_page;
    blc_bool blc_HelpSettingsScreen_87_hasNextPage;
    blc_nat8 blc_HelpSettingsScreen_87_press;
    blc_pc_t pc_32;
    struct blc_ranger_PressRecognizer pc_32_blc_ranger_PressRecognizer;
};
struct blc_ranger_UnitSettingsScreen {
    blc_nat8 blc_UnitSettingsScreen_displayedUnit;
    blc_nat8 blc_UnitSettingsScreen_93_press;
    blc_pc_t pc_33;
    struct blc_ranger_PressRecognizer pc_33_blc_ranger_PressRecognizer;
};
struct blc_ranger_OffsetSettingsScreen {
    blc_nat8 blc_OffsetSettingsScreen_97_press;
    blc_pc_t pc_34;
    struct blc_ranger_PressRecognizer pc_34_blc_ranger_PressRecognizer;
};
struct blc_ranger_BLESettingsScreen {
    blc_nat8 blc_BLESettingsScreen_100_press;
    blc_pc_t pc_35;
    struct blc_ranger_PressRecognizer pc_35_blc_ranger_PressRecognizer;
};
struct blc_ranger_BrightnessSettingsScreen {
    blc_nat8 blc_BrightnessSettingsScreen_105_press;
    blc_pc_t pc_36;
    struct blc_ranger_PressRecognizer pc_36_blc_ranger_PressRecognizer;
};
struct blc_ranger_SettingsScreen {
    blc_nat8 blc_SettingsScreen_index;
    blc_nat8 blc_SettingsScreen_110_press;
    blc_pc_t pc_37;
    blc_pc_t pc_38;
    blc_pc_t pc_39;
    struct blc_ranger_PressRecognizer pc_37_blc_ranger_PressRecognizer;
    struct blc_ranger_BLESettingsScreen pc_38_blc_ranger_BLESettingsScreen;
    struct blc_ranger_BrightnessSettingsScreen pc_38_blc_ranger_BrightnessSettingsScreen;
    struct blc_ranger_HelpSettingsScreen pc_38_blc_ranger_HelpSettingsScreen;
    struct blc_ranger_OffsetSettingsScreen pc_38_blc_ranger_OffsetSettingsScreen;
    struct blc_ranger_UnitSettingsScreen pc_38_blc_ranger_UnitSettingsScreen;
    struct blc_ranger_SettingsPersister pc_39_blc_ranger_SettingsPersister;
};
struct blc_ranger_HomeScreen {
    blc_bool blc_HomeScreen_prevBLEConnected;
    struct blc_ranger_BatteryInfo blc_HomeScreen_prevBattery;
    struct blc_ranger_ButtonStates blc_HomeScreen_buttonStates;
    blc_nat8 blc_HomeScreen_brightness;
    blc_nat8 blc_HomeScreen_122_123_pressType;
    blc_pc_t pc_40;
    blc_pc_t pc_41;
    blc_pc_t pc_42;
    blc_pc_t pc_43;
    blc_pc_t pc_44;
    blc_pc_t pc_45;
    struct blc_ranger_SettingsScreen pc_41_blc_ranger_SettingsScreen;
    struct blc_ranger_PressRecognizer pc_43_blc_ranger_PressRecognizer;
    struct blc_ranger_Dimmer pc_44_blc_ranger_Dimmer;
};
struct blc_ranger_RangingScreen {
    blc_pc_t pc_46;
    blc_pc_t pc_47;
    blc_pc_t pc_48;
};
struct blc_ranger_ErrorScreen {
    blc_pc_t pc_49;
    struct blc_ranger_PressRecognizer pc_49_blc_ranger_PressRecognizer;
};
struct blc_ranger_UI {
    blc_nat8 blc_UI_screenBrightness;
    blc_nat8 blc_UI_dialogBrightness;
    struct blc_ranger_DialogRequest blc_UI_bleDialogRequest;
    struct blc_ranger_DialogRequest blc_UI_usbDialogRequest;
    struct blc_ranger_DialogRequest blc_UI_batteryDialogRequest;
    blc_nat8 blc_UI_orientation;
    blc_pc_t pc_50;
    blc_pc_t pc_51;
    blc_pc_t pc_52;
    blc_pc_t pc_53;
    blc_pc_t pc_54;
    blc_pc_t pc_55;
    blc_pc_t pc_56;
    blc_pc_t pc_57;
    struct blc_ranger_ErrorScreen pc_51_blc_ranger_ErrorScreen;
    struct blc_ranger_HomeScreen pc_51_blc_ranger_HomeScreen;
    struct blc_ranger_RangingScreen pc_51_blc_ranger_RangingScreen;
    struct blc_ranger_WelcomeScreen pc_51_blc_ranger_WelcomeScreen;
    struct blc_ranger_BLEDialog pc_52_blc_ranger_BLEDialog;
    struct blc_ranger_USBDialog pc_53_blc_ranger_USBDialog;
    struct blc_ranger_BatteryDialog pc_54_blc_ranger_BatteryDialog;
    struct blc_ranger_DialogManager pc_55_blc_ranger_DialogManager;
    struct blc_ranger_BrightnessController pc_56_blc_ranger_BrightnessController;
    struct blc_ranger_RotationController pc_57_blc_ranger_RotationController;
};
struct blc_ranger_RangeSensor {
    blc_pc_t pc_58;
};
struct blc_ranger_BluetoothPublisher {
    blc_nat16 blc_BluetoothPublisher_151_prevRange;
    struct blc_ranger_BatteryInfo blc_BluetoothPublisher_151_prevBattery;
    blc_pc_t pc_59;
};
struct blc_ranger_BatterySensor {
    blc_pc_t pc_60;
    struct blc_ranger_DelayOrDidWakeup pc_60_blc_ranger_DelayOrDidWakeup;
};
struct blc_ranger_PowerManager {
    blc_bool blc_PowerManager_160_161_163_164_2_abortFinished;
    blc_pc_t pc_61;
    struct blc_ranger_Delay pc_61_blc_ranger_Delay;
};
struct blc_ranger_Main {
    blc_nat16 blc_Main_range;
    struct blc_ranger_BatteryInfo blc_Main_battery;
    blc_bool blc_Main_rangingRequest;
    blc_nat8 blc_Main_brightness;
    struct blc_ranger_Settings blc_Main_settings;
    blc_pc_t pc_62;
    blc_pc_t pc_63;
    blc_pc_t pc_64;
    blc_pc_t pc_65;
    blc_pc_t pc_66;
    blc_pc_t pc_67;
    struct blc_ranger_RangeSensor pc_63_blc_ranger_RangeSensor;
    struct blc_ranger_BatterySensor pc_64_blc_ranger_BatterySensor;
    struct blc_ranger_UI pc_65_blc_ranger_UI;
    struct blc_ranger_BluetoothPublisher pc_66_blc_ranger_BluetoothPublisher;
    struct blc_ranger_PowerManager pc_67_blc_ranger_PowerManager;
};

/*
** extern functions to be implemented in C
*/

void blc_ranger_loadSettings (struct blc_ranger_Settings *blc_retvar);

void blc_ranger_storeSettings (const struct blc_ranger_Settings *const blc_settings);

void blc_ranger_setScreenDimming (const blc_nat8 blc_level);

blc_float32 blc_ranger_readRotation (void);

void blc_ranger_setOrientation (const blc_nat8 blc_orientation);

void blc_ranger_displayDialog (const struct blc_ranger_DialogRequest *const blc_request);

void blc_ranger_hideDialog (void);

void blc_ranger_displayWelcomeScreen (void);

blc_bool blc_ranger_displayHelpSettingsScreen (const blc_nat8 blc_page);

void blc_ranger_displayUnitSettingsScreen (const blc_nat8 blc_displayedUnit,
                                           const blc_nat8 blc_selectedUnit);

void blc_ranger_displayOffsetSettingsScreen (const blc_bool blc_measureFromBack);

void blc_ranger_displayBLESettingsScreen (const blc_bool blc_bleEnabled);

void blc_ranger_enableBLE (void);

void blc_ranger_requestRestart (void);

void blc_ranger_displayBrightnessSettingsScreen (const blc_nat8 blc_brightness);

void blc_ranger_displaySettingsScreen (const blc_nat8 blc_index);

void blc_ranger_displayHomeScreen (const struct blc_ranger_BatteryInfo *const blc_battery,
                                   const blc_bool blc_bleEnabled);

void blc_ranger_displayRangingScreen (const blc_nat16 blc_range,
                                      const struct blc_ranger_BatteryInfo *const blc_battery,
                                      const blc_nat8 blc_orientation,
                                      const struct blc_ranger_Settings *const blc_settings);

void blc_ranger_displayErrorScreen (const blc_nat8 blc_err);

void blc_ranger_startRanging (void);

blc_nat16 blc_ranger_measure (void);

void blc_ranger_stopRanging (void);

void blc_ranger_publishRange (const blc_nat16 blc_range);

void blc_ranger_publishBattery (const struct blc_ranger_BatteryInfo *const blc_battery);

void blc_ranger_readBatteryInfo (struct blc_ranger_BatteryInfo *blc_retvar);

void blc_ranger_activateDisplay (const blc_bool blc_active);

void blc_ranger_enterSleep (const blc_nat16 blc_ticks);

/*
** program functions: tick, init
*/

void blc_blech_ranger_tick (const blc_nat8 blc_setupErr);

void blc_blech_ranger_init (void);

void blc_blech_ranger_printState (const blc_nat8 blc_setupErr);

#endif /* BLECH_RANGER_H_INCLUDED */