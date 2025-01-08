const admin = require("firebase-admin");

// Initialize Firebase Admin with your service account key
const serviceAccount = require("./serviceAccountKey.json");

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://iot-cw-1cb83-default-rtdb.firebaseio.com", // Firebase Realtime Database URL
});

// Firebase Realtime Database reference
const db = admin.database();

// Example: Write data to Firebase
const writeData = (path, value) => {
  const ref = db.ref(path);
  ref.set(value, (error) => {
    if (error) {
      console.error("Data could not be saved.", error);
    } else {
      console.log("Data saved successfully.");
    }
  });
};

module.exports = { writeData };
