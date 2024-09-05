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
<<<<<<< Updated upstream
=======
   const [clientDetails, setClientDetails] = useState({
      name: '',
      phoneNumber: '',
      address: '',
      bill: '',
   });
   const [isPending, setIsPending] = useState(false);
>>>>>>> Stashed changes

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch("http://localhost:12345/api/client?name=" + searchValue);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue]);

<<<<<<< Updated upstream
=======
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

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            <button className="ReactModal__Close" onClick={() => setNewClientScreen(false)}>X</button>
            <div className="ReactModal__Header">
               Adicionar Novo Cliente
=======
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
>>>>>>> Stashed changes
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
