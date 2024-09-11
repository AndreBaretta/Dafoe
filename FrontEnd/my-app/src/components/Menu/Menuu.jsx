// Menu.js
import React from 'react';
import { Link } from 'react-router-dom';
import './Menu.css';
import UserIcon from '../UserIcon/UserIcon';

function Menu() {
   return (
      <div className="Menu">
         <div className="UserIconWrapper">
            <UserIcon
               onClick={() => window.location.href = '/user'}
            />
         </div>
         <div className="MenuItem">
            <Link to="/sales">
               <div className="Menu-icon">📈</div>
               <span>Vendas</span>
            </Link>
         </div>
         <div className="MenuItem">
            <Link to="/clients">
               <div className="Menu-icon">👥</div>
               <span>Clientes</span>
            </Link>
         </div>
         <div className="MenuItem">
            <Link to="/stock">
               <div className="Menu-icon">📦</div>
               <span>Estoque</span>
            </Link>
         </div>
         <div className="MenuItem">
            <Link to="/employee">
               <div className="Menu-icon">🧑‍💼</div>
               <span>Funcionários</span>
            </Link>
         </div>
         <div className="MenuItem">
            <Link to="/manufacturer">
               <div className="Menu-icon">🏭</div>
               <span>Fabricantes</span>
            </Link>
         </div>
         <div className="MenuItem">
            <Link to="/general">
               <div className="Menu-icon">🌐</div>
               <span>Geral</span>
            </Link>
         </div>
         <div className="MenuItem">
            <Link to="/saleshistory">
               <div className="Menu-icon">🌐</div>
               <span>Histórico</span>
            </Link>
         </div>
      </div>
   );
}

export default Menu;
