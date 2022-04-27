//########## Constants ###################

const String googleAppUrl = "/macros/s/AKfycbyCdSBLHyV7GjInejM9eof4OCwlxF06YWlaEQBFFmabnXz2tM6Do-DWoxg13AsY3Rg/exec";
#define DHT_PIN D1
#define B20_PIN_4 D3
#define B20_PIN_5 D4
#define DT_4    D0      // Pin PWM per bilancia 2
#define SCK_4   D5      // Pin PWM per bilancia 2
#define DT_5    D7      // Pin PWM per bilancia 3
#define SCK_5   D6      // Pin PWM per bilancia 3
#define LED     D8      // Led luminoso segnalazione

#define calibration_factor_4 -22060.0
#define offset_4 -673388
#define calibration_factor_5 -21180.0
#define offset_5 380414

//########## Libaries ##################
#include "Zwifi.h"
#include "Zrecord.h"
#include "Zclient.h"
#include "Zsensors.h"

//########## Objects #####################
Records records;
Zclient zclient;
Zwifi zwifi;
Zsensors zsensors;

//########## Setup #######################
void setup() {
  Serial.begin(115200);
  Serial.println("Starting the setup\n");
  
  Serial.println("Setup WiFi...\n");
  zwifi.setup();
  Serial.println("Connecting to WiFi...");
  if (!zwifi.connect()) return; // If not able to connect restart
  
  Serial.println("Setup client...\n");
  zclient.setup();
}


//########## Loop ########################
void loop() {
  
  //This is how the cycle should look like:
  //Once evry while:
    //Reconnect wifi
    zwifi.connect();
    //Get all measures updated
    zsensors.updateMeasures();

    //Add all measures to a queue
    if (!records.addRecord(zsensors.getMeasuresRecord())) Serial.println("Not able to add to records... Probably full!");
    else Serial.println("Added new records to the ones to send, now at: " + String(records.toSend));

    //Connect to wifi
    if (!zwifi.connect()){
      Serial.println("Unable to connect to wifi");
      //Do someting since you was not able to connect
    }

    else {
      //Connect to client
      if (zclient.connect()){
        //Send the data
        //Read response
        Serial.println("Making a new request:");
        zclient.send(records, "Today");
        //Dequeue the data sent
        records.clear();
      }
      else {
        Serial.println("Unable to connect to the client");
        //Do something since you was not able to reach the client
      }
    } 
    //Wifi sleep N.B: this is almost 10s lost
    Serial.println("Going to sleep");
    zwifi.sleep(10*60*1000);
    Serial.println("Waking up");
  //sleep/keep
}