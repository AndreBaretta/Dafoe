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
   const [queryOrder, setQueryOrder] = useState("name");
   const [isPendind, setIsPending] = useState(false)
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

   const submitData = () => {
      try {
         setIsPending(true)

         fetch('https://localhost:12354/api/product', {
            method: 'POST',
            headers: {"Content-Type" : "application/json"},
            body: JSON.stringify(productDetails)
         }).then(() => {
            console.log("produto adicionado")
            isPendind(false)
         })
      } catch (error) {
         console.error(error);
         setNewProductScreen(false);
      }
   }
   //implementar assincronismo


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

   return (
      <div className="Stock">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="button-container">
               <button className="newProductButton" onClick={() => setNewProductScreen(true)}>Novo Produto</button>
               <button className="addStockButton" onClick={() => setAddStockScreen(true)}>Adicionar Estoque</button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Stock-table-container">
            <table className="Stock-table">
               <thead>
                  <tr>
                     <th>Nome <button onClick={() => setQueryOrder('name')}></button></th>
                     <th>Fabricante <button onClick={() => setQueryOrder('name')}></button></th>
                     <th>Preço <button onClick={() => setQueryOrder('name')}></button></th>
                     <th>Custo <button onClick={() => setQueryOrder('name')}></button></th>
                     <th>Quantidade <button onClick={() => setQueryOrder('name')}></button></th>
                  </tr>
               </thead>
               <tbody>
                  {results.map((item) => (
                     <tr key={item.id}>
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
                  <label>Referencia:
                     <input 
                        type='text' 
                        name='reference'
                        value={productDetails.reference}
                        onChange={handleInputChange} 
                        placeholder="Digite a referencia"
                     />
                  </label>
                  <label>Produto generico:
                     <input 
                        type='text' 
                        name='genericProduct'
                        value={productDetails.genericProduct}
                        onChange={handleInputChange} 
                        placeholder="Digite o produto generico"
                     />
                  </label>
                  { !isPendind && <button type="button" onClick={() => submitData()}>Salvar</button> }
                  { isPendind && <button disabled>Salvando...</button>}
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
               <h2>Adicionar Estoque</h2>
               <form>
                  <label>Nome do Produto:
                     <input 
                        type='text' 
                        name='name'
                        onChange={handleInputChange} 
                        placeholder="Digite o nome do produto"
                     />
                  </label>
                  <label>Quantidade:
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
      </div>
   );
}

export default Stock;
