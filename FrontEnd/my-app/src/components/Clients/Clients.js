import './Clients.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function Clients() {
   const [searchValue, setSearchValue] = useState('');
   const [results, setResults] = useState([]);
   const [newClientScreen, setNewClientScreen] = useState(false);
   const [clientDetails, setClientDetails] = useState({
      name: '',
      email: '',
      phone: '',
      address: '',
   });
   const [isPending, setIsPending] = useState(false);

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(
               `http://localhost:12345/api/clients?name=${searchValue}`
            );
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error('Erro ao buscar clientes:', error);
         }
      };

      getData();
   }, [searchValue]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setClientDetails((prevState) => ({
         ...prevState,
         [name]: value,
      }));
   };

   const submitClientData = async () => {
      setIsPending(true);
      try {
         const response = await fetch('http://localhost:12345/api/clients', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(clientDetails),
         });

         if (response.ok) {
            console.log('Cliente adicionado com sucesso');
            setClientDetails({
               name: '',
               email: '',
               phone: '',
               address: '',
            });
            setNewClientScreen(false);
            setSearchValue('');
         } else {
            console.error('Erro ao adicionar cliente');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   return (
      <div className="Clients">
         <header className="Menu-header">
            <Sidebar />
            <Menu />
         </header>
         <header className="SearchBarHeader">
            <div className="button-container">
               <button
                  className="newClientButton"
                  onClick={() => setNewClientScreen(true)}
               >
                  Novo Cliente
               </button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Clients-table-container">
            <table className="Clients-table">
               <thead>
                  <tr>
                     <th>
                        Nome{' '}
                        <button onClick={() => console.log('Ordenar por Nome')}></button>
                     </th>
                     <th>
                        Telefone{' '}
                        <button
                           onClick={() => console.log('Ordenar por Telefone')}
                        ></button>
                     </th>
                     <th>
                        Endereço{' '}
                        <button
                           onClick={() => console.log('Ordenar por Endereço')}
                        ></button>
                     </th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((client) => (
                     <tr key={client.id}>
                        <td>{client.name}</td>
                        <td>{client.phone}</td>
                        <td>{client.address}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
         <Model
            isOpen={newClientScreen}
            onRequestClose={() => setNewClientScreen(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <div className="newClient">
               <span
                  className="ReactModal__Close"
                  onClick={() => setNewClientScreen(false)}
               >
                  X
               </span>
               <h2>Adicionar Novo Cliente</h2>
               <form>
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={clientDetails.name}
                        onChange={handleInputChange}
                        placeholder="Digite o nome do cliente"
                     />
                  </label>
                  <label>
                     Telefone:
                     <input
                        type="tel"
                        name="phone"
                        value={clientDetails.phone}
                        onChange={handleInputChange}
                        placeholder="Digite o telefone do cliente"
                     />
                  </label>
                  <label>
                     Endereço:
                     <input
                        type="text"
                        name="address"
                        value={clientDetails.address}
                        onChange={handleInputChange}
                        placeholder="Digite o endereço do cliente"
                     />
                  </label>
                  {!isPending && (
                     <button type="button" onClick={submitClientData}>
                        Salvar
                     </button>
                  )}
                  {isPending && <button disabled>Salvando...</button>}
               </form>
            </div>
         </Model>
      </div>
   );
}

export default Clients;
