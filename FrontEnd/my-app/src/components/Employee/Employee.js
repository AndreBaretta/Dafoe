import './Employees.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function Employees() {
   const [searchValue, setSearchValue] = useState('');
   const [results, setResults] = useState([]);
   const [newEmployeeScreen, setNewEmployeeScreen] = useState(false);
   const [editEmployeeScreen, setEditEmployeeScreen] = useState(false); // Adicionado
   const [employeeDetails, setEmployeeDetails] = useState({
      id: '',
      name: '',
      cargo: '',
   });
   const [isPending, setIsPending] = useState(false);
   const [selectedEmployee, setSelectedEmployee] = useState(null);
   const [editMode, setEditMode] = useState(false);

   const [sortOrder, setSortOrder] = useState({
      name: 'asc',
   });

   const cargos = ['Manager', 'Developer', 'Designer', 'Tester'];

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(
               `https://localhost:12354/api/employee?name=${searchValue}`
            );
            const data = await response.json();
            if (Array.isArray(data)) {
               setResults(data);
            } else {
               console.error('Received data is not an array:', data);
               setResults([]);
            }
         } catch (error) {
            console.error('Erro ao buscar funcionários:', error);
            setResults([]);
         }
      };

      getData();
   }, [searchValue]);

   const handleInputChange = (e) => {
      const { name, value } = e.target;
      setEmployeeDetails((prevState) => ({
         ...prevState,
         [name]: value,
      }));
   };

   const submitEmployeeData = async () => {
      setIsPending(true);
      try {
         const response = await fetch('https://localhost:12354/api/employee', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(employeeDetails),
         });

         if (response.ok) {
            console.log('Funcionário adicionado com sucesso');
            setEmployeeDetails({
               id: '',
               name: '',
               cargo: '',
            });
            setNewEmployeeScreen(false);
            setSearchValue('');
         } else {
            console.error('Erro ao adicionar funcionário');
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

   const handleRowClick = (employee) => {
      setSelectedEmployee(employee);
      setEmployeeDetails(employee);
      setEditMode(true);
   };

   const handleUpdateEmployee = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/employee/${employeeDetails.id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(employeeDetails),
         });

         if (response.ok) {
            console.log('Funcionário atualizado com sucesso');
            setEditMode(false);
            setSearchValue('');
         } else {
            console.error('Erro ao atualizar funcionário');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   const handleDeleteEmployee = async () => {
      setIsPending(true);
      try {
         const response = await fetch(`https://localhost:12354/api/employee/${employeeDetails.id}`, {
            method: 'DELETE',
         });

         if (response.ok) {
            console.log('Funcionário deletado com sucesso');
            setEditMode(false);
            setSearchValue('');
         } else {
            console.error('Erro ao deletar funcionário');
         }
      } catch (error) {
         console.error('Erro na requisição:', error);
      } finally {
         setIsPending(false);
      }
   };

   return (
      <div className="Employees">
         <header className="Menu-header">
            <Sidebar />
            <Menu />
         </header>
         <header className="SearchBarHeader">
            <div className="button-container">
               <button
                  className="newEmployeeButton"
                  onClick={() => setNewEmployeeScreen(true)}
               >
                  Novo Funcionário
               </button>
               {/* Botão de Editar Funcionário */}
               <button
                  className="editEmployeeButton"
                  onClick={() => setEditEmployeeScreen(true)}
               >
                  Editar Funcionário
               </button>
            </div>
            <SearchBar results={searchValue} setResults={setSearchValue} />
         </header>
         <div className="Employees-table-container">
            <table className="Employees-table">
               <thead>
                  <tr>
                     <th onClick={() => handleSort('name')}>Nome</th>
                     <th onClick={() => handleSort('cargo')}>Cargo</th>
                  </tr>
               </thead>
               <tbody>
                  {Array.isArray(results) && results.length > 0 ? (
                     results.map((employee) => (
                        <tr key={employee.id} onClick={() => handleRowClick(employee)}>
                           <td>{employee.name}</td>
                           <td>{employee.cargo}</td>
                        </tr>
                     ))
                  ) : (
                     <tr>
                        <td colSpan="2">Nenhum funcionário encontrado</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal para adicionar novo funcionário */}
         <Model
            isOpen={newEmployeeScreen}
            onRequestClose={() => setNewEmployeeScreen(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setNewEmployeeScreen(false)}>X</button>
            <div className="ReactModal__Header">
               Novo Funcionário
            </div>
            <div className="newEmployee">
               <form>
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={employeeDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Cargo:
                     <select
                        name="cargo"
                        value={employeeDetails.cargo}
                        onChange={handleInputChange}
                     >
                        <option value="">Selecione</option>
                        {cargos.map((cargo, index) => (
                           <option key={index} value={cargo}>
                              {cargo}
                           </option>
                        ))}
                     </select>
                  </label>
                  {!isPending ? (
                     <button type="button" onClick={submitEmployeeData}>
                        Adicionar
                     </button>
                  ) : (
                     <button disabled>Salvando...</button>
                  )}
               </form>
            </div>
         </Model>

         {/* Modal para editar funcionário */}
         <Model
            isOpen={editEmployeeScreen}
            onRequestClose={() => setEditEmployeeScreen(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setEditEmployeeScreen(false)}>X</button>
            <div className="ReactModal__Header">
               Editar Funcionário
            </div>
            <div className="newEmployee">
               <form>
                  <label>
                     Nome:
                     <input
                        type="text"
                        name="name"
                        value={employeeDetails.name}
                        onChange={handleInputChange}
                     />
                  </label>
                  <label>
                     Cargo:
                     <select
                        name="cargo"
                        value={employeeDetails.cargo}
                        onChange={handleInputChange}
                     >
                        <option value="">Selecione</option>
                        {cargos.map((cargo, index) => (
                           <option key={index} value={cargo}>
                              {cargo}
                           </option>
                        ))}
                     </select>
                  </label>
                  <button type="button" onClick={handleUpdateEmployee}>
                     Atualizar
                  </button>
                  <button type="button" onClick={handleDeleteEmployee}>
                     Deletar
                  </button>
               </form>
            </div>
         </Model>
      </div>
   );
}

export default Employees;
