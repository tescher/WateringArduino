// Automatic watering system
// (C) 2015 Tim Escher

#define ZONES 2
#define PAUSE 20*60*1000 // In milliseconds

struct zoneConfig {
  byte pumpHiPin;
  byte pumpLoPin;
  byte moisturePin;
  unsigned int moistureTrigger; // 0-1023
  unsigned int pumpTime;  // In seconds
};
struct zoneConfig zones[ZONES];

void pump_off(struct zoneConfig zone) {
  digitalWrite(zone.pumpHiPin,LOW);
  digitalWrite(zone.pumpLoPin,LOW);
};

void pump_on(struct zoneConfig zone) {
  digitalWrite(zone.pumpHiPin,HIGH);
  digitalWrite(zone.pumpLoPin,LOW);
};

void setup() {
  
  Serial.begin(9600);
  
  // Initialize the zone configs and pumps
  
  byte zone;
  
  // Zone 0
  zone = 0;
  zones[zone].pumpHiPin = 3;
  pinMode(zones[zone].pumpHiPin,OUTPUT);
  zones[zone].pumpLoPin = 4;
  pinMode(zones[zone].pumpLoPin,OUTPUT);
  zones[zone].moistureTrigger = 300;
  zones[zone].moisturePin = 0;
  zones[zone].pumpTime = 20;
  
  // Zone 1
  zone = 1;
  zones[zone].pumpHiPin = 5;
  pinMode(zones[zone].pumpHiPin,OUTPUT);
  zones[zone].pumpLoPin = 6;
  pinMode(zones[zone].pumpLoPin,OUTPUT);
  zones[zone].moistureTrigger = 300;
  zones[zone].moisturePin = 1;
  zones[zone].pumpTime = 20;
  
  // Turn off all pumps
  for(zone=0; zone<ZONES; zone++) {
    pump_off(zones[zone]);
  }
 
}

void loop() {
  for (byte zone=0; zone<ZONES; zone++) {
    pump_on(zones[zone]);
    delay(5000);
    pump_off(zones[zone]);
    delay(1000);
    Serial.print("Zone ");
    Serial.print(zone);
    Serial.print(": ");
    Serial.println(analogRead(zones[zone].moisturePin));
  }

}
