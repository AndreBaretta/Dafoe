import React, { useState, useEffect } from 'react';
import './App.css';
import Home from './components/Home/Home';
import Login from './components/Login/Login';
import Sales from './components/Sales/Sales';
import Stock from './components/Stock/Stock';
import Register from './components/Register/Register';
import Clients from './components/Clients/Clients';
import History from './components/History/History';
import Manufacturer from './components/Manufacturer/Manufacturer';
import General from './components/General/General';
import Employee from './components/Employee/Employee';

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
      switch (page) {
         case 'login':
            return <Login />
         case 'home':
            return <Home />
         case 'sales':
            return <Sales />
         case 'stock':
            return <Stock />
         case 'register':
            return <Register />
         case 'clients':
            return <Clients />
         case 'history':
            return <History />
         case 'manufacturer':
            return <Manufacturer />
         case 'general':
            return <General />
         case 'employee':
            return <Employee />
         default:
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
