// ranger
// Copyright (c) 2021, Framework Labs.

// Includes

#include <M5StickC.h>
#include <VL53L0X.h>
#include <AXP192.h>
#include <BLEDevice.h>
#include <BLEService.h>
#include <BLECharacteristic.h>
#include <BLE2902.h>
#include <BLEAdvertising.h>
#include <Preferences.h>
#include <Esp.h>
#include <esp_sleep.h>
#include <esp_task_wdt.h>
#include <freertos/task.h>

extern "C"
{
#include "ranger.h"
#include "env.h"
}

// Defines

#define var auto
#define let const auto

// Constants

static constexpr auto VERSION = "V0.0.1";

static constexpr auto RANGE_SERVICE_UUID = "337c1e7b-b79f-4253-8ab7-66d59edbfb73";
static constexpr auto RANGE_CHAR_UUID = "b5791522-10cf-45ae-a308-9a37ffa329d8";

static constexpr auto BATTERY_SERVICE_UUID = "180f";
static constexpr auto BATTERY_CHAR_UUID = "2a19";

// Outputs

blc_ranger_ButtonStates buttonStates{};
blc_bool bleConnected = false;
blc_bool didWakeup = false;

// Globals

static blc_nat8 setupErr = 0;

static blc_nat16 wantsSleep = 0;
static var wantsRestart = false;

static VL53L0X sensor;

static TFT_eSprite screen{&M5.Lcd};
static TFT_eSprite dialog{&M5.Lcd};
static var showScreen = false;
static var showDialog = false;

static BLEServer *server = nullptr;
static BLECharacteristic *rangeChar = nullptr;
static BLECharacteristic *batteryChar = nullptr;

static Preferences preferences;

// Settings

void blc_ranger_loadSettings(struct blc_ranger_Settings *result)
{
  let size = preferences.getBytes("Settings", result, sizeof(struct blc_ranger_Settings));
  if (size < sizeof(struct blc_ranger_Settings))
  {
    if (size != 0)
    {
      // Upgrade detected - remove old settings.
      preferences.remove("Settings");
    }

    // Init settings with default values.
    result->measureFromBack = false;
    result->brightness = 10;
    result->bleEnabled = false;
    result->measureUnit = MEASURE_UNIT_CM;
  }
}

void blc_ranger_storeSettings(const struct blc_ranger_Settings *const settings)
{
  let size = preferences.putBytes("Settings", settings, sizeof(struct blc_ranger_Settings));
  if (size == 0)
  {
    Serial.println("Failed to store settings");
  }
}

// UI Helpers

void blc_ranger_setScreenDimming(const blc_nat8 level)
{
  M5.Axp.ScreenBreath(level);
}

blc_float32 blc_ranger_readRotation(void)
{
  blc_float32 x, y, z;
  M5.Imu.getAccelData(&x, &y, &z);
  return x;
}

void blc_ranger_setOrientation(const blc_nat8 orientation)
{
  M5.Lcd.setRotation(orientation);
  showScreen = true;
}

// Dialogs

void blc_ranger_displayDialog(const struct blc_ranger_DialogRequest *const request)
{
  dialog.fillSprite(BLACK);
  dialog.setTextFont(2);
  dialog.setCursor(10, 22);

  if (request->kind == DIALOG_BATTERY)
  {
    var percent = 0;
    if (request->info == DIALOG_BATTERY_BELOW_10)
    {
      percent = 10;
      dialog.setTextColor(RED);
    }
    else
    {
      percent = 20;
      dialog.setTextColor(ORANGE);
    }

    dialog.printf("Battery below %d%%!", percent);
  }
  else if (request->kind == DIALOG_BLE)
  {
    dialog.setTextColor(BLUE);

    switch (request->info)
    {
    case DIALOG_BLE_DISCONNECTED:
      dialog.print("BLE disconnected");
      break;
    case DIALOG_BLE_CONNECTED:
      dialog.print("BLE connected");
      break;
    case DIALOG_BLE_ENABLED:
      dialog.print("BLE enabled");
      break;
    }
  }
  else if (request->kind == DIALOG_USB)
  {
    dialog.setTextColor(WHITE);

    if (request->info == DIALOG_USB_CONNECTED)
    {
      dialog.print("USB connected");
    }
    else
    {
      dialog.print("USB disconnected");
    }
  }

  showDialog = true;
}

