import './Clients.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function Clients() {
   const [searchValue, setSearchValue] = useState('');
   const [results, setResults] = useState([]); // Initialized as empty array
   const [newClientScreen, setNewClientScreen] = useState(false); // Control new client modal
   const [clientDetails, setClientDetails] = useState({
      id: '',
      name: '',
      phoneNumber: '',
      address: '',
      bill: '', // Ensure this is a string
   });
   const [isPending, setIsPending] = useState(false);
   const [selectedClient, setSelectedClient] = useState(null);
   const [editMode, setEditMode] = useState(false);

   const [sortOrder, setSortOrder] = useState({
      name: 'asc',
      phoneNumber: 'asc',
      bill: 'asc',
   });

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(
               `https://localhost:12354/api/client?name=${searchValue}`
            );
            const data = await response.json();
            // Check if data is an array before setting it to results
            if (Array.isArray(data)) {
               setResults(data);
            } else {
               console.error('Received data is not an array:', data);
               setResults([]); // Ensure results is always an array
            }
         } catch (error) {
            console.error('Error fetching clients:', error);
            setResults([]); // Ensure results is always an array
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
               id: '',
               name: '',
               phoneNumber: '',
               address: '',
               bill: '', // Ensure this is a string
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
      setClientDetails(client); // Pre-fill with client details
      setEditMode(true); // Open the modal in edit mode
   };

   const handleUpdateClient = async () => {
      setIsPending(true);
      try {
         // Ensure bill is a string
         const updatedClientDetails = {
            ...clientDetails,
            bill: String(clientDetails.bill), // Convert bill to string
         };
   
         const response = await fetch(`https://localhost:12354/api/client/${clientDetails.id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(updatedClientDetails),
         });
   
         if (response.ok) {
            console.log('Cliente atualizado com sucesso');
            setEditMode(false); // Close modal
            setSearchValue(''); // Refetch data
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
         });

         if (response.ok) {
            console.log('Cliente deletado com sucesso');
            setEditMode(false); // Close modal
            setSearchValue(''); // Refetch data
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
                  onClick={() => setNewClientScreen(true)} // Open new client modal
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
      <div style={{ display: 'flex', justifyContent: 'space-between' }}>
        <span>Nome</span>
      </div>
    </th>
    <th onClick={() => handleSort('cargo')}>
      <div style={{ display: 'flex', justifyContent: 'space-between' }}>
        <span>Cargo</span>
      </div>
    </th>
  </tr>
</thead>
               <tbody>
                  {Array.isArray(results) && results.length > 0 ? (
                     results.map((client) => (
                        <tr key={client.id} onClick={() => handleRowClick(client)}>
                           <td>{client.name}</td>
                           <td>{client.phoneNumber}</td>
                           <td>{client.bill}</td>
                        </tr>
                     ))
                  ) : (
                     <tr>
                        <td colSpan="3">No clients found</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal for editing selected client */}
         <Model
            isOpen={editMode}
            onRequestClose={() => setEditMode(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setEditMode(false)}>X</button>
            <div className="ReactModal__Header">
               Editar Cliente
               <div className="editClient">
                  <form>
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
                           type="tel"
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
                           type="text" // Changed from number to text
                           name="bill"
                           value={clientDetails.bill}
                           onChange={handleInputChange}
                        />
                     </label>
                     {!isPending && (
                        <>
                           <button type="button" onClick={handleUpdateClient}>
                              Atualizar
                           </button>
                           <button type="button" onClick={handleDeleteClient}>
                              Deletar
                           </button>
                        </>
                     )}
                     {isPending && <button disabled>Salvando...</button>}
                  </form>
               </div>
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
               Novo Cliente
               <div className="addClient">
                  <form>
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
                           type="tel"
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
                           type="text" // Changed from number to text
                           name="bill"
                           value={clientDetails.bill}
                           onChange={handleInputChange}
                        />
                     </label>
                     {!isPending && (
                        <button type="button" onClick={submitClientData}>
                           Adicionar
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
