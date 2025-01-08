import React, { useState, useEffect } from "react";
import { writeData } from "../firebase/config";

const MotionDetection = () => {
  const [motionDetected, setMotionDetected] = useState(false);

  useEffect(() => {
    // Simulate motion detection (or integrate with your ESP32 here)
    const motionInterval = setInterval(() => {
      setMotionDetected((prev) => !prev);
    }, 5000);

    return () => clearInterval(motionInterval);
  }, []);

  useEffect(() => {
    // Update Firebase when motion is detected
    writeData("/motionDetected", motionDetected);
  }, [motionDetected]);

  return (
    <div>
      <h2>Motion Detection</h2>
      <p>{motionDetected ? "Motion Detected!" : "No Motion"}</p>
    </div>
  );
};

export default MotionDetection;
