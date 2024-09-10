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
   const [editClientScreen, setEditClientScreen] = useState(false);
   const [clientDetails, setClientDetails] = useState({
      id: '',
      name: '',
      phoneNumber: '',
      address: '',
      bill: '',
   });
   const [isPending, setIsPending] = useState(false);
   const [selectedClient, setSelectedClient] = useState(null);
   const [editMode, setEditMode] = useState(false);

   const [sortOrder, setSortOrder] = useState({
      name: 'asc',
      phoneNumber: 'asc',
      bill: 'asc',
   });

   // Extracting fetch logic to reuse
   const getData = async () => {
      try {
         const response = await fetch(`https://localhost:12354/api/client?name=${searchValue}`, {
            headers: {
               "token": localStorage.getItem('token'),
            },
         });
         const data = await response.json();
         if (Array.isArray(data)) {
            setResults(data);
         } else {
            console.error('Received data is not an array:', data);
            setResults([]);
         }
      } catch (error) {
         console.error('Error fetching clients:', error);
         setResults([]);
      }
   };

   // Fetch clients initially and whenever searchValue changes
   useEffect(() => {
      getData();
   }, [searchValue]);

const handleInputChange = (e) => {
   const { name, value } = e.target;

   // Ensure bill is handled as a string
   setClientDetails((prevState) => ({
      ...prevState,
      [name]: name === 'bill' ? String(value) : value, // Always store bill as a string
   }));
};   
  const submitClientData = async () => {
   setIsPending(true);
      try {
         const response = await fetch('https://localhost:12354/api/client', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json',
               'token': localStorage.getItem('token'),
            },
            body: JSON.stringify({
               ...clientDetails,
               bill: String(clientDetails.bill), // Make sure bill is sent as a string
            }),
         });

      if (response.ok) {
         console.log('Cliente adicionado com sucesso');
         setClientDetails({
            id: '',
            name: '',
            phoneNumber: '',
            address: '',
            bill: '', // Reset bill to an empty string
         });
         setNewClientScreen(false);
         setSearchValue('');
         getData();
      } else {
         console.error('Erro ao adicionar cliente');
      }
   } catch (error) {
      console.error('Erro na requisição:', error);
   } finally {
      setIsPending(false);
   }
};
   const handleSort = (key) => {
      const order = sortOrder[key] === 'asc' ? 'desc' : 'asc';

      const sortedResults = [...results].sort((a, b) => {
         if (order === 'asc') {
            return a[key] > b[key] ? 1 : -1;
         } else {
            return a[key] < b[key] ? 1 : -1;
         }
      });

      setResults(sortedResults);
      setSortOrder({ ...sortOrder, [key]: order });
   };

   const handleRowClick = (client) => {
      setSelectedClient(client);
      setClientDetails(client);
      setEditMode(true);
      setEditClientScreen(true);
   };

  const handleUpdateClient = async () => {
   setIsPending(true);
   try {
         const response = await fetch(`https://localhost:12354/api/client/${clientDetails.id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json',
               'token': localStorage.getItem('token'),
            },
            body: JSON.stringify({
               ...clientDetails,
               bill: String(clientDetails.bill), // Make sure bill is sent as a string
            }),
      });

      if (response.ok) {
         console.log('Cliente atualizado com sucesso');
         setEditMode(false);
         setEditClientScreen(false);
         setSearchValue('');
         getData();
      } else {
         console.error('Erro ao atualizar cliente');
      }
   } catch (error) {
      console.error('Erro na requisição:', error);
   } finally {
      setIsPending(false);
   }
};
   const handleDeleteClient = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/client/${clientDetails.id}`, {
            method: 'DELETE',
            headers: {
               "token": localStorage.getItem('token'),
            }
         });

         if (response.ok) {
            console.log('Cliente deletado com sucesso');
            setEditMode(false);
            setEditClientScreen(false);
            setSearchValue(''); // Reset search and trigger re-fetch
            getData(); // Fetch updated list
         } else {
            console.error('Erro ao deletar cliente');
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
                     <th onClick={() => handleSort('name')}>
                        Nome
                     </th>
                     <th onClick={() => handleSort('phoneNumber')}>
                        Telefone
                     </th>
                     <th onClick={() => handleSort('bill')}>
                        Dívida
                     </th>
                  </tr>
               </thead>
               <tbody>
                  {results.length > 0 ? (
                     results.map((client) => (
                        <tr key={client.id} onClick={() => handleRowClick(client)}>
                           <td>{client.name}</td>
                           <td>{client.phoneNumber}</td>
                           <td>{client.bill}</td>
                        </tr>
                     ))
                  ) : (
                     <tr>
                        <td colSpan="3">Nenhum cliente encontrado</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal for editing selected client */}
         <Model
            isOpen={editClientScreen}
            onRequestClose={() => setEditClientScreen(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setEditClientScreen(false)}>X</button>
            <div className="ReactModal__Header">
               <h2>Editar Cliente</h2>
               <form className="editClient">
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={clientDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Telefone:
                     <input
                        type="text"
                        name="phoneNumber"
                        value={clientDetails.phoneNumber}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Endereço:
                     <input
                        type="text"
                        name="address"
                        value={clientDetails.address}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Dívida:
                     <input
                        type="text"
                        name="bill"
                        value={clientDetails.bill}
                        onChange={handleInputChange}
                     />
                  </label>
                  {!isPending ? (
                     <>
                        <button type="button" onClick={handleUpdateClient}>
                           Atualizar
                        </button>
                        <button type="button" onClick={handleDeleteClient}>
                           Deletar
                        </button>
                     </>
                  ) : (
                     <button disabled>Salvando...</button>
                  )}
               </form>
            </div>
         </Model>

         {/* Modal for creating new client */}
         <Model
            isOpen={newClientScreen}
            onRequestClose={() => setNewClientScreen(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setNewClientScreen(false)}>X</button>
            <div className="ReactModal__Header">
               <h2>Novo Cliente</h2>
               <form className="newClient">
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={clientDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Telefone:
                     <input
                        type="text"
                        name="phoneNumber"
                        value={clientDetails.phoneNumber}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Endereço:
                     <input
                        type="text"
                        name="address"
                        value={clientDetails.address}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Dívida:
                     <input
                        type="text"
                        name="bill"
                        value={clientDetails.bill}
                        onChange={handleInputChange}
                     />
                  </label>
                  {!isPending ? (
                     <button type="button" onClick={submitClientData}>
                        Adicionar
                     </button>
                  ) : (
                     <button disabled>Salvando...</button>
                  )}
               </form>
            </div>
         </Model>
      </div>
   );
}

export default Clients;
