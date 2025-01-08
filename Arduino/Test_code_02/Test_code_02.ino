#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Provide the Wi-Fi credentials
#define WIFI_SSID "HP-GTR-Network"
#define WIFI_PASSWORD "123456789"

// Firebase project credentials
#define FIREBASE_PROJECT_ID "iot-cw-1cb83"
#define FIREBASE_API_KEY "AIzaSyB9Iozkn0yr4u6F5LT6ioOf9md1CcmcmQk"
#define FIREBASE_AUTH_TOKEN "Your_Auth_Token"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// GPIO pins
const int pirPin = 4;
const int ledPin = 2;

void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Firebase configuration
  config.api_key = FIREBASE_API_KEY;
  config.database_url = "https://" FIREBASE_PROJECT_ID ".firebaseio.com";

  // Authentication (using Auth token or Anonymous login)
  auth.token.uid = FIREBASE_AUTH_TOKEN;

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Serial.println("Firebase initialized");
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected) {
    Serial.println("Motion detected!");
    digitalWrite(ledPin, HIGH);

    // Update Firebase
    if (Firebase.RTDB.setBool(&fbdo, "/motionDetected", true)) {
      Serial.println("Data sent to Firebase");
    } else {
      Serial.println("Failed to send data to Firebase");
      Serial.println(fbdo.errorReason());
    }
  } else {
    digitalWrite(ledPin, LOW);

    if (!Firebase.RTDB.setBool(&fbdo, "/motionDetected", false)) {
      Serial.println("Failed to send data to Firebase");
      Serial.println(fbdo.errorReason());
    }
  }

  delay(1000); // Delay for stability
}
