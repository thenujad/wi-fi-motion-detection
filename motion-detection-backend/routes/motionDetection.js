const express = require("express");
const { writeData } = require("../firebaseAdmin");
const router = express.Router();

router.post("/motion", (req, res) => {
  const motionDetected = req.body.motionDetected;

  // Write motion status to Firebase Realtime Database
  writeData("/motionDetected", motionDetected);

  res.status(200).send("Motion data updated in Firebase");
});

module.exports = router;
