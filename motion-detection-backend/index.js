const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
const admin = require("firebase-admin");

// Initialize Firebase Admin SDK
const serviceAccount = require("./firebase-config.json");

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://iot-motion-app-default-rtdb.firebaseio.com/",
});

const db = admin.database();
const app = express();
const PORT = 5000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// Endpoint to get motion status
app.get("/motion-status", async (req, res) => {
  try {
    const ref = db.ref("motionDetected");
    ref.once("value", (snapshot) => {
      res.json({ motionDetected: snapshot.val() });
    });
  } catch (err) {
    res.status(500).json({ error: "Failed to fetch motion status" });
  }
});

// Endpoint to update motion status
app.post("/motion-status", async (req, res) => {
  const { motionDetected } = req.body;
  try {
    const ref = db.ref("motionDetected");
    ref.set(motionDetected, (error) => {
      if (error) {
        res.status(500).json({ error: "Failed to update motion status" });
      } else {
        res.json({ message: "Motion status updated successfully" });
      }
    });
  } catch (err) {
    res.status(500).json({ error: "Failed to update motion status" });
  }
});

app.listen(PORT, () => {
  console.log(`Backend running on http://localhost:${PORT}`);
});
