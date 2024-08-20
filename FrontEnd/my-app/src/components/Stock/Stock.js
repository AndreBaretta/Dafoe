import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import '../Buttons/BackButton.css'
import SearchBar from '../SearchBar/SearchBar';
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
        <div className="backButtonDisplay">
            <div className="backButton">
              <button onClick={()=>window.open('http://localhost:3000?home','_self')}></button>
              <div className="icon">⬅</div>
              <span>voltar</span>
            </div>
          </div>
        <header className='SearchBarHeader'>
          <SearchBar results={results} setResults={setResults}/>
        </header>
        <header className='SideBarHeader'>
          <Sidebar />
        </header>
      </div>
    </div>  
  );
}

export default Stock;