
/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP8266
 *
 * Copyright (c) 2023 mobizt
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


int led = 2;  // Number of GPIO that is connected to LED
String path = "Outputs/Digital/"; // path to LED on firebase Database 
// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "stc"
#define WIFI_PASSWORD "suthanhcon"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyAbPaKIi7XopVZKZ-tAp_XlDL5OVUpzNZk"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://test-esp8266-666e2-default-rtdb.asia-southeast1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "admin@gmail.com"
#define USER_PASSWORD "123456"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;


void setup()
{

  Serial.begin(115200);
  pinMode(led, OUTPUT);  
  digitalWrite(led, HIGH);     // make external led OFF

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);

  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);



  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

//    Serial.printf("Set bool... %s\n", Firebase.setBool(fbdo, F(path), count % 2 == 0) ? "ok" : fbdo.errorReason().c_str());

    
    Serial.printf("Get string... %s\n", Firebase.getString(fbdo, F("Outputs/Digital")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
    const char* fireStatus;
    fireStatus = Firebase.getString(fbdo, F("Outputs/Digital")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
//    Serial.printf("Get bool ref... %s\n", Firebase.getBool(fbdo, F("/test/bool"), &bVal) ? bVal ? "true" : "false" : fbdo.errorReason().c_str());
    Serial.printf(fireStatus);
    String ledStatus = String(fireStatus);
    if (ledStatus == "ON") 
    {    // compare the input of led status received from firebase
      Serial.println("Led Turned ON");       
      digitalWrite(led, LOW);       // make external led ON
    } 
    else if (ledStatus == "OFF") 
    {     // compare the input of led status received from firebase
      Serial.println("Led Turned OFF");
      digitalWrite(led, HIGH);     // make external led OFF
    }
    else 
    {
      Serial.println("Command Error! Please send ON/OFF");
      //Serial.println(fireStatus);
    }



    // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create_Parse_Edit.ino
//    FirebaseJson json;
//
//    if (count == 0)
//    {
//      json.set("value/round/" + String(count), F("cool!"));
//      json.set(F("vaue/ts/.sv"), F("timestamp"));
//      Serial.printf("Set json... %s\n", Firebase.set(fbdo, F("/test/json"), json) ? "ok" : fbdo.errorReason().c_str());
//    }
//    else
//    {
//      json.add(String(count), "smart!");
//      Serial.printf("Update node... %s\n", Firebase.updateNode(fbdo, F("/test/json/value/round"), json) ? "ok" : fbdo.errorReason().c_str());
//    }

    Serial.println();
//    count++;
  }
}
