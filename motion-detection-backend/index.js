const express = require("express");
const admin = require("firebase-admin");
const cors = require("cors");

const app = express();
app.use(cors());
app.use(express.json());

// Firebase setup
const serviceAccount = require("./serviceAccountKey.json");
admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://iot-motion-app-default-rtdb.firebaseio.com",
});
const db = admin.database();

// Endpoint to get motion data
app.get("/motion", async (req, res) => {
  const ref = db.ref("motionDetected");
  ref.once("value", (snapshot) => {
    res.send({ motionDetected: snapshot.val() });
  });
});

app.listen(3000, () => console.log("Server running on port 3000"));