void blc_ranger_hideDialog(void)
{
  showDialog = false;
}

// Screens

static void displayStatusPane(const struct blc_ranger_BatteryInfo *const battery, const blc_bool bleEnabled)
{
  screen.setTextFont(1);

  if (bleEnabled)
  {
    screen.setTextColor(BLUE);
    screen.setCursor(10, 6);
    if (bleConnected)
    {
      screen.print("BT connected");
    }
    else
    {
      screen.print("BT");
    }
  }

  screen.setTextColor(BLACK);
  screen.setCursor(110, 6);
  screen.printf("%s %d%%", battery->isCharging ? "USB" : "   ", battery->stateOfCharge);
}

static void displayNavigationPane(const char *doubleText, const char *longText = "Go Back")
{
  screen.setTextColor(BLACK);
  screen.setTextFont(1);

  int16_t y = 70;
  if (longText)
  {
    screen.setCursor(10, y);
    y -= 10;
    screen.print("Long press: ");
    screen.print(longText);
  }
  if (doubleText)
  {
    screen.setCursor(10, y);
    screen.print("Double press: ");
    screen.print(doubleText);
  }
}

void blc_ranger_displayWelcomeScreen(void)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setTextFont(4);
  screen.setCursor(30, 30);
  screen.print("Ranger");

  screen.setTextFont(1);
  screen.setCursor(20, 65);
  screen.print(VERSION);

  showScreen = true;
}

blc_bool blc_ranger_displayHelpSettingsScreen(const blc_nat8 page)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);
  screen.setTextFont(1);

  screen.setCursor(10, 6);
  screen.println("Help & Info");

  var hasNextPage = true;
  int16_t y = 24;
  let pr = [&y](const char *txt)
  {
    screen.setCursor(6, y);
    screen.print(txt);
    y += 14;
  };

  switch (page)
  {
  case 0:
    pr("Ranger lets you measure");
    pr("the distance up to 2m.");
    pr("You can measure either");
    pr("from the top of the hat");
    break;
  case 1:
    pr("or from the bottom of");
    pr("the stick.");
    pr("This can be changed in");
    pr("the 'Offset' settings.");
    break;
  case 2:
    pr("Ranger can publish");
    pr("the measured distance");
    pr("via Bluetooth LE.");
    pr("Enable Bluetooth in");
    break;
  case 3:
    pr("the Settings under");
    pr("Bluetooth. Note that when");
    pr("enabled the device can't");
    pr("go to sleep mode.");
    break;
  case 4:
    pr("Ranger ");
    pr(VERSION);
    pr("(c) 2021 Framework Labs");
    hasNextPage = false;
    displayNavigationPane(nullptr);
    break;
  }

  showScreen = true;

  return hasNextPage;
}

void blc_ranger_displayUnitSettingsScreen(const blc_nat8 displayedUnit,
                                          const blc_nat8 selectedUnit)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setCursor(10, 6, 1);
  screen.print("Units");

  screen.setCursor(20, 24, 2);
  switch (displayedUnit)
  {
  case MEASURE_UNIT_MM:
    screen.print("Millimeter [mm]");
    break;
  case MEASURE_UNIT_CM:
    screen.print("Centimeter [cm]");
    break;
  case MEASURE_UNIT_M:
    screen.print("Meter [m]");
    break;
  }
  if (selectedUnit == displayedUnit)
  {
    screen.setCursor(40, 42, 1);
    screen.print("(selected)");
  }

  displayNavigationPane("Set");

  showScreen = true;
}

void blc_ranger_displayOffsetSettingsScreen(const blc_bool measureFromBack)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setCursor(10, 6, 1);
  screen.print("Offset");

  screen.setCursor(20, 30, 2);
  if (measureFromBack)
  {
    screen.print("Measure from Back");
  }
  else
  {
    screen.print("Measure from Hat");
  }

  displayNavigationPane(nullptr);

  showScreen = true;
}

