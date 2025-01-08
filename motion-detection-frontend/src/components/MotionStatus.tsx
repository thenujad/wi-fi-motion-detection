import React, { useEffect, useState } from 'react';
import { getMotionStatus } from '../services/api';

const MotionStatus: React.FC = () => {
    const [motionDetected, setMotionDetected] = useState<boolean>(false);
    const [loading, setLoading] = useState<boolean>(true);

    useEffect(() => {
        const fetchData = async () => {
            try {
                const status = await getMotionStatus();
                setMotionDetected(status);
            } catch (error) {
                console.error('Error fetching motion status:', error);
            } finally {
                setLoading(false);
            }
        };
        fetchData();
    }, []);

    if (loading) return <p>Loading...</p>;

    return (
        <div>
            <h2>Motion Detection Status</h2>
            <p>{motionDetected ? 'Motion Detected!' : 'No Motion Detected'}</p>
        </div>
    );
};

export default MotionStatus;
