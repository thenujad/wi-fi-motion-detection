import React, { useEffect, useState } from "react";
import axios from "axios";
import { FiActivity } from "react-icons/fi";

const MotionStatus: React.FC = () => {
  const [motionDetected, setMotionDetected] = useState<boolean>(false);

  useEffect(() => {
    // Fetch motion status from the backend
    const fetchMotionStatus = async () => {
      try {
        const response = await axios.get("http://localhost:5000/motion-status");
        setMotionDetected(response.data.motionDetected);
      } catch (error) {
        console.error("Error fetching motion status:", error);
      }
    };

    fetchMotionStatus();

    // Polling for real-time updates
    const interval = setInterval(fetchMotionStatus, 2000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div
      style={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        height: "100vh",
        flexDirection: "column",
        fontFamily: "Arial, sans-serif",
      }}
    >
      <h1 style={{ fontSize: "2rem", marginBottom: "1rem" }}>
        IoT Motion Dashboard
      </h1>
      <div
        style={{
          display: "flex",
          alignItems: "center",
          padding: "1rem",
          borderRadius: "8px",
          backgroundColor: motionDetected ? "#ff4d4d" : "#4caf50",
          color: "#fff",
          fontSize: "1.5rem",
          boxShadow: "0px 4px 10px rgba(0,0,0,0.2)",
        }}
      >
        <FiActivity size={30} style={{ marginRight: "0.5rem" }} />
        {motionDetected ? "Motion Detected!" : "No Motion"}
      </div>
    </div>
  );
};

export default MotionStatus;
