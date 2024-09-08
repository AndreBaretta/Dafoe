import './General.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar'; 
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function General() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [view, setView] = useState(null); // Track current view: 'payment-methods' or 'categories'
   const [itemDetails, setItemDetails] = useState({ name: '' });
   const [isPending, setIsPending] = useState(false);
   const [editingItemId, setEditingItemId] = useState(null);
   const [newItemModal, setNewItemModal] = useState(false);
   const [sortOrder, setSortOrder] = useState('asc'); // Sorting order for names

   const fetchData = async () => {
      if (view) {
         try {
            let url;
            if (view === 'payment-methods') {
               url = 'https://localhost:12354/api/payment-method';
            } else if (view === 'categories') {
               url = 'https://localhost:12354/api/category';
            }
            const response = await fetch(url);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error('Error fetching data:', error);
         }
      }
   };

   useEffect(() => {
      fetchData();
   }, [view]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setItemDetails((prevState) => ({
         ...prevState,
         [name]: value,
      }));
   };

   const handleSubmit = async () => {
      setIsPending(true);
      try {
         let url, method;
         if (view === 'payment-methods') {
            url = `https://localhost:12354/api/payment-method${editingItemId ? `/${editingItemId}` : ''}`;
            method = editingItemId ? 'PUT' : 'POST';
         } else if (view === 'categories') {
            url = `https://localhost:12354/api/category${editingItemId ? `/${editingItemId}` : ''}`;
            method = editingItemId ? 'PUT' : 'POST';
         } else {
            return;
         }
         const response = await fetch(url, {
            method: method,
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(itemDetails),
         });

         if (response.ok) {
            console.log(`${view === 'payment-methods' ? 'PaymentMethod' : 'Category'} ${editingItemId ? 'updated' : 'created'} successfully`);
            setItemDetails({ name: '' });
            setEditingItemId(null);
            setNewItemModal(false);
            // Refresh list after adding/updating
            await fetchData(); 
         } else {
            console.error(`Error ${editingItemId ? 'updating' : 'creating'} ${view === 'payment-methods' ? 'PaymentMethod' : 'Category'}`);
         }
      } catch (error) {
         console.error('Error in request:', error);
      } finally {
         setIsPending(false);
      }
   };

   const handleDelete = async () => {
      setIsPending(true);
      try {
         let url;
         if (view === 'payment-methods') {
            url = `https://localhost:12354/api/payment-method/${editingItemId}`;
         } else if (view === 'categories') {
            url = `https://localhost:12354/api/category/${editingItemId}`;
         } else {
            return;
         }
         const response = await fetch(url, { method: 'DELETE' });

         if (response.ok) {
            console.log(`${view === 'payment-methods' ? 'PaymentMethod' : 'Category'} deleted successfully`);
            // Refresh list after deletion
            await fetchData();
            setNewItemModal(false);
         } else {
            console.error('Error deleting item');
         }
      } catch (error) {
         console.error('Error in request:', error);
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
      setSortOrder(sortOrder === 'asc' ? 'desc' : 'asc');
   };

   return (
      <div className="General">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="button-container">
               <button onClick={() => { setView('payment-methods'); setItemDetails({ name: '' }); }}>Métodos de Pagamento</button>
               <button onClick={() => { setView('categories'); setItemDetails({ name: '' }); }}>Categorias</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         {view && (
            <div className="General-table-container">
               <button
                  className="newItemButton"
                  onClick={() => { setNewItemModal(true); setItemDetails({ name: '' }); setEditingItemId(null); }}
               >
                  Novo {view === 'payment-methods' ? 'Método de Pagamento' : 'Categoria'}
               </button>
               <table className="General-table">
                  <thead>
                     <tr>
                        <th onClick={handleSort}>
                           Nome {sortOrder === 'asc' ? '↑' : '↓'}
                        </th>
                     </tr>
                  </thead>
                  <tbody>
                     {results.length > 0 ? (
                        results.map((item) => (
                           <tr key={item.id} onClick={() => { setItemDetails(item); setEditingItemId(item.id); setNewItemModal(true); }}>
                              <td>{item.name}</td>
                           </tr>
                        ))
                     ) : (
                        <tr>
                           <td colSpan="1">Nenhum {view === 'payment-methods' ? 'método de pagamento' : 'categoria'} encontrado</td>
                        </tr>
                     )}
                  </tbody>
               </table>
            </div>
         )}

         {/* Modal for creating/editing an item */}
         <Model
            isOpen={newItemModal}
            onRequestClose={() => setNewItemModal(false)}
            className="ReactModal__Content"
         >
            <button className="ReactModal__Close" onClick={() => setNewItemModal(false)}>X</button>
            <div className='newItem'>
               <h2>{editingItemId ? `Editar ${view === 'payment-methods' ? 'Método de Pagamento' : 'Categoria'}` : `Novo ${view === 'payment-methods' ? 'Método de Pagamento' : 'Categoria'}`}</h2>
               <form>
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={itemDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  {!isPending && (
                     <button type="button" onClick={handleSubmit}>
                        Salvar
                     </button>
                  )}
                  {isPending && <button disabled>Salvando...</button>}
                  {editingItemId && (
                     <button type="button" onClick={handleDelete} style={{ backgroundColor: 'red', color: 'white' }}>
                        Deletar
                     </button>
                  )}
               </form>
            </div>
         </Model>
      </div>
   );
}

export default General;

