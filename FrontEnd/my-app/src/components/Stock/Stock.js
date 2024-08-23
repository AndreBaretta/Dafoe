import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, {useState, useEffect} from 'react';

function Stock() {

  const [query, setQuery] = useState ("");
  const [results, setResults] = useState ("");

  function getData() {
    fetch("https://jsonplaceholder.typicode.com/posts").then((Response) => Response.json().then(json=>console.log(json)))
  }

  return (
    <div className="Stock">
      <div className="Stock-glass">
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

export default Stock;