#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Wi-Fi credentials
#define WIFI_SSID "HUAWEI Y7a"              // Your Wi-Fi SSID
#define WIFI_PASSWORD "12345678"            // Your Wi-Fi password

// Firebase project credentials
#define FIREBASE_PROJECT_ID "iot-motion-app"  // Your Firebase project ID
#define FIREBASE_API_KEY "AIzaSyDF3BzX13uilp4W0EK0f222LW4salTv1tE"     // Your Firebase API key

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// GPIO pins
const int pirPin = 13;
const int led_01_Pin = 2;

void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(pirPin, INPUT);
  pinMode(led_01_Pin, OUTPUT);

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

  // Anonymous authentication (No need for a UID)
  auth.token.uid = ""; // Leave it empty for anonymous login

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Serial.println("Firebase initialized");
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected) {
    Serial.println("Motion detected!");
    digitalWrite(led_01_Pin, HIGH);

    // Update Firebase with motion status
    if (Firebase.RTDB.setBool(&fbdo, "/motionDetected", true)) {
      Serial.println("Data sent to Firebase");
    } else {
      Serial.println("Failed to send data to Firebase");
      Serial.println(fbdo.errorReason());
    }
  } else {
    digitalWrite(led_01_Pin, LOW);

    // Update Firebase with motion status
    if (!Firebase.RTDB.setBool(&fbdo, "/motionDetected", false)) {
      Serial.println("Failed to send data to Firebase");
      Serial.println(fbdo.errorReason());
    }
  }

  delay(1000); // Delay for stability
}
