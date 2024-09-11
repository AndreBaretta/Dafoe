import React, { useState, useEffect } from 'react';
import {BrowserRouter as Router, Routes, Route} from "react-router-dom";
import './App.css';
import Home from './components/Home/Home';
import Login from './components/Login/Login';
import Sales from './components/Sales/Sales';
import Stock from './components/Stock/Stock';
import Clients from './components/Clients/Clients';
import Manufacturer from './components/Manufacturer/Manufacturer';
import General from './components/General/General';
import Employee from './components/Employee/Employee';
import User from './components/User/User'

function App() {
   const [page, setPage] = useState('')

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
         case 'clients':
            return <Clients />
         case 'manufacturer':
            return <Manufacturer />
         case 'general':
            return <General />
         case 'employee':
            return <Employee />
         case 'user':
            return <User />
         default:
            return <Login />
      }
   }

   return (
      <div className="App">
         <Router>
            <Routes>
            <Route path="/" element={<Login />} />
            <Route path="/home" element={<Home />} />
            <Route path="/sales" element={<Sales />} />
            <Route path="/stock" element={<Stock />} />
            <Route path="/clients" element={<Clients />} />
            <Route path="/manufacturer" element={<Manufacturer />} />
            <Route path="/general" element={<General />} />
            <Route path="/employee" element={<Employee />} />
            <Route path="/user" element={<User />} />
            </Routes>
         </Router>
      </div>
   );
}

export default App;
