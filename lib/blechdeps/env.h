// Ranger
// Copyright (c) 2021, Framework Labs.

#include "blech.h"

// Constants

#define ERR_OK 0
#define ERR_PREFS 1
#define ERR_IMU 2
#define ERR_WIRE 3
#define ERR_TOF 4
#define ERR_BLE 5

#define UNDEF_RANGE ((1 << 16) - 1)

#define DIALOG_BATTERY 1
#define DIALOG_BLE 2
#define DIALOG_USB 3

#define DIALOG_BATTERY_BELOW_10 1
#define DIALOG_BATTERY_BELOW_20 2

#define DIALOG_BLE_DISCONNECTED 0
#define DIALOG_BLE_CONNECTED 1
#define DIALOG_BLE_ENABLED 2

#define DIALOG_USB_DISCONNECTED 0
#define DIALOG_USB_CONNECTED 1

#define SETTINGS_HELP 0
#define SETTINGS_UNIT 1
#define SETTINGS_OFFSET 2
#define SETTINGS_BLE 3
#define SETTINGS_BRIGHTNESS 4

#define MEASURE_UNIT_MM 0
#define MEASURE_UNIT_CM 1
#define MEASURE_UNIT_M 2

#define ORIENTATION_HAT_LEFT 1
#define ORIENTATION_HAT_RIGHT 3

// Outputs

extern struct blc_ranger_ButtonStates buttonStates;
extern blc_bool bleConnected;
extern blc_bool didWakeup;
