import './Clients.css';
import React, { useState, useEffect } from 'react';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import SearchBar from '../SearchBar/SearchBar';

function Clients() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch("http://localhost:12354/api/client?name=" + searchValue);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue]);

   return (
      <div className="Clients">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Clients-table-container">
            <table className="Clients-table">
               <thead>
                  <tr>
                     <th>Nome</th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.id}>
                        <td>{item.name}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
      </div>
   );
}

export default Clients;
