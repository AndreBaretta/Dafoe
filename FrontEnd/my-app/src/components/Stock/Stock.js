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
            const genericProductData = await genericProductResponse.json();          
            setGenericProducts(genericProductData);
         } catch (error) {
            console.error(error);
         }
      };

      fetchData();
   }, [searchValue]);

   const resetProductDetails = () => {
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
      setSelectedProduct('');
   };

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setProductDetails(prevState => ({
         ...prevState,
         [name]: value
      }));
   };

   const handleEditClick = (product) => {
      setProductDetails({
         name: product.name,
         barcode: product.barcode,
         manufacturer: product.manufacturer,
         genericProduct: product.genericProduct,
         price: product.price,
         cost: product.cost,
         reference: product.reference,
         quantity: product.quantity
      });
      setSelectedProduct(product.id);
      setEditProductScreen(true);
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
         const response = await fetch(`https://localhost:12354/api/product?name=${searchValue}`, {
            headers: {
               "Content-Type": "application/json",
               "token" : localStorage.getItem('token')
            },
         });
         const data = await response.json();
         setResults(data);
         setIsPending(false);
         setNewProductScreen(false);
         setEditProductScreen(false);
         resetProductDetails();
         setSelectedProduct(null);
      } catch (error) {
         console.error('Erro ao deletar:', error);
      }
   };

   const submitData = async () => {
      try {
         if(!isBarcodeUnique(productDetails.barcode)){
            alert("Código de barras já existe");
            return false;
         }
         if(!isReferenceUnique(productDetails.reference)){
            alert("Referencia já existe");
            return false;
         }
         setIsPending(true);
         if (selectedProduct) {
            // Update existing product
            await fetch(`https://localhost:12354/api/product/${selectedProduct}`, {
               method: 'PUT',
               headers: { 
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token') 
               },
               body: JSON.stringify({
                  ...productDetails,
                  manufacturer: String(productDetails.manufacturer),
                  genericProduct: String(productDetails.genericProduct),
                  cost: String(productDetails.cost),
                  id: String(productDetails.id),
                  price: String(productDetails.price),
                  quantity: String(productDetails.quantity)
               }),
            });
            console.log("Produto atualizado");
            setSelectedProduct(null); 
         } else {
            // Create new product
            await fetch('https://localhost:12354/api/product', {
               method: 'POST',
               headers: { 
                  "Content-Type": "application/json",
                  "token" : localStorage.getItem('token') 
               },
               body: JSON.stringify({
                  ...productDetails,
                  manufacturer: String(productDetails.manufacturer),
                  genericProduct: String(productDetails.genericProduct),
               }),
            });
            console.log("Produto adicionado");
         }
         setIsPending(false);
         setNewProductScreen(false);
         setEditProductScreen(false);
         resetProductDetails(); // Reset product details after submission
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

   const getGenericProductName = (id) => {
      const genericProduct = genericProducts.find(gp => gp.id === id);
      return genericProduct ? genericProduct.name : 'N/A';
   };

   const isBarcodeUnique = (barcode) => {
      return !results.some(product => product.barcode === barcode);
   };

   const isReferenceUnique = (reference) => {
      return !results.some(product => product.reference == reference);
   }
   

   return (
      <div className="Stock">
         <header className='Menu-header'>
            <Sidebar />
            <Menu />
         </header>
         <header className='SearchBarHeader'>
            <div className="stock-button-container">
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
                     <tr>
                        <td colSpan="5">Nenhum resultado encontrado</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal Novo Produto */}
         <Model
            isOpen={newProductScreen}
            onRequestClose={() => {
               setNewProductScreen(false);
               resetProductDetails(); // Reset product details when closing
            }}
            className="ReactModal__Content"
         >
            <div className='newProduct'>
               <span className='ReactModal__Close' onClick={() => {
                  setNewProductScreen(false);
                  resetProductDetails(); // Reset product details when closing
               }}>X</span>
               <h2>Adicionar Novo Produto</h2>
               <form>
                  <label>Nome:
                     <input 
                        type='text' 
                        name='name'
                        value={productDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Código de barras:
                     <input 
                        type='text' 
                        name='barcode'
                        value={productDetails.barcode}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Fabricante:
                     <Select
                        options={manufacturers.map(m => ({ value: m.id, label: m.name }))}
                        onChange={(selectedOption) => setProductDetails(prevState => ({ ...prevState, manufacturer: selectedOption.value }))}
                        value={manufacturers.find(m => m.id === productDetails.manufacturer) ? { value: productDetails.manufacturer, label: manufacturers.find(m => m.id === productDetails.manufacturer).name } : null}
                     />
                  </label>
                  <label>Produto Genérico:
                     <Select
                        options={genericProducts.map(gp => ({ value: gp.id, label: gp.name }))}
                        onChange={(selectedOption) => setProductDetails(prevState => ({ ...prevState, genericProduct: selectedOption.value }))}
                        value={genericProducts.find(gp => gp.id === productDetails.genericProduct) ? { value: productDetails.genericProduct, label: genericProducts.find(gp => gp.id === productDetails.genericProduct).name } : null}
                     />
                  </label>
                  <label>Preço:
                     <input 
                        type='number' 
                        name='price'
                        value={productDetails.price}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Custo:
                     <input 
                        type='number' 
                        name='cost'
                        value={productDetails.cost}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Referência:
                     <input 
                        type='text' 
                        name='reference'
                        value={productDetails.reference}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Quantidade:
                     <input 
                        type='number' 
                        name='quantity'
                        value={productDetails.quantity}
                        onChange={handleInputChange}
                     />
                  </label>
                  <button type="button" onClick={submitData}>
                     {selectedProduct ? 'Atualizar' : 'Adicionar'}
                  </button>
                  {isPending && <p>Processing...</p>}
               </form>
            </div>
         </Model>

         {/* Modal Editar Produto */}
         <Model
            isOpen={editProductScreen}
            onRequestClose={() => {
               setEditProductScreen(false);
               resetProductDetails(); // Reset product details when closing
            }}
            className="ReactModal__Content"
         >
            <div className='editProduct'>
               <span className='ReactModal__Close' onClick={() => {
                  setEditProductScreen(false);
                  resetProductDetails(); // Reset product details when closing
               }}>X</span>
               <h2>Editar Produto</h2>
               <form>
                  <label>Nome:
                     <input 
                        type='text' 
                        name='name'
                        value={productDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Código de barras:
                     <input 
                        type='text' 
                        name='barcode'
                        value={productDetails.barcode}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Fabricante:
                     <Select
                        options={manufacturers.map(m => ({ value: m.id, label: m.name }))}
                        onChange={(selectedOption) => setProductDetails(prevState => ({ ...prevState, manufacturer: selectedOption.value }))}
                        value={manufacturers.find(m => m.id === productDetails.manufacturer) ? { value: productDetails.manufacturer, label: manufacturers.find(m => m.id === productDetails.manufacturer).name } : null}
                     />
                  </label>
                  <label>Produto Genérico:
                     <Select
                        options={genericProducts.map(gp => ({ value: gp.id, label: gp.name }))}
                        onChange={(selectedOption) => setProductDetails(prevState => ({ ...prevState, genericProduct: selectedOption.value }))}
                        value={genericProducts.find(gp => gp.id === productDetails.genericProduct) ? { value: productDetails.genericProduct, label: genericProducts.find(gp => gp.id === productDetails.genericProduct).name } : null}
                     />
                  </label>
                  <label>Preço:
                     <input 
                        type='number' 
                        name='price'
                        value={productDetails.price}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Custo:
                     <input 
                        type='number' 
                        name='cost'
                        value={productDetails.cost}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Referência:
                     <input 
                        type='text' 
                        name='reference'
                        value={productDetails.reference}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>Quantidade:
                     <input 
                        type='number' 
                        name='quantity'
                        value={productDetails.quantity}
                        onChange={handleInputChange}
                     />
                  </label>
                  <button type="button" onClick={submitData}>
                     Atualizar
                  </button>
                  <button type="button" onClick={() => {
                     setDeleteProductScreen(true);
                     setEditProductScreen(false);
                  }}>
                     Excluir
                  </button>
                  {isPending && <p>Processing...</p>}
               </form>
            </div>
         </Model>

         {/* Modal Deletar Produto */}
         <Model
            isOpen={deleteProductScreen}
            onRequestClose={() => {
               setDeleteProductScreen(false);
               resetProductDetails(); // Reset product details when closing
            }}
            className="ReactModal__Content"
         >
            <div className='deleteProduct'>
               <span className='ReactModal__Close' onClick={() => {
                  setDeleteProductScreen(false);
                  resetProductDetails(); // Reset product details when closing
               }}>X</span>
               <h2>Confirmar Exclusão</h2>
               <p>Tem certeza de que deseja excluir este produto?</p>
               <button type="button" onClick={handleDelete}>
                  Confirmar
               </button>
               <button type="button" onClick={() => {
                  setDeleteProductScreen(false);
                  resetProductDetails(); // Reset product details when closing
               }}>
                  Cancelar
               </button>
            </div>
         </Model>
      </div>
   );
}

export default Stock;
