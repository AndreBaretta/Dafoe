import React, { useState, useEffect } from 'react';
import './App.css';
import Home from './components/Home/Home';
import Login from './components/Login/Login';
import Sales from './components/Sales/Sales';
import Stock from './components/Stock/Stock';
import Register from './components/Register/Register';
import Clients from './components/Clients/Clients';
import History from './components/History/History';

function App() {

   const [page, setPage] = useState('login')

   useEffect(
      () => {
         const url = window.location.href
         const res = url.split('?')
         setPage(res[1])
      }
   )

   function returnPage() {
      if (page === 'home') {
         return <Home />
      } else if (page === 'login') {
         return <Login />
      } else if (page === 'sales') {
         return <Sales />
      } else if (page === 'stock') {
         return <Stock />
      } else if (page === 'register') {
         return <Register />
      } else if (page === 'clients') {
         return <Clients />
      } else if (page === 'history') {
         return <History />
      } else {
         return <Login />
      }
   }

   return (
      <div className="App">
         {returnPage()}
      </div>
   );
}

export default App;
