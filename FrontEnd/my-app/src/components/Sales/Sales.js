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

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(`http://localhost:12345/api/sales?name=${searchValue}`);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue]);

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
               <input type="text" value={product} onChange={(e) => setProduct(e.target.value)} />
               
               <label>Valor</label>
               <input type="number" value={price} onChange={(e) => setPrice(e.target.value)} />
               
               <label>Vendedor</label>
               <input type="text" value={seller} onChange={(e) => setSeller(e.target.value)} />
               
               <label>Data</label>
               <input type="date" value={date} onChange={(e) => setDate(e.target.value)} />
               
               <button onClick={handleSubmit}>Salvar</button>
            </div>
         </Model>
      </div>
   );
}

export default Sales;
