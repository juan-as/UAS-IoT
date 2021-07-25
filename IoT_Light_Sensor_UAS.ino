
//Juan Augusto || 2301880471
//UAS IoT
//Selasa, 27 July 2021
//IoT 2.b
//Simple MQTT Program

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTEthernet.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = " value username dari cayenne";
char password[] = " value password dari cayenne ";
char clientID[] = " value id dari cayenne";

#define SENSOR_PIN 0
#define LED_PIN 3
#define VIRTUAL_CHANNEL 4

int value;

#define ACTUATOR_PIN 4 // Do not use digital pins 0 or 1 since those conflict with the use of Serial.


void setup()
{
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID);
  pinMode(LED_PIN, OUTPUT);

    pinMode(ACTUATOR_PIN, OUTPUT);

}

void loop()
{
  value = analogRead(SENSOR_PIN);
  Serial.print("Sensor LDR: ");
  Serial.println(value);

      if (value < 80) {
    digitalWrite(LED_PIN, HIGH);
        digitalWrite(ACTUATOR_PIN, LOW);

  }
  else {
    digitalWrite(LED_PIN, LOW);
        digitalWrite(ACTUATOR_PIN, HIGH);

  }
  
  Cayenne.loop();
}

// This function is called when data is sent from Cayenne.
CAYENNE_IN(VIRTUAL_CHANNEL)
{
  // Write value to turn the relay switch on or off. This code assumes you wire your relay as normally open.
  if (getValue.asInt() == 0) {
    digitalWrite(ACTUATOR_PIN, HIGH);
  }
  else {
    digitalWrite(ACTUATOR_PIN, LOW);
  }
}



// This function is called at intervals to send sensor data to Cayenne.
CAYENNE_OUT(VIRTUAL_CHANNEL)
{
  Cayenne.virtualWrite(VIRTUAL_CHANNEL, analogRead(SENSOR_PIN), "analog_sensor", "null");


    CAYENNE_LOG("Send data for Virtual Channel 0");
  // This command writes the device's uptime in seconds to the Virtual Channel. 
  Cayenne.virtualWrite(0, millis() / 1000);
}
