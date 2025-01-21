#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Wi-Fi credentials
#define WIFI_SSID "HUAWEI Y7a"
#define WIFI_PASSWORD "12345678"

// Firebase credentials
#define API_KEY "AIzaSyDF3BzX13uilp4W0EK0f222LW4salTv1tE"
#define DATABASE_URL "https://iot-motion-app-default-rtdb.firebaseio.com/"

// Define GPIO pins
const int pirPin = 13;   // PIR sensor pin
const int ledPin = 2;    // LED pin

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool motionDetected = false;
bool signupOK = false;

void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Firebase configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Firebase signup
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Sign-Up Successful");
    signupOK = true;
  } else {
    Serial.printf("Firebase Sign-Up Failed: %s\n", config.signer.signupError.message.c_str());
  }

  // Token status callback
  config.token_status_callback = tokenStatusCallback;

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase initialized");
}

void loop() {
  if (Firebase.ready() && signupOK) {
    // Read PIR sensor
    motionDetected = digitalRead(pirPin);

    if (motionDetected) {
      Serial.println("Motion detected!");
      digitalWrite(ledPin, HIGH); // Turn on the LED

      // Update Firebase with motion status
      if (Firebase.RTDB.setBool(&fbdo, "/motionDetected", true)) {
        Serial.println("Motion status updated to Firebase: true");
      } else {
        Serial.printf("Failed to update Firebase: %s\n", fbdo.errorReason().c_str());
      }
    } else {
      digitalWrite(ledPin, LOW); // Turn off the LED

      // Update Firebase with motion status
      if (Firebase.RTDB.setBool(&fbdo, "/motionDetected", false)) {
        Serial.println("Motion status updated to Firebase: false");
      } else {
        Serial.printf("Failed to update Firebase: %s\n", fbdo.errorReason().c_str());
      }
    }

    // Delay for stability
    delay(1000);
  }
}
