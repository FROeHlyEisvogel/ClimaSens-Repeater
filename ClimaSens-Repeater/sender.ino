void initBLESender () {
  BLEDevice::deinit(false);
  BLEDevice::init("");
  BLEDevice::setPower (ESP_PWR_LVL_P9);
  
  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();

  pAdvertising = BLEDevice::getAdvertising();
  setBeacon();
}

void sendBLEDevice (std::string mManufacturerData, BLEAddress mAddress) {
  
  
  setBeaconManufacturerData (mManufacturerData, mAddress);
  
  pAdvertising->start();
  delay(SEND_TIME);
  pAdvertising->stop();
}

void setBeaconManufacturerData (std::string mManufacturerData, BLEAddress mAddress) {
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04

  String myAddress = mAddress.toString().c_str();
  
  mManufacturerData += stringToHex(myAddress.substring(0,2));
  mManufacturerData += stringToHex(myAddress.substring(3,5));
  mManufacturerData += stringToHex(myAddress.substring(6,8));
  mManufacturerData += stringToHex(myAddress.substring(9,11));
  mManufacturerData += stringToHex(myAddress.substring(12,14));
  mManufacturerData += stringToHex(myAddress.substring(15,17));
  
  oAdvertisementData.setManufacturerData(mManufacturerData);
  pAdvertising->setAdvertisementData(oAdvertisementData);
}

void setBeacon() {
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();

  oScanResponseData.setName ("ClimaSensRepeater");
  
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04

  std::string strManufacturerData = "";
  strManufacturerData += (char)0xFF;    // MSB Company ID
  strManufacturerData += (char)0xFF;    // LSB Company ID
  strManufacturerData += (char)0x00;    // MSB Internal Voltage
  strManufacturerData += (char)0x00;    // LSB Internal Voltage
  strManufacturerData += (char)0x00;    // MSB Internal Temperature
  strManufacturerData += (char)0x00;    // LSB Internal Temperature
  strManufacturerData += (char)0x00;    // MSB Luminance
  strManufacturerData += (char)0x00;    // LSB Luminance
  strManufacturerData += (char)0x00;    // MSB Temperature
  strManufacturerData += (char)0x00;    // LSB Temperature
  strManufacturerData += (char)0x00;    // MSB Humidity
  strManufacturerData += (char)0x00;    // LSB Humidity
  strManufacturerData += (char)0x00;    // MSB Barometric
  strManufacturerData += (char)0x00;    // LSB Barometric
  strManufacturerData += (char)0x00;    // Open/Close
  strManufacturerData += (char)0x00;    // MSB Power
  strManufacturerData += (char)0x00;    // LSB Power
  
  oAdvertisementData.setManufacturerData(strManufacturerData);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);

  //pAdvertising->setMinInterval (160);  // 100ms
  //pAdvertising->setMaxInterval (160);  // 100ms
  pAdvertising->setMinInterval (35); // 40ms
  pAdvertising->setMaxInterval (35); // 40ms
}
