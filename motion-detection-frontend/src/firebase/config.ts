import { initializeApp } from "firebase/app";
import { getDatabase, ref, set } from "firebase/database";
import { getAuth, signInAnonymously } from "firebase/auth";

// Your Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyB9Iozkn0yr4u6F5LT6ioOf9md1CcmcmQk", // Get this from Firebase Console
  authDomain: "iot-cw-1cb83.firebaseapp.com", // Firebase project auth domain
  databaseURL: "https://iot-cw-1cb83-default-rtdb.firebaseio.com", // Firebase Realtime Database URL
  projectId: "iot-cw-1cb83",
  storageBucket: "iot-cw-1cb83.firebasestorage.app",
  messagingSenderId: "529878475692",
  appId: "1:529878475692:web:c76d7139f8107269dd9009"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);

// Get references for services you need
const database = getDatabase(app);
const auth = getAuth(app);

// Optional: Sign in anonymously (useful for prototype apps)
signInAnonymously(auth).catch((error) => {
  const errorCode = error.code;
  const errorMessage = error.message;
  console.error(errorCode, errorMessage);
});

// Example: Write data to Firebase
export const writeData = (path: string, value: boolean) => {
  const dbRef = ref(database, path);
  set(dbRef, value).catch((error) => console.error(error));
};

export default app;
