import React from 'react';
import './Menu.css';
import UserIcon from '../UserIcon/UserIcon'; // Import the UserIcon component

function Menu() {
   const handleUserIconClick = () => {
      // Handle user icon click, e.g., open user profile or settings
      window.open('http://localhost:3000?user', '_self');
   };

   return (
      <div className="Menu">
         <div className="UserIconWrapper">
            <UserIcon 
               onClick={handleUserIconClick} 
            />
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?sales', '_self')}></button>
            <div className="Menu-icon">📈</div>
            <span>Vendas</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?clients', '_self')}></button>
            <div className="Menu-icon">👥</div>
            <span>Clientes</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?stock', '_self')}></button>
            <div className="Menu-icon">📦</div>
            <span>Estoque</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?employee', '_self')}></button>
            <div className="Menu-icon">🧑‍💼</div>
            <span>Funcionários</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?manufacturer', '_self')}></button>
            <div className="Menu-icon">🏭</div>
            <span>Fabricantes</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?general', '_self')}></button>
            <div className="Menu-icon">🌐</div>
            <span>Geral</span>
         </div>
      </div>
   )
}

export default Menu;
