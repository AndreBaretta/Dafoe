import './History.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar'; 
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';

function History() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [queryOrder, setQueryOrder] = useState("name");

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(`https://localhost:12354/api/product?name=${searchValue}`);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue, queryOrder]);

   return (
      <div className="History">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="History-table-container">
            <table className="History-table">
               <thead>
                  <tr>
                     <th>Item <button onClick={() => setQueryOrder("name")}></button></th>
                     <th>Fabricante <button onClick={() => setQueryOrder("manufacturer")}></button></th>
                     <th>Preço <button onClick={() => setQueryOrder("price")}></button></th>
                     <th>Quantidade <button onClick={() => setQueryOrder("quantity")}></button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.name}>
                        <td>{item.name}</td>
                        <td>{item.manufacturer}</td>
                        <td>{item.price}</td>
                        <td>{item.quantity}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
      </div>
   );
}

export default History;
