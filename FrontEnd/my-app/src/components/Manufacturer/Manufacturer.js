import './Manufacturer.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function Manufacturer() {
   const [searchValue, setSearchValue] = useState('');
   const [results, setResults] = useState([]);
   const [newManufacturerScreen, setNewManufacturerScreen] = useState(false);
   const [manufacturerDetails, setManufacturerDetails] = useState({
      name: '',
      contact: '',
      address: '',
      email: '',
   });
   const [isPending, setIsPending] = useState(false);

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(`https://localhost:12354/api/manufacturer?name=${searchValue}`);
            const data = await response.json();
            if (Array.isArray(data)) {
               setResults(data);
            } else {
               console.error('Received data is not an array:', data);
               setResults([]);
            }
         } catch (error) {
            console.error('Error fetching manufacturers:', error);
            setResults([]);
         }
      };

      getData();
   }, [searchValue]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setManufacturerDetails((prevState) => ({
         ...prevState,
         [name]: value,
      }));
   };

   const handleSubmit = async () => {
      setIsPending(true);
      try {
         const response = await fetch('https://localhost:12354/api/manufacturer', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(manufacturerDetails),
         });

         if (response.ok) {
            console.log('Fabricante adicionado com sucesso');
            setManufacturerDetails({
               name: '',
               contact: '',
               address: '',
               email: '',
            });
            setNewManufacturerScreen(false);
            setSearchValue('');
         } else {
            console.error('Erro ao adicionar fabricante');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   return (
      <div className="Manufacturer">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="button-container">
               <button className="newManufacturerButton" onClick={() => setNewManufacturerScreen(true)}>Novo Fabricante</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Manufacturer-table-container">
            <table className="Manufacturer-table">
               <thead>
                  <tr>
                     <th>Nome <button onClick={() => console.log('Ordenar por Nome')}></button></th>
                     <th>Contato <button onClick={() => console.log('Ordenar por Contato')}></button></th>
                     <th>Endereço <button onClick={() => console.log('Ordenar por Endereço')}></button></th>
                     <th>Email <button onClick={() => console.log('Ordenar por Email')}></button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.id}>
                        <td>{item.name}</td>
                        <td>{item.contact}</td>
                        <td>{item.address}</td>
                        <td>{item.email}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>

         {/* Modal para adicionar novo fabricante */}
         <Model
            isOpen={newManufacturerScreen}
            onRequestClose={() => setNewManufacturerScreen(false)}
            className="ReactModal__Content"
         >
            <button className="ReactModal__Close" onClick={() => setNewManufacturerScreen(false)}>X</button>
            <div className='newManufacturer'>
               <h2>Novo Fabricante</h2>
               <form>
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={manufacturerDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Contato:
                     <input
                        type="text"
                        name="contact"
                        value={manufacturerDetails.contact}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Endereço:
                     <input
                        type="text"
                        name="address"
                        value={manufacturerDetails.address}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Email:
                     <input
                        type="email"
                        name="email"
                        value={manufacturerDetails.email}
                        onChange={handleInputChange}
                     />
                  </label>
                  {!isPending && (
                     <button type="button" onClick={handleSubmit}>
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

export default Manufacturer;
