import './Clients.css';
import React, { useState, useEffect } from 'react';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import SearchBar from '../SearchBar/SearchBar';
import ReactModal from 'react-modal';

function Clients() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [newClientScreen, setNewClientScreen] = useState(false);

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch("http://localhost:12354/api/client?name=" + searchValue);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue]);

   return (
      <div className="Clients">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <SearchBar results={searchValue} setResults={setSearchValue} />
            <div className="button-container">
               <button className="newClientButton" onClick={() => setNewClientScreen(true)}>Novo Cliente</button>
            </div>
         </header>
         <div className="Clients-table-container">
            <table className="Clients-table">
               <thead>
                  <tr>
                     <th>Nome</th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.id}>
                        <td>{item.name}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
         <ReactModal 
            isOpen={newClientScreen} 
            onRequestClose={() => setNewClientScreen(false)}
            className="ReactModal__Content"
            overlayClassName="ReactModal__Overlay"
         >
            <button className="ReactModal__Close" onClick={() => setNewClientScreen(false)}>X</button>
            <div className="ReactModal__Header">
               Adicionar Novo Cliente
            </div>
            <div className="newClient">
               <label htmlFor="name">Nome:</label>
               <input id="name" type='text'></input>
               <label htmlFor="phone">Telefone:</label>
               <input id="phone" type='text'></input>
               <button>Salvar</button>
            </div>
         </ReactModal>
      </div>
   );
}

export default Clients;
