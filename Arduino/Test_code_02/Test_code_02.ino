#include <WiFi.h>
#include <FirebaseESP32.h>

// Wi-Fi credentials
#define WIFI_SSID "Your_SSID"
#define WIFI_PASSWORD "Your_Password"

// Firebase credentials
#define FIREBASE_HOST "https://iot-cw-1cb83-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Your_Firebase_Database_Secret"

// Firebase objects
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;
FirebaseData firebaseData;

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

  // Configure Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.api_key = FIREBASE_AUTH;
  firebaseConfig.token_status_callback = tokenStatusCallback; // Optional

  Firebase.begin(&firebaseConfig, &firebaseAuth);

  Serial.println("Firebase initialized");
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected) {
    Serial.println("Motion detected!");
    digitalWrite(ledPin, HIGH);

    // Update Firebase
    if (Firebase.RTDB.setBool(&firebaseData, "/motionDetected", true)) {
      Serial.println("Data sent to Firebase");
    } else {
      Serial.println("Failed to send data to Firebase");
      Serial.println(firebaseData.errorReason());
    }
  } else {
    digitalWrite(ledPin, LOW);
    Firebase.RTDB.setBool(&firebaseData, "/motionDetected", false);
  }

  delay(1000); // Delay for stability
}
