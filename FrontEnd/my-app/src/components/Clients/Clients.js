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
      phoneNumber: '',
      address: '',
      bill: '',
   });
   const [isPending, setIsPending] = useState(false);

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(
               `https://localhost:12354/api/client?name=${searchValue}`
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

         const response = await fetch('https://localhost:12354/api/client', {

            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(clientDetails),
         });

         if (response.ok) {
            console.log('Cliente adicionado com sucesso');
            setClientDetails({
               name: '',
               phoneNumber: '',
               address: '',
               bill: '',
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
                        Divida{' '}
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
                        <td>{client.phoneNumber}</td>
                        <td>{client.bill}</td>
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
            <button className="ReactModal__Close" onClick={() => setNewClientScreen(false)}>X</button>
            <div className="ReactModal__Header">
               Adicionar Novo Cliente
               <div className="newClient">
                  <span
                     className="ReactModal__Close"
                     onClick={() => setNewClientScreen(false)}
                  >
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
                           name="phoneNumber"
                           value={clientDetails.phoneNumber}
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
                     <label>
                        Dívida:
                        <input
                           type="number"
                           name="bill"
                           value={clientDetails.bill}
                           onChange={handleInputChange}
                           placeholder="Digite a dívida do cliente"
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
            </div>
         </Model>
      </div>
   );
}

export default Clients;