void blc_ranger_displayBLESettingsScreen(const blc_bool bleEnabled)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setCursor(10, 6, 1);
  screen.print("Bluetooth");

  screen.setCursor(20, 30, 2);
  if (bleEnabled)
  {
    screen.print("Bluetooth enabled");
  }
  else
  {
    screen.print("Bluetooth disabled");
  }

  screen.setTextColor(RED);
  screen.setCursor(10, 60, 1);
  if (bleEnabled)
  {
    screen.print("Double press to disable!");
  }
  else
  {
    screen.print("Double press to enable!");
  }

  displayNavigationPane(nullptr);

  showScreen = true;
}

void blc_ranger_displayBrightnessSettingsScreen(const blc_nat8 brightness)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setCursor(10, 6, 1);
  screen.print("Brightness");

  screen.setCursor(20, 30, 2);
  switch (brightness)
  {
  case 1:
    screen.print("very low");
    break;
  case 2:
    screen.print("low");
    break;
  case 3:
    screen.print("medium");
    break;
  case 4:
    screen.print("high");
    break;
  case 5:
    screen.print("very high");
    break;
  }

  displayNavigationPane(nullptr);

  showScreen = true;
}

void blc_ranger_displaySettingsScreen(const blc_nat8 index)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setCursor(10, 6, 1);
  screen.print("Settings");

  screen.setCursor(20, 30, 2);
  switch (index)
  {
  case SETTINGS_HELP:
    screen.print("Help & Info");
    break;
  case SETTINGS_UNIT:
    screen.print("Units");
    break;
  case SETTINGS_OFFSET:
    screen.print("Offset");
    break;
  case SETTINGS_BLE:
    screen.print("Bluetooth");
    break;
  case SETTINGS_BRIGHTNESS:
    screen.print("Brightness");
    break;
  }

  displayNavigationPane("Show");

  showScreen = true;
}

void blc_ranger_displayHomeScreen(const struct blc_ranger_BatteryInfo *const battery, const blc_bool bleEnabled)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);
  screen.setCursor(30, 30, 2);
  screen.print("Press to Start");

  displayStatusPane(battery, bleEnabled);
  displayNavigationPane("Settings", nullptr);

  showScreen = true;
}

void blc_ranger_displayRangingScreen(const blc_nat16 range,
                                     const struct blc_ranger_BatteryInfo *const battery,
                                     const blc_nat8 orientation,
                                     const struct blc_ranger_Settings *const settings)
{
  screen.fillSprite(WHITE);
  screen.setTextColor(BLACK);

  screen.setCursor(20, 30, 4);
  if (range >= 8190)
  {
    screen.print("----");
  }
  else
  {
    switch (settings->measureUnit)
    {
    case MEASURE_UNIT_MM:
      screen.printf("%u mm", range);
      break;
    case MEASURE_UNIT_CM:
      screen.printf("%.1f cm", float(range) / 10.0);
      break;
    case MEASURE_UNIT_M:
      screen.printf("%.3f m", float(range) / 1000.0);
      break;
    }
  }
  if (orientation == ORIENTATION_HAT_LEFT)
  {
    if (settings->measureFromBack)
    {
      screen.fillTriangle(150, 40, 160, 35, 160, 45, BLACK);
    }
    else
    {
      screen.fillTriangle(0, 40, 10, 35, 10, 45, BLACK);
    }
  }
  else
  {
    if (settings->measureFromBack)
    {
      screen.fillTriangle(0, 35, 0, 45, 10, 40, BLACK);
    }
    else
    {
      screen.fillTriangle(150, 35, 150, 45, 160, 40, BLACK);
    }
  }

  screen.setCursor(10, 65, 1);
  screen.print("Press to Stop");

  displayStatusPane(battery, settings->bleEnabled);

  showScreen = true;
}

void blc_ranger_displayErrorScreen(const blc_nat8 err)
{
  screen.fillSprite(RED);
  screen.setTextColor(WHITE);

  screen.setCursor(30, 30, 2);
  switch (err)
  {
  case ERR_TOF:
    screen.print("ToF Hat missing!");
    break;
  default:
    screen.printf("ERROR: %u", err);
    break;
  }

  screen.setCursor(10, 60, 1);
  screen.print("Press any key to restart");

  showScreen = true;
}

// Ranging

