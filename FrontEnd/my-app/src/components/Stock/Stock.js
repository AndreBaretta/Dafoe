import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

function Stock() {

   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [newProductScreen, setNewProductScreen] = useState(false)
   const [addStockScreen, setAddStockScreen] = useState(false)
   const [queryType, setQueryType] = useState(0)

   useEffect(() => {
      const getData = async () => {
         try {
            if(queryType === 0){
               const response = await fetch("http://localhost:12354/api/product?name=" + searchValue);
               const data = await response.json();
               setResults(data)
            }else if(queryType === 1){
               const response = await fetch("http://localhost:12354/api/product?name=" + searchValue);
               const data = await response.json();
               setResults(data)
            }else if(queryType === 2){
               const response = await fetch("http://localhost:12354/api/product?name=" + searchValue);
               const data = await response.json();
               setResults(data)
            }else if(queryType === 3){
               const response = await fetch("http://localhost:12354/api/product?name=" + searchValue);
               const data = await response.json();
               setResults(data)
            }else if(queryType === 4){
               const response = await fetch("http://localhost:12354/api/product?name=" + searchValue);
               const data = await response.json();
               setResults(data)
            }
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue])
   
   return (
      <div className="Stock">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <button onClick={() => setNewProductScreen(true)}>novo produto</button> 
            <button onClick={() => setAddStockScreen(true)}>Adicionar estoque</button>
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
         <Model isOpen={newProductScreen}>
            <div className='newProduct'>
               <button onClick={() => setNewProductScreen(false)}>X</button>
               Nome: <input type='text'></input>
            </div>
         </Model>
         <Model isOpen={addStockScreen}>
            <div className='addStock'>
               <button onClick={() => setAddStockScreen(false)}>X</button>
            </div>
         </Model>
      </div>
   );
}

export default Stock;
