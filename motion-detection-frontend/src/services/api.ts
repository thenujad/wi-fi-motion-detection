import axios from 'axios';

const api = axios.create({
    baseURL: 'http://localhost:3000', // Replace with your backend URL
});

export const getMotionStatus = async (): Promise<boolean> => {
    const response = await api.get('/motion');
    return response.data.motionDetected;
};
