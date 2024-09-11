import './SalesHistory.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function SalesHistory() {
   const [sales, setSales] = useState([]);
   const [clients, setClients] = useState([]);
   const [selectedSale, setSelectedSale] = useState(null);
   const [editSaleScreen, setEditSaleScreen] = useState(false);
   const [isPending, setIsPending] = useState(false);
   const [sortOrder, setSortOrder] = useState({
      date: 'asc',
      clientName: 'asc',
      price: 'asc',
   });
   const [products, setProducts] = useState([]);
   const [error, setError] = useState(null);

   // Fetch sales and clients data
   useEffect(() => {
      const fetchSalesAndClients = async () => {
         try {
            const [salesResponse, clientsResponse] = await Promise.all([
               fetch('https://localhost:12354/api/order', {
                  method: 'GET',
                  headers: {
                     "Content-Type": "application/json",
                     "token": localStorage.getItem('token'),
                  },
               }),
               fetch('https://localhost:12354/api/client', {
                  method: 'GET',
                  headers: {
                     "Content-Type": "application/json",
                     "token": localStorage.getItem('token'),
                  },
               }),
            ]);
            if (!salesResponse.ok || !clientsResponse.ok) {
               throw new Error('Failed to fetch data');
            }
            const salesData = await salesResponse.json();
            const clientsData = await clientsResponse.json();
            setSales(sortSales(salesData, 'id', 'desc')); // Sort sales initially
            setClients(clientsData);
         } catch (error) {
            console.error('Error fetching sales or clients:', error);
            setError('Failed to fetch sales or clients');
         }
      };

      fetchSalesAndClients();
   }, []);

   const sortSales = (salesData, key, order) => {
      return [...salesData].sort((a, b) => {
         if (order === 'desc') {
            if (key === 'date') {
               return new Date(b[key]) - new Date(a[key]);
            }
            return b[key] > a[key] ? 1 : -1;
         } else {
            if (key === 'date') {
               return new Date(a[key]) - new Date(b[key]);
            }
            return a[key] > b[key] ? 1 : -1;
         }
      });
   };

   const handleRowClick = (sale) => {
      setSelectedSale(sale);
      fetchProducts(sale.id);
      setEditSaleScreen(true);
   };

   const fetchProducts = async (saleId) => {
      try {
         const response = await fetch(`https://localhost:12354/api/order/${saleId}`, {
            method: 'GET',
            headers: {
               "Content-Type": "application/json",
               "token": localStorage.getItem('token'),
            },
         });

         if (!response.ok) {
            throw new Error('Failed to fetch products');
         }

         const data = await response.json();
         console.log('Fetched products:', data); // Check if data is correct

         // Assuming data is an object, convert it to an array
         const productsArray = Object.values(data);
         setProducts(productsArray);
      } catch (error) {
         console.error('Error fetching products:', error);
         setError('Failed to fetch products');
      }
   };

   const handleSort = (key) => {
      const order = sortOrder[key] === 'asc' ? 'desc' : 'asc';

      const sortedSales = [...sales].sort((a, b) => {
         if (order === 'asc') {
            if (key === 'date') {
               return new Date(a[key]) - new Date(b[key]);
            }
            return a[key] > b[key] ? 1 : -1;
         } else {
            if (key === 'date') {
               return new Date(b[key]) - new Date(a[key]);
            }
            return a[key] < b[key] ? 1 : -1;
         }
      });

      setSales(sortedSales);
      setSortOrder({ ...sortOrder, [key]: order });
   };

   const handleUpdateSale = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/order/${selectedSale.id}`, {
            method: 'PUT',
            headers: {
               'Content-Type': 'application/json',
               'token': localStorage.getItem('token'),
            },
            body: JSON.stringify(selectedSale),
         });

         if (response.ok) {
            console.log('Sale updated successfully');
            setEditSaleScreen(false);
            // Refresh sales data
            const salesResponse = await fetch('https://localhost:12354/api/order', {
               headers: {
                  "Content-Type": "application/json",
                  "token": localStorage.getItem('token'),
               },
            });
            const data = await salesResponse.json();
            setSales(data);
         } else {
            console.error('Error updating sale');
         }
      } catch (error) {
         console.error('Error in request:', error);
      } finally {
         setIsPending(false);
      }
   };

   const handleDeleteSale = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/order/${selectedSale.id}`, {
            method: 'DELETE',
            headers: {
               "token": localStorage.getItem('token'),
            }
         });

         if (response.ok) {
            console.log('Sale deleted successfully');
            setEditSaleScreen(false);
            // Refresh sales data
            const salesResponse = await fetch('https://localhost:12354/api/order', {
               headers: {
                  "Content-Type": "application/json",
                  "token": localStorage.getItem('token'),
               },
            });
            const data = await salesResponse.json();
            setSales(data);
         } else {
            console.error('Error deleting sale');
         }
      } catch (error) {
         console.error('Error in request:', error);
      } finally {
         setIsPending(false);
      }
   };

   const getClientName = (id) => {
      const client = clients.find(c => c.id === id);
      return client ? client.name : 'Unknown';
   };

   const getProductName = (productId) => {
      const product = products.find(p => p.id === productId);
      return product ? product.name : 'Unknown';
   };

   return (
      <div className="SalesHistory">
         <header className="Menu-header">
            <Sidebar />
            <Menu />
         </header>
         <header className="SearchBarHeader">
            <div className="sales-button-container">
               {/* Optionally add buttons here if needed */}
            </div>
         </header>
         <div className="SalesHistory-table-container">
            <table className="SalesHistory-table">
               <thead>
                  <tr>
                     <th onClick={() => handleSort('id')}>Id</th>
                     <th onClick={() => handleSort('date')}>Data</th>
                     <th onClick={() => handleSort('clientName')}>Cliente</th>
                     <th onClick={() => handleSort('price')}>Preço Total</th>
                  </tr>
               </thead>
               <tbody>
                  {sales.length > 0 ? (
                     sales.map((sale) => (
                        <tr key={sale.id} onClick={() => handleRowClick(sale)}>
                           <td>{sale.id}</td>
                           <td>{new Date(sale.date).toLocaleDateString()}</td>
                           <td>{getClientName(sale.clientId)}</td>
                           <td>{sale.price}</td>
                        </tr>
                     ))
                  ) : (
                     <tr>
                        <td colSpan="4">No sales found</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal for displaying products in the selected sale */}
         <Model
            isOpen={!!selectedSale}
            onRequestClose={() => {
               setSelectedSale(null);
               setProducts([]);
            }}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => {
               setSelectedSale(null);
               setProducts([]);
            }}>X</button>
            <div className="ReactModal__Header">
               <h2>Venda de produtos</h2>
               {error && <p className="error-message">{error}</p>}
               <div className="Products-table-container">
                  <table className="Products-table">
                     <thead>
                        <tr>
                           <th>ID</th>
                           <th>Quantidade</th>
                           <th>Preço</th>
                        </tr>
                     </thead>
                     <tbody>
                        {products.length > 0 ? (
                           products.map((product) => (
                              <tr key={product.id}>
                                 <td>{product.product}</td>
                                 <td>{product.quantity}</td>
                                 <td>{product.price.toFixed(2)}</td>
                              </tr>
                           ))
                        ) : (
                           <tr>
                              <td colSpan="4">No products found</td>
                           </tr>
                        )}
                     </tbody>
                  </table>
               </div>
            </div>
         </Model>
      </div>
   );
}

export default SalesHistory;
