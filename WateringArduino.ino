// Automatic watering system
// (C) 2015 Tim Escher

#define ZONES 2
// #define PAUSE 5*1000 // In milliseconds
#define PAUSE 20L*60L*1000L // In milliseconds
#define MOISTURE_READS 10 // NUmber of reads of the moisture sensor to get rid of noise.

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

int moisture_level(struct zoneConfig zone) {
  int reading = 0;
  analogRead(zone.moisturePin);   // Discard first reading to allow settling.
  delay(50);
  for (byte i=0;i<MOISTURE_READS;i++) {
    reading += analogRead(zone.moisturePin);
    delay(50);
  }
  return reading / MOISTURE_READS;
}

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
  zones[zone].moistureTrigger = 600;
  zones[zone].moisturePin = 0;
  zones[zone].pumpTime = 20;
  
  // Zone 1
  zone = 1;
  zones[zone].pumpHiPin = 5;
  pinMode(zones[zone].pumpHiPin,OUTPUT);
  zones[zone].pumpLoPin = 6;
  pinMode(zones[zone].pumpLoPin,OUTPUT);
  zones[zone].moistureTrigger = 600;
  zones[zone].moisturePin = 1;
  zones[zone].pumpTime = 20;
  
  // Turn off all pumps
  for(zone=0; zone<ZONES; zone++) {
    pump_off(zones[zone]);
  }
 
}

void loop() {
  unsigned int moisture_reading;
  for (byte zone=0; zone<ZONES; zone++) {
    moisture_reading = moisture_level(zones[zone]);
    Serial.print("Zone ");
    Serial.print(zone);
    Serial.print(": ");
    Serial.println(moisture_reading);
    if (moisture_reading > zones[zone].moistureTrigger) {    // Higher moisture reading => drier
      Serial.println("pumping...");
      pump_on(zones[zone]);
      delay(zones[zone].pumpTime*1000);
      pump_off(zones[zone]);
    }  
  }
  delay(PAUSE);

}
