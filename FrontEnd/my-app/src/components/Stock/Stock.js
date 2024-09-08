import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

function Stock() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [newProductScreen, setNewProductScreen] = useState(false);
   const [addStockScreen, setAddStockScreen] = useState(false);
   const [deleteProductScreen, setDeleteProductScreen] = useState(false); 
   const [queryOrder, setQueryOrder] = useState("name");
   const [isPending, setIsPending] = useState(false);
   const [selectedOption, setSelectedOption] = useState('');
   const [productDetails, setProductDetails] = useState({
      manufacturer: '',
      genericProduct: '',
      name: '',
      barcode: '',
      price: '',
      cost: '',
      reference: '',
      quantity: ''
   });
   const [sortOrder, setSortOrder] = useState({
      name: 'asc',
      manufacturer: 'asc',
      price: 'asc',
      cost: 'asc',
      quantity: 'asc'
   });

   const submitData = () => {
      try {
         setIsPending(true);

         fetch('https://localhost:12354/api/product', {
            method: 'POST',
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(productDetails)
         }).then(() => {
            console.log("Produto adicionado");
            setIsPending(false);
            setNewProductScreen(false);
         });
      } catch (error) {
         console.error(error);
      }
   };

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(`https://localhost:12354/api/product?name=${searchValue}`);
            const data = await response.json();
            setResults(data);
         } catch (error) {
            console.error(error);
         }
      };

      getData();
   }, [searchValue, queryOrder]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setProductDetails(prevState => ({
         ...prevState,
         [name]: value
      }));
   };

   const openDPScreen = () => {
      setSearchValue('');
      setDeleteProductScreen(true);
   };

   const handleDelete = () => {
      fetch(`https://localhost:12354/api/product/${selectedOption}`, {
         method: 'DELETE'
      }).then(response => {
         console.log(response);
      }).catch(error => {
         console.error('Error deleting:', error);
      });
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

   return (
      <div className="Stock">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="button-container">
               <button className="newProductButton" onClick={() => setNewProductScreen(true)}>Novo Produto</button>
               <button className="addStockButton" onClick={() => setAddStockScreen(true)}>Atualizar Produto</button>
               <button className="addStockButton" onClick={() => openDPScreen(true)}>Deletar Produto</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Stock-table-container">
            <table className="Stock-table">
               <thead>
                  <tr>
                     <th>Item <button onClick={() => handleSort('name')}>{sortOrder.name === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Fabricante <button onClick={() => handleSort('manufacturer')}>{sortOrder.manufacturer === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Preço <button onClick={() => handleSort('price')}>{sortOrder.price === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Custo <button onClick={() => handleSort('cost')}>{sortOrder.cost === 'asc' ? '↑' : '↓'}</button></th>
                     <th>Quantidade <button onClick={() => handleSort('quantity')}>{sortOrder.quantity === 'asc' ? '↑' : '↓'}</button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.map(item => (
                     <tr key={item.name}>
                        <td>{item.name}</td>
                        <td>{item.manufacturer}</td>
                        <td>{item.price}</td>
                        <td>{item.cost}</td>
                        <td>{item.quantity}</td>
                     </tr>
                  ))}
               </tbody>
            </table>
         </div>
         <Model
            isOpen={newProductScreen}
            onRequestClose={() => setNewProductScreen(false)}
            className="ReactModal__Content"
         >
            <div className='newProduct'>
               <span className='ReactModal__Close' onClick={() => setNewProductScreen(false)}>X</span>
               <h2>Adicionar Novo Produto</h2>
               <form>
                  <label>Nome:
                     <input 
                        type='text' 
                        name='name'
                        value={productDetails.name}
                        onChange={handleInputChange} 
                        placeholder="Digite o nome do produto"
                     />
                  </label>
                  <label>Fabricante:
                     <input 
                        type='text' 
                        name='manufacturer'
                        value={productDetails.manufacturer}
                        onChange={handleInputChange} 
                        placeholder="Digite o fabricante"
                     />
                  </label>
                  <label>Preço:
                     <input 
                        type='text' 
                        name='price'
                        value={productDetails.price}
                        onChange={handleInputChange} 
                        placeholder="Digite o preço"
                     />
                  </label>
                  <label>Custo:
                     <input 
                        type='text' 
                        name='cost'
                        value={productDetails.cost}
                        onChange={handleInputChange} 
                        placeholder="Digite o custo"
                     />
                  </label>
                  <label>Quantidade:
                     <input 
                        type='text' 
                        name='quantity'
                        value={productDetails.quantity}
                        onChange={handleInputChange} 
                        placeholder="Digite a quantidade"
                     />
                  </label>
                  <label>Código de barras:
                     <input 
                        type='text' 
                        name='barcode'
                        value={productDetails.barcode}
                        onChange={handleInputChange} 
                        placeholder="Digite o código de barras"
                     />
                  </label>
                  <label>Referência:
                     <input 
                        type='text' 
                        name='reference'
                        value={productDetails.reference}
                        onChange={handleInputChange} 
                        placeholder="Digite a referência"
                     />
                  </label>
                  <label>Produto genérico:
                     <input 
                        type='text' 
                        name='genericProduct'
                        value={productDetails.genericProduct}
                        onChange={handleInputChange} 
                        placeholder="Digite o produto genérico"
                     />
                  </label>
                  {!isPending && <button type="button" onClick={submitData}>Salvar</button>}
                  {isPending && <button disabled>Salvando...</button>}
               </form>
            </div>
         </Model>
         <Model
            isOpen={addStockScreen}
            onRequestClose={() => setAddStockScreen(false)}
            className="ReactModal__Content"
         >
            <div className='addStock'>
               <span className='ReactModal__Close' onClick={() => setAddStockScreen(false)}>X</span>
               <h2>Atualizar Produto</h2>
               <form>
                  <label>Nome do Produto:
                     <input 
                        type='text' 
                        name='name'
                        onChange={handleInputChange} 
                        placeholder="Digite o nome do produto"
                     />
                  </label>
                  <label>Atributo:
                     <input 
                        type='text' 
                        name='quantity'
                        onChange={handleInputChange} 
                        placeholder="Digite a quantidade"
                     />
                  </label>
                  <label>Novo Atributo:
                     <input 
                        type='text' 
                        name='quantity'
                        onChange={handleInputChange} 
                        placeholder="Digite a quantidade"
                     />
                  </label>
                  <button type="button" onClick={() => setAddStockScreen(false)}>Salvar</button>
               </form>
            </div>
         </Model>
         {/* Modal Deletar Produto */}
<Model
   isOpen={deleteProductScreen}
   onRequestClose={() => setDeleteProductScreen(false)}
   className="ReactModal__Content"
>
   <div className='deleteProduct'>
      <span className='ReactModal__Close' onClick={() => setDeleteProductScreen(false)}>X</span>
      <h2>Deletar Produto</h2> {/* Título centralizado */}
      <form>
                  <label>Selecione o produto a ser deletado:
                     <select onChange={(e) => setSelectedOption(e.target.value)}>
                        {results.map(item => (
                           <option key={item.name} value={item.name}>{item.name}</option>
                        ))}
                     </select>
                  </label>
                  <button type="button" onClick={handleDelete}>Deletar</button>
               </form>
   </div>
</Model>

      </div>
   );
}

export default Stock;
