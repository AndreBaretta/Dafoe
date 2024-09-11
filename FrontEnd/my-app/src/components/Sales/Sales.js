// Sales.js
import './Sales.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';
import Select from 'react-select';

function Sales() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [clients, setClients] = useState([]);
   const [sellers, setSellers] = useState([]);
   const [statuses, setStatuses] = useState([]);
   const [products, setProducts] = useState([]);
   const [paymentMethods, setPaymentMethods] = useState([]);
   const [newSaleScreen, setNewSaleScreen] = useState(false);
   const [editSaleScreen, setEditSaleScreen] = useState(false);
   const [deleteSaleScreen, setDeleteSaleScreen] = useState(false);
   const [selectedSale, setSelectedSale] = useState(null);
   const [saleDetails, setSaleDetails] = useState({
      clientId: '',
      sellerId: '',
      statusId: '',
      paymentMethodId: '',
      date: '',
      price: '',
      productId: '',
      quantity: ''
   });
   const [sortOrder, setSortOrder] = useState({
      clientId: 'asc',
      sellerId: 'asc',
      date: 'asc',
      price: 'asc'
   });
   const [isPending, setIsPending] = useState(false);

   const addProduct = (productId, quantity) => {
      setSaleDetails(prevState => ({
         ...prevState,
         products: [...prevState.products, { productId, quantity }]  // Adiciona o produto com quantidade
      }));
   };

   useEffect(() => {
      const fetchData = async () => {
         try {
            const salesResponse = await fetch(`https://localhost:12354/api/order`, {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const salesData = await salesResponse.json();
            setResults(salesData);

            const clientsResponse = await fetch(`https://localhost:12354/api/client`, {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const clientsData = await clientsResponse.json();
            setClients(clientsData);

            const sellersResponse = await fetch('https://localhost:12354/api/employee', {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const sellersData = await sellersResponse.json();
            setSellers(sellersData);

            const productsResponse = await fetch('https://localhost:12354/api/product', {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const productsData = await productsResponse.json();
            setProducts(productsData);

            const statusesResponse = await fetch('https://localhost:12354/api/status', {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const statusesData = await statusesResponse.json();
            setStatuses(statusesData);

            const paymentMethodsResponse = await fetch('https://localhost:12354/api/payment-method', {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const paymentMethodsData = await paymentMethodsResponse.json();
            setPaymentMethods(paymentMethodsData);
         } catch (error) {
            console.error(error);
         }
      };

      fetchData();
   }, [searchValue]);

   const resetSaleDetails = () => {
      setSaleDetails({
         clientId: '',
         sellerId: '',
         statusId: '',
         paymentMethodId: '',
         date: '',
         price: ''
      });
      setSelectedSale('');
   };

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setSaleDetails(prevState => ({
         ...prevState,
         [name]: value
      }));
   };

   const handleEditClick = (sale) => {
      setSaleDetails({
         clientId: sale.clientId,
         sellerId: sale.sellerId,
         statusId: sale.statusId,
         paymentMethodId: sale.paymentMethodId,
         date: sale.date,
         price: sale.price
      });
      setSelectedSale(sale.id);
      setEditSaleScreen(true);
   };

   const styles = {
      productCard: {
         border: '1px solid #ccc',
         padding: '16px',
         margin: '8px 0',
         borderRadius: '8px',
         backgroundColor: '#f9f9f9',
      }
   };
   
   const handleSort = (key) => {
      const order = sortOrder[key] === 'asc' ? 'desc' : 'asc';

      const sortedResults = [...results].sort((a, b) => {
         if (order === 'asc') {
            return a[key] > b[key] ? 1 : -1;
         } else {
            return a[key] < b[key] ? 1 : -1;
         }
      });

      setResults(sortedResults);
      setSortOrder({ ...sortOrder, [key]: order });
   };

   const handleDelete = async () => {
      try {
         await fetch(`https://localhost:12354/api/order/${selectedSale}`, {
            method: 'DELETE',
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
         });
         console.log('Venda deletada');
         setEditSaleScreen(false);
         setDeleteSaleScreen(false);
         setSelectedSale(null);
         const response = await fetch(`https://localhost:12354/api/order`, {
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
         });
         const data = await response.json();
         setResults(data);
         setIsPending(false);
         setNewSaleScreen(false);
         setEditSaleScreen(false);
         resetSaleDetails();
         setSelectedSale(null);
      } catch (error) {
         console.error('Erro ao deletar:', error);
      }
   };

   const submitData = async () => {
      try {
         setIsPending(true);
         if (selectedSale) {
            await fetch(`https://localhost:12354/api/sales/${selectedSale}`, {
               method: 'PUT',
               headers: { 
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token') 
               },
               body: JSON.stringify(
                  saleDetails,
               )
            });
            console.log("Venda atualizada");
            setSelectedSale(null); 
         } else {
            await fetch('https://localhost:12354/api/sales', {
               method: 'POST',
               headers: { 
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token') 
               },
               body: JSON.stringify({
                  ...saleDetails,
                  clientId: String(saleDetails.clientId),
                  Product: String(saleDetails.productId),
                  paymentMethod: String(saleDetails.paymentMethodId),
                  quantity: String(saleDetails.quantity),
                  price: String(saleDetails.price)
               }),
            });
            console.log("Venda adicionada");
         }
         setIsPending(false);
         setNewSaleScreen(false);
         setEditSaleScreen(false);
         resetSaleDetails();
         const response = await fetch(`https://localhost:12354/api/order`, {
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
         });
         const data = await response.json();
         setResults(data);
      } catch (error) {
         console.error(error);
         setIsPending(false);
      }
   };

   const getClientName = (id) => {
      const client = clients.find(c => c.id === id);
      return client ? client.name : 'N/A';
   };

   const getProductName = (id) => {
      const product = products.find(p => p.id === id);
      return product ? product.name : 'N/A';
   };

   const getSellerName = (id) => {
      const seller = sellers.find(s => s.id === id);
      return seller ? seller.name : 'N/A';
   };

   const getStatusName = (id) => {
      const status = statuses.find(st => st.id === id);
      return status ? status.name : 'N/A';
   };

   const getPaymentMethodName = (id) => {
      const paymentMethod = paymentMethods.find(pm => pm.id === id);
      return paymentMethod ? paymentMethod.name : 'N/A';
   };

   return (
      <div className="Sales">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="button-container">
               <button className="newSaleButton" onClick={() => setNewSaleScreen(true)}>Nova Venda</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Sales-table-container">
            <table className="Sales-table">
               <thead>
                  <tr>
                     <th>Produto<button onClick={() => handleSort('productName')}>{sortOrder.getProductName === 'asc' ? '↑' : '↓' }</button></th>
                     <th>Quantidade<button onClick={() => handleSort('quantidade')}>{sortOrder.quantity === 'asc' ? '↑' : '↓' }</button></th>
                     <th>Cliente <button onClick={() => handleSort('clientId')}>{sortOrder.clientId === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Vendedor <button onClick={() => handleSort('sellerId')}>{sortOrder.sellerId === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Data <button onClick={() => handleSort('date')}>{sortOrder.date === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Preço <button onClick={() => handleSort('price')}>{sortOrder.price === 'asc' ? '↑' : '↓'}</button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.length > 0 ? (
                     results.map(sale => (
                        <tr key={sale.id} onClick={() => handleEditClick(sale)}>
                           <td>{getClientName(sale.clientId)}</td>
                           <td>{getSellerName(sale.sellerId)}</td>
                           <td>{getStatusName(sale.statusId)}</td>
                           <td>{getProductName(sale.productId)}</td>
                           <td>{sale.date}</td>
                           <td>{sale.price}</td>
                        </tr>
                     ))
                  ) : (
                     <tr>
                        <td colSpan="4">Nenhuma venda encontrada.</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal for editing or creating sales */}
         <Model isOpen={newSaleScreen || editSaleScreen}>
            <div>
               <h2>{selectedSale ? "Editar Venda" : "Nova Venda"}</h2>
               <form onSubmit={submitData}>
                  <div>
                     <label>Cliente</label>
                     <Select
                        options={clients.map(c => ({ value: c.id, label: c.name }))}
                        onChange={(selectedOption) => setSaleDetails(prevState => ({ ...prevState, clientId: selectedOption.value }))}
                        value={sellers.find(c => c.id === saleDetails.clientId) ? { value: saleDetails.clientId, label: clients.find(c => c.id === saleDetails.clientId).name } : null}
                     />
                  </div>
                  <div>
                     <label>Método de Pagamento</label>
                     <Select
                        options={paymentMethods.map(paymentMethod => ({ value: paymentMethod.id, label: paymentMethod.name }))}
                        value={paymentMethods.find(paymentMethod => paymentMethod.id === saleDetails.paymentMethodId)}
                        onChange={selectedOption => setSaleDetails(prevState => ({ ...prevState, paymentMethodId: selectedOption.value }))}
                     />
                  </div>
                  <div>
                     <label>Produto</label>
                     <Select
                        options={products.map(p => ({ value: p.id, label: p.name}))}
                        value={products.find(p => p.id === saleDetails.productId)}
                        onChange={selectedOption => setSaleDetails(prevState => ({ ...prevState, productId: selectedOption.value}))}
                     />
                  </div>
                  <div>
                     <button type="submit">{selectedSale ? "Salvar" : "Criar"}</button>
                     <button onClick={() => {
                        submitData();
                        resetSaleDetails();
                        setNewSaleScreen(false);
                        setEditSaleScreen(false);
                     }}>Cancelar</button>
                  </div>
               </form>
            </div>
         </Model>
      </div>
   );
}

export default Sales;


