import './Stock.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';
import Select from 'react-select';

function Stock() {
   const [searchValue, setSearchValue] = useState("");
   const [results, setResults] = useState([]);
   const [manufacturers, setManufacturers] = useState([]);
   const [genericProducts, setGenericProducts] = useState([]);
   const [newProductScreen, setNewProductScreen] = useState(false);
   const [editProductScreen, setEditProductScreen] = useState(false);
   const [deleteProductScreen, setDeleteProductScreen] = useState(false); 
   const [selectedProduct, setSelectedProduct] = useState(null);
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
   const [isPending, setIsPending] = useState(false);

   useEffect(() => {
      const fetchData = async () => {
         try {
            const productResponse = await fetch(`https://localhost:12354/api/product?name=${searchValue}`, {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const productData = await productResponse.json();
            setResults(productData);

            const manufacturerResponse = await fetch('https://localhost:12354/api/manufacturer', {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            const manufacturerData = await manufacturerResponse.json();
            setManufacturers(manufacturerData);

            const genericProductResponse = await fetch(`https://localhost:12354/api/generic-product?name=${searchValue}`, {
               headers: {
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token')
               },
            });
            let genericProductData = await genericProductResponse.json();            
            setGenericProducts(genericProductData)
         } catch (error) {
            console.error(error);
         }
      };

      fetchData();
   }, [searchValue]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setProductDetails(prevState => ({
         ...prevState,
         [name]: value
      }));
   };

   const handleEditClick = (product) => {
      setProductDetails(product);
      setSelectedProduct(product.id);
      setEditProductScreen(true);
   };

   const handleDelete = async () => {
      try {
         await fetch(`https://localhost:12354/api/product/${selectedProduct}`, {
            method: 'DELETE',
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
         });
         console.log('Produto deletado');
         setEditProductScreen(false);
         setDeleteProductScreen(false);
         setSelectedProduct(null);
         // Refresh product list
         const response = await fetch(`https://localhost:12354/api/product?name=${searchValue}`);
         const data = await response.json();
         setResults(data);
      } catch (error) {
         console.error('Erro ao deletar:', error);
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

   const submitData = async () => {
      try {
         setIsPending(true);
         if (selectedProduct) {
            // Update existing product
            await fetch(`https://localhost:12354/api/product/${selectedProduct}`, {
               method: 'PUT',
               headers: { "Content-Type": "application/json" },
               headers: {"token" : localStorage.getItem('token')},
               body: JSON.stringify(productDetails)
            });
            console.log("Produto atualizado");
         } else {
            // Create new product
            await fetch('https://localhost:12354/api/product', {
               method: 'POST',
               headers: { "Content-Type": "application/json" },
               headers: {"token" : localStorage.getItem('token')},
               body: JSON.stringify(productDetails)
            });
            console.log("Produto adicionado");
         }
         setIsPending(false);
         setNewProductScreen(false);
         setEditProductScreen(false);
         setProductDetails({
            manufacturer: '',
            genericProduct: '',
            name: '',
            barcode: '',
            price: '',
            cost: '',
            reference: '',
            quantity: ''
         });
         // Refresh product list
         const response = await fetch(`https://localhost:12354/api/product?name=${searchValue}`, {
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
         });
         const data = await response.json();
         setResults(data);
      } catch (error) {
         console.error(error);
         setIsPending(false);
      }
   };

   const getManufacturerName = (id) => {
      const manufacturer = manufacturers.find(m => m.id === id);
      return manufacturer ? manufacturer.name : 'N/A';
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
                  {results.length > 0 ? (
                     results.map(item => (
                        <tr key={item.id} onClick={() => handleEditClick(item)}>
                           <td>{item.name}</td>
                           <td>{getManufacturerName(item.manufacturer)}</td>
                           <td>{item.price}</td>
                           <td>{item.cost}</td>
                           <td>{item.quantity}</td>
                        </tr>
                     ))
                  ) : (
                     <tr><td colSpan="5">Nenhum produto encontrado</td></tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal Adicionar Novo Produto */}
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
                     <Select 
                        name='manufacturer'
                        options={manufacturers.map(m => ({ value: m.id, label: m.name }))}
                        onChange={(option) => setProductDetails(prevState => ({ ...prevState, manufacturer: option.value }))}
                        value={manufacturers.find(m => m.id === productDetails.manufacturer) ? { value: productDetails.manufacturer, label: manufacturers.find(m => m.id === productDetails.manufacturer).name } : null}
                        placeholder="Selecione o fabricante"
                     />
                  </label>
                  <label>Produto Genérico:
                     <Select 
                        name='genericProduct'
                        options={genericProducts.map(gp => ({value: gp.id, lavel: gp.name}))} 
                        onChange={(option) => setProductDetails(prevState => ({ ...prevState, genericProduct: option.value }))}
                        value={genericProducts.find(gp => gp.value === productDetails.genericProduct) ? {value: productDetails.genericProduct, lavel: genericProducts.find(gp => gp.id == productDetails.genericProduct).name} : null}
                        placeholder="Selecione o produto genérico"
                     />
                  </label>
                  <label>Referência:
                     <input 
                        type='text' 
                        name='reference'
                        value={productDetails.reference}
                        onChange={handleInputChange} 
                        placeholder="Digite a referência do produto"
                     />
                  </label>
                  <label>Código de Barras:
                     <input 
                        type='text' 
                        name='barcode'
                        value={productDetails.barcode}
                        onChange={handleInputChange} 
                        placeholder="Digite o código de barras"
                     />
                  </label>
                  <label>Preço:
                     <input 
                        type='number' 
                        name='price'
                        value={productDetails.price}
                        onChange={handleInputChange} 
                        placeholder="Digite o preço"
                     />
                  </label>
                  <label>Custo:
                     <input 
                        type='number' 
                        name='cost'
                        value={productDetails.cost}
                        onChange={handleInputChange} 
                        placeholder="Digite o custo"
                     />
                  </label>
                  <label>Quantidade:
                     <input 
                        type='number' 
                        name='quantity'
                        value={productDetails.quantity}
                        onChange={handleInputChange} 
                        placeholder="Digite a quantidade"
                     />
                  </label>
                  <button type="button" onClick={submitData} disabled={isPending}>
                     {isPending ? 'Salvando...' : 'Salvar'}
                  </button>
               </form>
            </div>
         </Model>
      </div>
   );
}

export default Stock;
