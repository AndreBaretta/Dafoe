import './SalesHistory.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';

function SalesHistory() {
   const [salesHistory, setSalesHistory] = useState([]);

   useEffect(() => {
      const fetchSalesHistory = async () => {
         try {
            const salesResponse = await fetch('https://localhost:12354/api/order', {
               headers: { "Content-Type": "application/json", "token": localStorage.getItem('token') },
            });
            const salesData = await salesResponse.json();
            setSalesHistory(salesData);
         } catch (error) {
            console.error("Error fetching sales history:", error);
         }
      };

      fetchSalesHistory();
   }, []);

   const getClientName = (id) => {
      // You might need to fetch clients similarly to how you did in Sales.js
      return "Client Name"; // Replace with actual client name fetching logic
   };

   return (
      <div className="SalesHistory">
         <header className="Menu-header">
            <Sidebar />
            <Menu />
         </header>

         <div className="SalesHistory-content">
            <h2>Histórico de Vendas</h2>
            {salesHistory.length > 0 ? (
               <table>
                  <thead>
                     <tr>
                        <th>ID</th>
                        <th>Cliente</th>
                        <th>Total</th>
                        <th>Data</th>
                     </tr>
                  </thead>
                  <tbody>
                     {salesHistory.map((sale, index) => (
                        <tr key={index}>
                           <td>{sale.id}</td>
                           <td>{getClientName(sale.clientId)}</td>
                           <td>{sale.price}</td>
                           <td>{new Date(sale.createdAt).toLocaleDateString()}</td>
                        </tr>
                     ))}
                  </tbody>
               </table>
            ) : (
               <p>Nenhuma venda encontrada.</p>
            )}
         </div>
      </div>
   );
}

export default SalesHistory;
