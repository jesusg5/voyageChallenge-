#include "application.h"
#include "Particle.h"
#include <lib/carloop.h>
#include <lib/LIS3DH.h>

// function declerations
void printGPSValues();
void printAccValues();
void printDateTime(TinyGPSDate &d, TinyGPSTime &t);

Carloop<CarloopRevision2> carloop;

// Print 10 accelerometer samples per second to serial
const unsigned long ACCEL_SAMPLE_PERIOD = 100;
// Print GPS sample every 2 seconds
const unsigned long GPS_SAMPLE_PERIOD = 2000;

// LIS3DH is connected via SPI with A2 as the CS (SS) pin, and INT connected to WKP
LIS3DHSPI accel(SPI, A2, WKP);
unsigned long lastAccelSample = 0;
unsigned long lastGPSSample = 0;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    // initialize carloop
    carloop.begin();

    // Initialize accelerometer
    LIS3DHConfig config;
    config.setAccelMode(LIS3DH::RATE_100_HZ);

    bool setupSuccess = accel.setup(config);
    Serial.printlnf("setupSuccess=%d", setupSuccess);
    // stop if setup failed
    while(!setupSuccess)  { }
}

void loop()
{
    carloop.update();

    if (millis() - lastAccelSample >= ACCEL_SAMPLE_PERIOD) {
		    lastAccelSample = millis();
        printAccValues();
      }

    if (millis() - lastGPSSample >= GPS_SAMPLE_PERIOD) {
        lastGPSSample = millis();
        printGPSValues();
    }
}

void printAccValues()
{
  LIS3DHSample acc;
  if (accel.getSample(acc)) {
    Serial.printlnf("%d,%d,%d ", acc.x, acc.y, acc.z);
  }
  else {
    Serial.println("no sample!");
  }
}

// This function prints gps values+current date/time
void printGPSValues()
{
    auto &gps = carloop.gps();

    // Lock gps readings while printing
    WITH_LOCK(gps) {
        Serial.print("GPS: ");

        // print GPS values if readings are valid
        if (gps.location.isValid()) {
          printDateTime(gps.date, gps.time); // Timestamp
          Serial.printf("Latitude: %d , Longitude: %d", gps.location.lat(),gps.location.lng());
        }
        else {
          Serial.println("GPS reading invalid!");
        }

        Serial.println(" "); // print new line
    }
}

// date+time print function courtesy of carloop library/example code
void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
    if (!d.isValid()) {
        Serial.print("********** ");
    }
    else {
        Serial.printf("%02d/%02d/%02d ", d.month(), d.day(), d.year());
    }

    if (!t.isValid()) {
        Serial.print("******** ");
    }
    else {
        Serial.printf("%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    }
}