void blc_ranger_startRanging(void)
{
  sensor.startContinuous(100);
  sensor.setTimeout(50);
}

blc_nat16 blc_ranger_measure(void)
{
  let range = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred())
  {
    return UNDEF_RANGE;
  }
  return range;
}

void blc_ranger_stopRanging(void)
{
  sensor.stopContinuous();
}

// Bluetooth

static bool setupBT()
{
  BLEDevice::init("Ranger");

  server = BLEDevice::createServer();

  struct Callbacks : BLEServerCallbacks
  {
    void onDisconnect(BLEServer *pServer) final
    {
      BLEDevice::startAdvertising();
    }
  };
  server->setCallbacks(new Callbacks);

  var *rangeService = server->createService(RANGE_SERVICE_UUID);
  rangeChar = rangeService->createCharacteristic(
      RANGE_CHAR_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  {
    var *descriptor = new BLE2902;
    descriptor->setNotifications(true);
    rangeChar->addDescriptor(descriptor);
  }
  rangeService->start();

  uint16_t rangeValue = UNDEF_RANGE;
  rangeChar->setValue(rangeValue);

  var *batteryService = server->createService(BATTERY_SERVICE_UUID);
  batteryChar = batteryService->createCharacteristic(BATTERY_CHAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  {
    var *descriptor = new BLE2902;
    descriptor->setNotifications(true);
    batteryChar->addDescriptor(descriptor);
  }
  batteryService->start();

  uint8_t batteryValue = 0;
  batteryChar->setValue(&batteryValue, 1);

  var *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(RANGE_SERVICE_UUID);
  advertising->addServiceUUID(BATTERY_SERVICE_UUID);
  advertising->setScanResponse(true);
  advertising->setScanFilter(false, false);
  advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  esp_bt_sleep_enable();

  return true;
}

void blc_ranger_enableBLE(void)
{
  setupBT();
}

void blc_ranger_requestRestart(void)
{
  wantsRestart = true;
}

void blc_ranger_publishRange(const blc_nat16 range)
{
  uint16_t value = range;
  rangeChar->setValue(value);
  rangeChar->notify();
}

void blc_ranger_publishBattery(const struct blc_ranger_BatteryInfo *const battery)
{
  uint8_t value = battery->stateOfCharge;
  batteryChar->setValue(&value, 1);
  batteryChar->notify();
}

// Battery & Sleep

void blc_ranger_readBatteryInfo(struct blc_ranger_BatteryInfo *result)
{
  static constexpr float volts[] = {3.2, 3.7, 4.0, 4.2};
  static constexpr float socs[] = {0.0, 0.2, 0.8, 1.0};

  float volt = M5.Axp.GetBatVoltage();

  float soc{};
  if (volt <= volts[0])
  {
    soc = socs[0];
  }
  else
  {
    constexpr auto num = sizeof(volts) / sizeof(float);
    for (size_t i = 1; i < num; ++i)
    {
      if (volt <= volts[i])
      {
        let weight = (volt - volts[i - 1]) / (volts[i] - volts[i - 1]);
        soc = weight * (socs[i] - socs[i - 1]) + socs[i - 1];
        break;
      }
    }
  }

  result->voltage = blc_float32(volt);
  result->stateOfCharge = blc_nat8(soc * 100);
  result->isCharging = (M5.Axp.GetInputPowerStatus() & 0b00110000) != 0;
}

static void write1Byte(TwoWire &wire, uint8_t addr, uint8_t reg, uint8_t data)
{
  wire.beginTransmission(addr);
  wire.write(reg);
  wire.write(data);
  wire.endTransmission();
}

static void configurePMU()
{
  write1Byte(Wire1, 0x34, 0x10, 0x00);       // Disable DC-DC2 and EXTERN
  write1Byte(Wire1, 0x34, 0x12, 0b00001101); // Disable DC-DC3 and enable LD02/3 and DC-DC1
  write1Byte(Wire1, 0x34, 0x90, 0x00);       // Disable LDOIO
  write1Byte(Wire1, 0x34, 0x94, 0b00000111); // Set GPIOs to float
}

static void sleepPeripherals()
{
  if (M5.Imu.imuType == 2)
  {
    write1Byte(Wire1, MPU6886_ADDRESS, MPU6886_PWR_MGMT_1, 0b01001111);
  }
}

static void wakePeripherals()
{
  if (M5.Imu.imuType == 2)
  {
    write1Byte(Wire1, MPU6886_ADDRESS, MPU6886_PWR_MGMT_1, 0b00001001);

    // IMU needs a bit to wakeup otherwise reading from it will report old data.
    delay(20);
  }
}

void blc_ranger_activateDisplay(const blc_bool active)
{
  M5.Axp.SetLDO2(active);
  M5.Axp.SetLDO3(active);
}

void blc_ranger_enterSleep(const blc_nat16 ticks)
{
  wantsSleep = ticks;
}

// Watchdog

static bool configureWDT()
{
  if (esp_task_wdt_init(2, true) != ESP_OK)
  {
    return false;
  }
  if (esp_task_wdt_add(NULL) != ESP_OK)
  {
    return false;
  }
  return true;
}

static void resetWDT()
{
  esp_task_wdt_reset();
}

// Setup Helpers

static void note(const char *msg)
{
  static int lines = 0;
  ++lines;
  if (lines > 10)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    lines = 0;
  }
  M5.Lcd.println(msg);
  Serial.println(msg);
}

// Arduino setup/loop

void setup()
{
  setCpuFrequencyMhz(80);

  M5.begin();

  M5.Lcd.setRotation(1);
  screen.createSprite(160, 80);
  dialog.createSprite(140, 60);

  note("Config WDT");
  if (!configureWDT())
  {
    note("Config WDT failed");
    // Continue anyways.
  }

  note("Config PMU");
  configurePMU();

  note("Init Blech");
  blc_blech_ranger_init();

  note("Init Preferences");
  if (!preferences.begin("Ranger"))
  {
    note("Preferences setup failed");
    setupErr = ERR_PREFS;
    return;
  }

  note("Init IMU");
  if (M5.Imu.Init())
  {
    note("IMU setup failed");
    setupErr = ERR_IMU;
    return;
  }

  if (M5.Imu.imuType == 1)
  {
    note("Detected SH200Q");
  }
  else if (M5.Imu.imuType == 2)
  {
    note("Detected MPU6886");
  }

  note("Init Wire");
  if (!Wire.begin(0, 26, 100000))
  {
    note("Wire setup failed");
    setupErr = ERR_WIRE;
    return;
  }

  note("Init ToF Sensor");
  if (!sensor.init())
  {
    note("ToF sensor setup failed");
    setupErr = ERR_TOF;
    return;
  }

  note("Loading Settings");
  struct blc_ranger_Settings settings;
  blc_ranger_loadSettings(&settings);

  if (settings.bleEnabled)
  {
    note("Setting up Bluetooth");
    if (!setupBT())
    {
      note("BT setup failed");
      setupErr = ERR_BLE;
      return;
    }
  }

  resetWDT();

  note("Setup finished");
}

void loop()
{
  TickType_t prevWakeTime = xTaskGetTickCount();

  while (true)
  {
    M5.update();
    buttonStates.aPressed = M5.BtnA.wasPressed();
    buttonStates.aReleased = M5.BtnA.wasReleased();
    buttonStates.bPressed = M5.BtnB.wasPressed();
    buttonStates.bReleased = M5.BtnB.wasReleased();
    if (server)
    {
      bleConnected = server->getConnectedCount() > 0;
    }
    else
    {
      bleConnected = false;
    }

    showScreen = false;
    wantsSleep = 0;
    bool didShowDialog = showDialog;

    blc_blech_ranger_tick(setupErr);

    if (showDialog)
    {
      dialog.pushSprite(10, 10);
    }
    else if (showScreen || didShowDialog)
    {
      screen.pushSprite(0, 0);
    }
    didWakeup = false;

    resetWDT();

    if (wantsRestart)
    {
      ESP.restart();
      return;
    }
    if (wantsSleep)
    {
      sleepPeripherals();
      esp_sleep_enable_timer_wakeup(100000 * wantsSleep);
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, LOW);
      esp_light_sleep_start();
      wakePeripherals();
      didWakeup = true;
    }
    else
    {
      vTaskDelayUntil(&prevWakeTime, 100);
    }
  }
}
