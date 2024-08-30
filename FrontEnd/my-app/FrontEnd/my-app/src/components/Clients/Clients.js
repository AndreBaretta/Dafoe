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
            setResults(data)
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue])

   return (
      <div className="Clients">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
            <header className='SearchBarHeader'>
               <SearchBar results={searchValue} setResults={setSearchValue} />
            </header>
            <div>
               {results.map((item) => (
                  <tr>
                     <td>{item.name}</td>
                  </tr>
               ))}
            </div>
      </div>
   );
}

export default Clients;