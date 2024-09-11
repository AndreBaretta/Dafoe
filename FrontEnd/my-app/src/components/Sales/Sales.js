import './Sales.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Select from 'react-select';

function Sales() {
   const [clients, setClients] = useState([]);
   const [products, setProducts] = useState([]);
   const [paymentMethods, setPaymentMethods] = useState([]);
   const [saleDetails, setSaleDetails] = useState({
      clientId: '',
      paymentMethodId: '',
      products: [],
   });
   const [totalPrice, setTotalPrice] = useState(0);

   useEffect(() => {
      const fetchData = async () => {
         try {
            const clientsResponse = await fetch(`https://localhost:12354/api/client`, {
               headers: { "Content-Type": "application/json", "token" : localStorage.getItem('token') },
            });
            const clientsData = await clientsResponse.json();
            setClients(clientsData);

            const productsResponse = await fetch('https://localhost:12354/api/product', {
               headers: { "Content-Type": "application/json", "token" : localStorage.getItem('token') },
            });
            const productsData = await productsResponse.json();
            setProducts(productsData);

            const paymentMethodsResponse = await fetch('https://localhost:12354/api/payment-method', {
               headers: { "Content-Type": "application/json", "token" : localStorage.getItem('token') },
            });
            const paymentMethodsData = await paymentMethodsResponse.json();
            setPaymentMethods(paymentMethodsData);
         } catch (error) {
            console.error(error);
         }
      };

      fetchData();
   }, []);

   const addProduct = (productId, quantity) => {
      const product = products.find(p => p.id === productId);
      if (product) {
         if (quantity > product.quantity) {
            alert(`A quantidade escolida: ${quantity} excede o limite em estoque: (${product.quantity}).`);
            return;
         }
   
         if (quantity > 0) {
            setSaleDetails(prevState => ({
               ...prevState,
               products: [...prevState.products, { productId, quantity, price: product.price }],
            }));
            setTotalPrice(prevTotal => prevTotal + (product.price * quantity));
         }
      }
   };

   const quantities = saleDetails.products.map(product => String(product.quantity));
   const ids = saleDetails.products.map(product => String(product.productId));
   const prices = saleDetails.products.map(products =>String(products.price));

   const handleSubmit = async () => {
      if (!saleDetails.clientId) {
         alert('Adicione um cliente.');
         return;
      }
   
      if (!saleDetails.paymentMethodId) {
         alert('Adicione um método de pagamento.');
         return;
      }
   
      if (saleDetails.products.length === 0) {
         alert('Adicione pelo menos um produto a venda.');
         return;
      }
   
      const hasInvalidQuantity = saleDetails.products.some(product => product.quantity <= 0);
      if (hasInvalidQuantity) {
         alert('Tenha certeza que todos os produtos tem uma quantidade.');
         return;
      }
      const saleData = {
         sellerId: String(localStorage.getItem('id')),
         price: String(totalPrice),
         quantity : quantities,
         products : ids,
         priceArray : prices,
         clientId :  String(saleDetails.clientId),
      };

      try {
         await fetch('https://localhost:12354/api/order', {
            method: 'POST',
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
            body: JSON.stringify(saleData)
         });
         alert("Venda feita com sucesso");

         setSaleDetails({
            clientId: '',
            paymentMethodId: '',
            products: [],
         })

      } catch (error) {
         console.error("Error submitting sale:", error);
      }
   };

   const getClientName = (id) => clients.find(c => c.id === id)?.name || 'N/A';
   const getProductName = (id) => products.find(p => p.id === id)?.name || 'N/A';

   return (
      <div className="Sales">
         <header className="Menu-header">
            <Sidebar />
            <Menu />
         </header>

         <div className="Sales-content">
            <div className="SelectedProducts">
               <h2>Produtos selecionados</h2>
               {saleDetails.products.length > 0 ? (
                  saleDetails.products.map((product, index) => (
                     <div key={index} className="productLine">
                        <span>{getProductName(product.productId)}</span>
                        <span>Quantity: {product.quantity}</span>
                        <span>Price: {product.price * product.quantity}</span>
                     </div>
                  ))
               ) : (
                  <p>Nenhum produto selectionado</p>
               )}
               <div className="totalPrice">Total Price: {totalPrice}</div>

               <div className="OrderDetails">
                  <label>Cliente</label>
                  <Select
                     options={clients.map(client => ({ value: client.id, label: client.name }))}
                     onChange={selectedOption => setSaleDetails(prevState => ({ ...prevState, clientId: selectedOption.value }))}
                  />

                  <label>Método de pagamento</label>
                  <Select
                     options={paymentMethods.map(pm => ({ value: pm.id, label: pm.name }))}
                     onChange={selectedOption => setSaleDetails(prevState => ({ ...prevState, paymentMethodId: selectedOption.value }))}
                  />
               </div>
            </div>

            <div className="AvailableProducts">
               <h2>Produtos disponíveis</h2>
               {products.map(product => (
                  <div key={product.id} className="productLine">
                     <span>{product.name}</span>
                     <span>Price: {product.price}</span>
                     <input
                        type="number"
                        placeholder="Quantity"
                        min="1"
                        onChange={(e) => setSaleDetails(prevState => ({
                           ...prevState,
                           currentQuantity: e.target.value,
                           currentProductId: product.id
                        }))}
                     />
                     <button
                        onClick={() => addProduct(saleDetails.currentProductId, saleDetails.currentQuantity)}
                     >
                        Adicionar a venda
                     </button>
                  </div>
               ))}
            </div>

            <button onClick={handleSubmit} className="submitSaleButton">Finalizar venda</button>
         </div>
      </div>
   );
}

export default Sales;
