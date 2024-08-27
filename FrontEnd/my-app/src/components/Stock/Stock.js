import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, {useState, useEffect} from 'react';



function Stock() {

  const [searchValue, setSearchValue] = useState("");
  const [results, setResults] = useState([]);
  console.log(results)

  useEffect(() => {
    const getData = async () => {
      try{
        const response = await fetch("localhost:12354/api/product/" + searchValue);
        const data = await response.json();
        setResults(data)
      } catch(error) {
        console.error(error);
      }
    };

    getData();
  }, [searchValue])

  return (
    <div className="Stock">
      <div className="Stock-glass">
        <header className='Menu-header'>
          <Sidebar />
          <Menu />
        </header>
        <header className='SearchBarHeader'>
          <SearchBar results={searchValue} setResults={setSearchValue}/>
        </header>
        <div>
          {results.map((item) => (
            <tr>
              <td>{item.name}</td>
              <td>{item.manufacturer}</td>
              <td>{item.price}</td>
              <td>{item.cost}</td>
              <td>{item.quantity}</td>
            </tr>
          ))}
        </div>
      </div>
    </div>  
  );
}

export default Stock;