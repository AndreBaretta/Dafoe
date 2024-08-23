import './Clients.css';
import React, {useState} from 'react';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import SearchBar from '../SearchBar/SearchBar';

function Clients() {

   const [query, setQuery] = useState ("");
   const [results, setResults] = useState ("");
 
   function getData() {
     fetch("https://jsonplaceholder.typicode.com/posts").then((Response) => Response.json().then(json=>console.log(json)))
   }

  return (
    <div className="Clients">
      <div className="Clients-glass">
        <header className='Menu-header'>
          <Sidebar />
          <Menu />
        </header>
        <header className='SearchBarHeader'>
          <SearchBar results={results} setResults={setResults}/>
        </header>
      </div>
    </div>
  );
}

export default Clients;