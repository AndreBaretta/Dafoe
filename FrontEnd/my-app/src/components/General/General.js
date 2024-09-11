import './General.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function General() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [categories, setCategories] = useState([]); // To store categories
   const [view, setView] = useState(null);
   const [itemDetails, setItemDetails] = useState({ name: '', category: '' });
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
            } else if (view === 'generic-products') {
               url = 'https://localhost:12354/api/generic-product';
            }
            const response = await fetch(url, {
               headers: {
                  "token": localStorage.getItem('token'),
               },
            });
            const data = await response.json();
            setResults(data || []); // Ensure results is always an array
         } catch (error) {
            console.error('Error fetching data:', error);
            setResults([]); // Ensure results is always an array
         }
      }
   };

   const fetchCategories = async () => {
      if (view === 'generic-products') {
         try {
            const response = await fetch('https://localhost:12354/api/category', {
               headers: {
                  "token": localStorage.getItem('token'),
               },
            });
            const data = await response.json();
            setCategories(data || []); // Ensure categories is always an array
         } catch (error) {
            console.error('Error fetching categories:', error);
            setCategories([]); // Ensure categories is always an array
         }
      }
   };

   useEffect(() => {
      fetchData();
      fetchCategories(); // Fetch categories if generic products view is selected
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
         } else if (view === 'generic-products') {
            url = `https://localhost:12354/api/generic-product${editingItemId ? `/${editingItemId}` : ''}`;
            method = editingItemId ? 'PUT' : 'POST';
         } else {
            return;
         }
         const response = await fetch(url, {
            method: method,
            headers: {
               'Content-Type': 'application/json',
               'token': localStorage.getItem('token')
            },
            body: JSON.stringify(itemDetails),
         });

         if (response.ok) {
            console.log(`${view === 'payment-methods' ? 'PaymentMethod' : view === 'categories' ? 'Category' : 'GenericProduct'} ${editingItemId ? 'updated' : 'created'} successfully`);
            setItemDetails({ name: '', category: '' });
            setEditingItemId(null);
            setNewItemModal(false);
            // Refresh list after adding/updating
            await fetchData();
         } else {
            console.error(`Error ${editingItemId ? 'updating' : 'creating'} ${view === 'payment-methods' ? 'PaymentMethod' : view === 'categories' ? 'Category' : 'GenericProduct'}`);
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
         } else if (view === 'generic-products') {
            url = `https://localhost:12354/api/generic-product/${editingItemId}`;
         } else {
            return;
         }
         const response = await fetch(url, {
            method: 'DELETE',
            headers: {
               'Content-Type': 'application/json',
               'token': localStorage.getItem('token')
            },
         });

         if (response.ok) {
            console.log(`${view === 'payment-methods' ? 'PaymentMethod' : view === 'categories' ? 'Category' : 'GenericProduct'} deleted successfully`);
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
      const sortedResults = [...(results || [])].sort((a, b) => {
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
            <div className="general-button-container">
               <button onClick={() => { setView('payment-methods'); setItemDetails({ name: '', category: '' }); }}>Métodos de Pagamento</button>
               <button onClick={() => { setView('categories'); setItemDetails({ name: '', category: '' }); }}>Categorias</button>
               <button onClick={() => { setView('generic-products'); setItemDetails({ name: '', category: '' }); }}>Produtos Genéricos</button>
            </div>
         </header>
         {view && (
            <div className="General-table-container">
               <button
                  className="newItemButton"
                  onClick={() => { setNewItemModal(true); setItemDetails({ name: '', category: '' }); setEditingItemId(null); }}
               >
                  Novo {view === 'payment-methods' ? 'Método de Pagamento' : view === 'categories' ? 'Categoria' : 'Produto Genérico'}
               </button>
               <table className="General-table">
                  <thead>
                     <tr>
                        <th onClick={handleSort}>
                           Nome
                        </th>
                     </tr>
                  </thead>
                  <tbody>
                     {(results || []).length > 0 ? (
                        (results || []).map((item) => (
                           <tr key={item.id} onClick={() => { setItemDetails(item); setEditingItemId(item.id); setNewItemModal(true); }}>
                              <td>{item.name}</td>
                           </tr>
                        ))
                     ) : (
                        <tr>
                           <td colSpan="1">Nenhum {view === 'payment-methods' ? 'método de pagamento' : view === 'categories' ? 'categoria' : 'produto genérico'} encontrado</td>
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
               <h2>{editingItemId ? `Editar ${view === 'payment-methods' ? 'Método de Pagamento' : view === 'categories' ? 'Categoria' : 'Produto Genérico'}` : `Novo ${view === 'payment-methods' ? 'Método de Pagamento' : view === 'categories' ? 'Categoria' : 'Produto Genérico'}`}</h2>
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
                  {view === 'generic-products' && (
                     <label>
                        Categoria:
                        <select
                           name="category"
                           value={itemDetails.category}
                           onChange={handleInputChange}
                        >
                           <option value="">Selecione uma categoria</option>
                           {(categories || []).map((cat) => (
                              <option key={cat.id} value={cat.id}>{cat.name}</option>
                           ))}
                        </select>
                     </label>
                  )}
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
