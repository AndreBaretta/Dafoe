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
   const [editManufacturerScreen, setEditManufacturerScreen] = useState(false);
   const [manufacturerDetails, setManufacturerDetails] = useState({
      id: '',
      name: '',
   });
   const [isPending, setIsPending] = useState(false);
   const [sortOrder, setSortOrder] = useState('asc'); // Sorting order state

   const fetchManufacturers = async () => {
      try {
         const response = await fetch(`https://localhost:12354/api/manufacturer?name=${searchValue}`, {
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
         console.error('Error fetching manufacturers:', error);
         setResults([]);
      }
   };

   useEffect(() => {
      fetchManufacturers();
   }, [searchValue]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setManufacturerDetails((prevState) => ({
         ...prevState,
         [name]: value,
      }));
   };

   const handleRowClick = (manufacturer) => {
      setManufacturerDetails(manufacturer);
      setEditManufacturerScreen(true);
   };

   const handleSubmit = async () => {
      setIsPending(true);
      try {
         const response = await fetch('https://localhost:12354/api/manufacturer', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json',
               'token': localStorage.getItem('token')
            },
            body: JSON.stringify(manufacturerDetails),
         });

         if (response.ok) {
            console.log('Fabricante adicionado com sucesso');
            setNewManufacturerScreen(false);
            setManufacturerDetails({
               id: '',
               name: '',
            });
            fetchManufacturers(); // Refresh after adding new manufacturer
         } else {
            console.error('Erro ao adicionar fabricante');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   const handleUpdateManufacturer = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/manufacturer/${manufacturerDetails.id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json',
               'token': localStorage.getItem('token')
            },
            body: JSON.stringify(manufacturerDetails),
         });

         if (response.ok) {
            console.log('Fabricante atualizado com sucesso');
            setEditManufacturerScreen(false);
            fetchManufacturers(); // Refresh after updating manufacturer
            setManufacturerDetails({
               id: '',
               name: '',
            });
         } else {
            console.error('Erro ao atualizar fabricante');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   const handleDeleteManufacturer = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/manufacturer/${manufacturerDetails.id}`, {
            method: 'DELETE',
            headers: {
               'token': localStorage.getItem('token')
            }
         });

         if (response.ok) {
            console.log('Fabricante deletado com sucesso');
            setEditManufacturerScreen(false);
            fetchManufacturers(); // Refresh after deleting manufacturer
            setManufacturerDetails({
               id: '',
               name: '',
            });
         } else {
            console.error('Erro ao deletar fabricante');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   const handleSort = () => {
      const sortedResults = [...results].sort((a, b) => {
         if (sortOrder === 'asc') {
            return a.name.localeCompare(b.name);
         } else {
            return b.name.localeCompare(a.name);
         }
      });
      setResults(sortedResults);
      setSortOrder(sortOrder === 'asc' ? 'desc' : 'asc'); // Toggle sort order
   };

   // Function to reset manufacturerDetails state
   const resetManufacturerDetails = () => {
      setManufacturerDetails({
         id: '',
         name: '',
      });
   };

   return (
      <div className="Manufacturer">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="manufacturer-button-container">
               <button className="newManufacturerButton" onClick={() => setNewManufacturerScreen(true)}>Novo Fabricante</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Manufacturer-table-container">
            <table className="Manufacturer-table">
               <thead>
                  <tr>
                     <th>
                        Nome <button onClick={handleSort}></button>
                     </th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((manufacturer) => (
                     <tr key={manufacturer.id} onClick={() => handleRowClick(manufacturer)}>
                        <td>{manufacturer.name}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>

         {/* Modal to edit existing manufacturer */}
         <Model
            isOpen={editManufacturerScreen}
            onRequestClose={() => {
               resetManufacturerDetails(); // Reset details when closing modal
               setEditManufacturerScreen(false);
            }}
            className="ReactModal__Content"
         >
            <button className="Manufacturer_ReactModal__Close" onClick={() => {
               resetManufacturerDetails(); // Reset details when closing modal
               setEditManufacturerScreen(false);
            }}>X</button>
            <div className='editManufacturer'>
               <h2>Editar Fabricante</h2>
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
                  {!isPending && (
                     <>
                        <button type="button" onClick={handleUpdateManufacturer}>
                           Atualizar
                        </button>
                        <button type="button" className="deleteButton" onClick={handleDeleteManufacturer}>
                           Deletar
                        </button>
                     </>
                  )}
                  {isPending && <button disabled>Salvando...</button>}
               </form>
            </div>
         </Model>

         {/* Modal to add new manufacturer */}
         <Model
            isOpen={newManufacturerScreen}
            onRequestClose={() => setNewManufacturerScreen(false)}
            className="ReactModal__Content"
         >
            <button className="Manufacturer_ReactModal__Close" onClick={() => setNewManufacturerScreen(false)}>X</button>
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
