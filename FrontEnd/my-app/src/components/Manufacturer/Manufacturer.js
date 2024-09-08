import './Manufacturer.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar'; 
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';

function Manufacturer() {
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
      <div className="Manufacturer">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Manufacturer-table-container">
         </div>
      </div>
   );
}

export default Manufacturer;
