import './Sales.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

function Sales() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [newSaleScreen, setNewSaleScreen] = useState(false);
   const [product, setProduct] = useState("");
   const [price, setPrice] = useState("");
   const [seller, setSeller] = useState("");
   const [date, setDate] = useState("");
   const [productsList, setProductsList] = useState([]);
   const [sellersList, setSellersList] = useState([]);

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(`https://localhost:12354/api/order?product=${searchValue}`);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue]);

   useEffect(() => {
      const fetchProductsAndSellers = async () => {
         try {
            const productsResponse = await fetch('https://localhost:12354/api/product?name=');
            const productsData = await productsResponse.json();
            setProductsList(productsData);

            const sellersResponse = await fetch('https://localhost:12354/api/employee?name=');
            const sellersData = await sellersResponse.json();
            setSellersList(sellersData);
         } catch (error) {
            console.error(error);
         }
      };

      fetchProductsAndSellers();
   }, []);

   const handleSubmit = () => {
      console.log({ product, price, seller, date });
      setNewSaleScreen(false); 
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
                     <th>Produto <button onClick={() => console.log('Ordenar por Produto')}></button></th>
                     <th>Quantidade <button onClick={() => console.log('Ordenar por Quantidade')}></button></th>
                     <th>Preço <button onClick={() => console.log('Ordenar por Preço')}></button></th>
                     <th>Data <button onClick={() => console.log('Ordenar por Data')}></button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.id}>
                        <td>{item.product}</td>
                        <td>{item.quantity}</td>
                        <td>{item.price}</td>
                        <td>{item.date}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
         <Model
            isOpen={newSaleScreen}
            onRequestClose={() => setNewSaleScreen(false)}
            className="ReactModal__Content"
         >
            <div className='newSale'>
               <span className='ReactModal__Close' onClick={() => setNewSaleScreen(false)}>X</span>
               <h2>Nova Venda</h2>
               <label>Produto</label>
               <select value={product} onChange={(e) => setProduct(e.target.value)}>
                  <option value="">Selecione um produto</option>
                  {productsList.map((p) => (
                     <option key={p.id} value={p.id}>{p.name}</option>
                  ))}
               </select>
               
               <label>Valor</label>
               <input type="number" value={price} onChange={(e) => setPrice(e.target.value)} />
               
               <label>Vendedor</label>
               <select value={seller} onChange={(e) => setSeller(e.target.value)}>
                  <option value="">Selecione um vendedor</option>
                  {sellersList.map((s) => (
                     <option key={s.id} value={s.id}>{s.name}</option>
                  ))}
               </select>
               
               <label>Data</label>
               <input type="date" value={date} onChange={(e) => setDate(e.target.value)} />
               
               <button onClick={handleSubmit}>Salvar</button>
            </div>
         </Model>
      </div>
   );
}

export default Sales;
