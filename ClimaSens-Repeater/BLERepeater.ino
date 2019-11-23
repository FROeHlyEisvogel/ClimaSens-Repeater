#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//Scanner
BLEScan* pBLEScan;
BLEScanResults foundDevices;

boolean callbackDeviceFound = false;
uint8_t dataBuffer[100];
BLEAdvertisedDevice callbackDevice;
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    BLEUtils::buildHexData(dataBuffer, (uint8_t*)advertisedDevice.getManufacturerData().data(), advertisedDevice.getManufacturerData().length());
    if ((advertisedDevice.getName() == "ClimaSens") && (dataBuffer[29] == '2')) pBLEScan->stop(), callbackDevice = advertisedDevice, callbackDeviceFound = true;
  }
};

//Sender
BLEAdvertising *pAdvertising;

#define SCAN_TIME 60    // seconds
#define SEND_TIME 250   // ms

void setup() {
  Serial.begin(115200);
}

void loop() {
  initBLEScanner ();
  Serial.println("Scanning...");
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME, false);

  initBLESender ();
  if (callbackDeviceFound) {
    callbackDeviceFound = false;
    serialPrintBLEDevice (callbackDevice);
    sendBLEDevice (callbackDevice.getManufacturerData(), callbackDevice.getAddress());
    pBLEScan->clearResults();
    return;
  }
  
  for (int deviceIndex = foundDevices.getCount(); deviceIndex > 0; deviceIndex --) {
    BLEAdvertisedDevice myDevice = foundDevices.getDevice(deviceIndex);
      if (myDevice.getName() == "ClimaSens") {
        serialPrintBLEDevice (myDevice);
        sendBLEDevice (myDevice.getManufacturerData(), myDevice.getAddress());
    }
  }

  pBLEScan->clearResults();
  ESP.restart();
}
