import React, {useState, useEffect} from 'react';
import './App.css';
import Home from './components/Home/Home';
import Login from './components/Login/Login';
import Sales from './components/Sales/Sales';
import Stock from './components/Stock/Stock';
import Register from './components/Register/Register';
import SearchBar from './components/SearchBar/SearchBar';

function App() {

  const [query, setQuery] = useState ("");
  const [results, setResults] = useState ("");


  const [page, setPage] = useState(0)

  useEffect(
    () => {
      const url=window.location.href
      const res=url.split('?')
      setPage(res[1])
    }
  )

  const linksPages=(p) => {
    if(p===1){
      window.open('http://localhost:3000?home','_self')
    }else if(p===2){
      window.open('http://localhost:3000?login','_self')
    }else if(p===3){
      window.open('http://localhost:3000?sales','_self')
    }else if(p===4){
      window.open('http://localhost:3000?stock','_self')
    }else if(p===5){
      window.open('http://localhost:3000?register','_self')
    }
  }

  const returnPage=() => {
    if(page==='home'){
      return <Home />
    }else if(page==='login'){
      return <Login />
    }else if(page==='sales'){
      return <Sales />
    }else if(page==='stock'){
      return <Stock />
    }else if(page==='register'){
      return <Register />
    }else{
      return <div>  
              <button onClick={()=>linksPages(2)}>Login</button>
              </div>
  }
  }

  return (
    <div className="App">
      {returnPage()}
      <SearchBar results={results} setResults={setResults}/>
    </div>
  );
}

export default App;
