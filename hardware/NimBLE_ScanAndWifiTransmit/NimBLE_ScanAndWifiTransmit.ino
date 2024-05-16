#pragma optionbytes = INTPWRMEM_EN // Enable program compression

#include <NimBLEDevice.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "xxx";
const char* pass = "***";
bool hasData = false;
int rssiData;
uint8_t clock_counter=0;

#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"

NimBLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
        // Check if the advertised device has the desired service UUID
        if (advertisedDevice->haveServiceUUID() && advertisedDevice->isAdvertisingService(BLEUUID(SERVICE_UUID))) {
            Serial.printf("Found device with service UUID %s: %s\n", SERVICE_UUID, advertisedDevice->toString().c_str());
            hasData = true;
            rssiData = advertisedDevice->getRSSI();
            Serial.println(rssiData);
        }
    }
};

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(10);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");

    Serial.println("Scanning for BLE devices...");
    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DATA_DEVICE);
    NimBLEDevice::setScanDuplicateCacheSize(200);
    NimBLEDevice::init("");
    pBLEScan = NimBLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), false);
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(97); // How often the scan occurs / switches channels; in milliseconds,
    pBLEScan->setWindow(37);  // How long to scan during the interval; in milliseconds.
    pBLEScan->setMaxResults(0); // do not store the scan results, use callback only.
}

void loop() {
    // If an error occurs that stops the scan, it will be restarted here.
    if(pBLEScan->isScanning() == false) {
        // Start scan with: duration = 0 seconds(forever), no scan end callback, not a continuation of a previous scan.
        pBLEScan->start(1, nullptr, false);
    }
    if(clock_counter >= 10000){
      clock_counter = 0;
    }
    if (hasData) {
        HTTPClient http;
        http.begin("http://172.20.10.6:5001/data"); // Change server URL to device URL
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpCode = http.POST("A="+String(rssiData)+"="+String(clock_counter));
        if (httpCode > 0) {
            Serial.printf("HTTP Response code: %d\n", httpCode);

        } else {
            Serial.println("Error sending HTTP request"+String(httpCode));
        }
        http.end();
        hasData = false;
        clock_counter++;
    }
    delay(1000);
}