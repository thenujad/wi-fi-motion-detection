const express = require("express");
const motionDetectionRoute = require("./routes/motionDetection");

const app = express();
app.use(express.json()); // Middleware to parse JSON request bodies

// Use motion detection routes
app.use("/api", motionDetectionRoute);

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
