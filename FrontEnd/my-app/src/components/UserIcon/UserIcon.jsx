import React from 'react';
import './UserIcon.css';

function UserIcon({ onClick, imageUrl }) {
   return (
      <div className="user-icon-container" onClick={onClick}>
         👤
      </div>
   );
}

export default UserIcon;
