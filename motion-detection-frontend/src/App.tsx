import React from 'react';
import MotionStatus from './components/MotionStatus';

const App: React.FC = () => {
    return (
      <>
        <div style={{ textAlign: 'center', marginTop: '50px' }}>
            <h1>Wi-Fi-Based Motion Detection System</h1>
            <MotionStatus />
        </div>
        </>
    );
};

export default App;
