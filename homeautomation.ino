#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#define BLYNK_TEMPLATE_ID "TMPL3_4jHnxRi"
#define BLYNK_TEMPLATE_NAME "Home Automation"

#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>

// Define the relay pins
#define relay1 D0
#define relay2 D1
#define relay3 D2
#define relay4 D3

#define BLYNK_AUTH_TOKEN "YyZpD3oeItVRCDpPGTAF1MBydF-AByih" // Enter your Blynk auth token

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "COFE_CE6E"; // Enter your WiFi name
char pass[] = "Open@54321"; // Enter your WiFi password

// EEPROM addresses to store relay states
#define RELAY1_STATE_ADDR 0
#define RELAY2_STATE_ADDR 1
#define RELAY3_STATE_ADDR 2
#define RELAY4_STATE_ADDR 3

// Function to write relay state to EEPROM
void saveRelayState(int relayAddr, bool state) {
  EEPROM.write(relayAddr, state);
  EEPROM.commit();
}

// Function to read relay state from EEPROM
bool readRelayState(int relayAddr) {
  return EEPROM.read(relayAddr);
}

// Get the button values for relay1
BLYNK_WRITE(V0) {
  bool value1 = param.asInt();
  digitalWrite(relay1, value1 ? LOW : HIGH); // Update relay state
  saveRelayState(RELAY1_STATE_ADDR, value1); // Save state to EEPROM
}

// Get the button values for relay2
BLYNK_WRITE(V2) {
  bool value2 = param.asInt();
  digitalWrite(relay2, value2 ? LOW : HIGH); // Update relay state
  saveRelayState(RELAY2_STATE_ADDR, value2); // Save state to EEPROM
}
BLYNK_WRITE(V3) {
  bool value3 = param.asInt();
  digitalWrite(relay3, value3 ? LOW : HIGH); // Update relay state
  saveRelayState(RELAY3_STATE_ADDR, value3); // Save state to EEPROM
}
BLYNK_WRITE(V4) {
  bool value4 = param.asInt();
  digitalWrite(relay4, value4 ? LOW : HIGH); // Update relay state
  saveRelayState(RELAY4_STATE_ADDR, value4); // Save state to EEPROM
}

void setup() {
  // Initialize EEPROM with size 512 bytes
  EEPROM.begin(512);

  // Set the relay pins as output pins
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // Restore relay states from EEPROM
  digitalWrite(relay1, readRelayState(RELAY1_STATE_ADDR) ? LOW : HIGH);
  digitalWrite(relay2, readRelayState(RELAY2_STATE_ADDR) ? LOW : HIGH);
  digitalWrite(relay3, readRelayState(RELAY3_STATE_ADDR) ? LOW : HIGH);
  digitalWrite(relay4, readRelayState(RELAY4_STATE_ADDR) ? LOW : HIGH);

  // Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  // Run the Blynk library
  Blynk.run();
}
