/**************************************************************
 *
 * For this example, you need to install library:
 * TinyGSM Getting Started guide:
 *   http://tiny.cc/tiny-gsm-readme
 *
 **************************************************************/


// Select your modem:
#define TINY_GSM_MODEM_SIM800
//#define TINY_GSM_MODEM_SIM900
//#define TINY_GSM_MODEM_A6
//#define TINY_GSM_MODEM_M590

#include <TinyGsmClient.h>
#include <PubSubClient.h>
// Your GPRS credentials
// Leave empty, if missing user or pass
const char apn[]  = "APN";
const char user[] = "";
const char pass[] = "";

// Set serial for debug console (to the Serial Monitor, speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

void setup() {
    SerialMon.begin(115200);
    delay(10);
    // Set GSM module baud rate
    SerialAT.begin(38400);
    delay(3000);
      // Restart takes quite some time
      // To skip it, call init() instead of restart()
      Serial.println(F("Initializing modem..."));
      modem.restart();
      
      // Unlock your SIM card with a PIN
      //modem.simUnlock("1234");
         
      Serial.print(F("Waiting for network..."));
      if (!modem.waitForNetwork()) {
        Serial.println(" fail");
        while (true);
      }
      Serial.println(F(" OK"));
      Serial.print(F("Connecting to "));
      Serial.print(apn);
      if (!modem.gprsConnect(apn, user, pass)) {
        Serial.println(F(" fail"));
        while (true);
      }
      Serial.println(F(" OK"));
}

void loop() {
  
  String IMEI = modem.getIMEI();
  SerialMon.println(IMEI);
  delay(3000);
  String Location = modem.getGsmLocation();
  SerialMon.println(Location);
  delay(5000);
  String Time = modem.getNetTime();
  SerialMon.println(Time);
  delay(3000);
  // put your main code here, to run repeatedly:

}
