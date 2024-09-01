import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

function Stock() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [newProductScreen, setNewProductScreen] = useState(false);
   const [addStockScreen, setAddStockScreen] = useState(false);
   const [queryType, setQueryType] = useState(0);
   const [productDetails, setProductDetails] = useState({
      name: '',
      manufacturer: '',
      price: '',
      cost: '',
      quantity: ''
   });

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(`http://localhost:12354/api/product?name=${searchValue}&type=${queryType}`);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue, queryType]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setProductDetails(prevState => ({
         ...prevState,
         [name]: value
      }));
   };

   return (
      <div className="Stock">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="button-container">
               <button className="newProductButton" onClick={() => setNewProductScreen(true)}>Novo Produto</button>
               <button className="addStockButton" onClick={() => setAddStockScreen(true)}>Adicionar Estoque</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Stock-table-container">
            <table className="Stock-table">
               <thead>
                  <tr>
                     <th>Nome <button onClick={() => setQueryType(0)}></button></th>
                     <th>Fabricante <button onClick={() => setQueryType(1)}></button></th>
                     <th>Preço <button onClick={() => setQueryType(2)}></button></th>
                     <th>Custo <button onClick={() => setQueryType(3)}></button></th>
                     <th>Quantidade <button onClick={() => setQueryType(4)}></button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.id}>
                        <td>{item.name}</td>
                        <td>{item.manufacturer}</td>
                        <td>{item.price}</td>
                        <td>{item.cost}</td>
                        <td>{item.quantity}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
         <Model
            isOpen={newProductScreen}
            onRequestClose={() => setNewProductScreen(false)}
            className="ReactModal__Content"
         >
            <div className='newProduct'>
               <span className='ReactModal__Close' onClick={() => setNewProductScreen(false)}>X</span>
               <h2>Adicionar Novo Produto</h2>
               <form>
                  <label>Nome:
                     <input 
                        type='text' 
                        name='name'
                        value={productDetails.name}
                        onChange={handleInputChange} 
                        placeholder="Digite o nome do produto"
                     />
                  </label>
                  <label>Fabricante:
                     <input 
                        type='text' 
                        name='manufacturer'
                        value={productDetails.manufacturer}
                        onChange={handleInputChange} 
                        placeholder="Digite o fabricante"
                     />
                  </label>
                  <label>Preço:
                     <input 
                        type='text' 
                        name='price'
                        value={productDetails.price}
                        onChange={handleInputChange} 
                        placeholder="Digite o preço"
                     />
                  </label>
                  <label>Custo:
                     <input 
                        type='text' 
                        name='cost'
                        value={productDetails.cost}
                        onChange={handleInputChange} 
                        placeholder="Digite o custo"
                     />
                  </label>
                  <label>Quantidade:
                     <input 
                        type='text' 
                        name='quantity'
                        value={productDetails.quantity}
                        onChange={handleInputChange} 
                        placeholder="Digite a quantidade"
                     />
                  </label>
                  <button type="button" onClick={() => setNewProductScreen(false)}>Salvar</button>
               </form>
            </div>
         </Model>
         <Model
            isOpen={addStockScreen}
            onRequestClose={() => setAddStockScreen(false)}
            className="ReactModal__Content"
         >
            <div className='addStock'>
               <span className='ReactModal__Close' onClick={() => setAddStockScreen(false)}>X</span>
               <h2>Adicionar Estoque</h2>
               <form>
                  <label>Nome do Produto:
                     <input 
                        type='text' 
                        name='name'
                        onChange={handleInputChange} 
                        placeholder="Digite o nome do produto"
                     />
                  </label>
                  <label>Quantidade:
                     <input 
                        type='text' 
                        name='quantity'
                        onChange={handleInputChange} 
                        placeholder="Digite a quantidade"
                     />
                  </label>
                  <button type="button" onClick={() => setAddStockScreen(false)}>Salvar</button>
               </form>
            </div>
         </Model>
      </div>
   );
}

export default Stock;
