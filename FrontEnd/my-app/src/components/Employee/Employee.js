import './Employees.css';
import Sidebar from '../Sidebar/sidebar';
import SearchBar from '../SearchBar/SearchBar';
import Menu from '../Menu/Menuu';
import React, { useState, useEffect } from 'react';
import Model from 'react-modal';

Model.setAppElement('#root');

function Employees() {
   const [searchValue, setSearchValue] = useState('');
   const [results, setResults] = useState([]); // Initialized as empty array
   const [newEmployeeScreen, setNewEmployeeScreen] = useState(false);
   const [employeeDetails, setEmployeeDetails] = useState({
      id: '',
      name: '',
      cargo: '',
   });
   const [isPending, setIsPending] = useState(false);
   const [selectedEmployee, setSelectedEmployee] = useState(null); // State to track selected employee
   const [editMode, setEditMode] = useState(false); // Toggle edit modal

   const [sortOrder, setSortOrder] = useState({
      name: 'asc',
   });

   const cargos = ['Manager', 'Developer', 'Designer', 'Tester']; // List of positions

   useEffect(() => {
      const getData = async () => {
         try {
            const response = await fetch(
               `https://localhost:12354/api/employee?name=${searchValue}`
            );
            const data = await response.json();
            // Ensure data is an array before setting it to state
            if (Array.isArray(data)) {
               setResults(data);
            } else {
               console.error('Received data is not an array:', data);
               setResults([]); // Ensure results is always an array
            }
         } catch (error) {
            console.error('Erro ao buscar funcionários:', error);
            setResults([]); // Ensure results is always an array
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
      setEmployeeDetails(employee); // Pre-fill with employee details
      setEditMode(true); // Open the modal in edit mode
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
            setEditMode(false); // Close modal
            setSearchValue(''); // Refetch data
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
            setEditMode(false); // Close modal
            setSearchValue(''); // Refetch data
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
            </div>
               <SearchBar results={searchValue} setResults={setSearchValue} />
            </header>
            <div className="Employees-table-container">
               <table className="Employees-table">
               <thead>
               <thead>
  <tr>
    <th onClick={() => handleSort('name')}>Nome</th>
    <th onClick={() => handleSort('cargo')}>Cargo</th>
  </tr>
</thead>
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
                        <td colSpan="2">No employees found</td>
                     </tr>
                  )}
               </tbody>
            </table>
         </div>

         {/* Modal for adding new employee */}
         <Model
            isOpen={newEmployeeScreen}
            onRequestClose={() => setNewEmployeeScreen(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setNewEmployeeScreen(false)}>X</button>
            <div className="ReactModal__Header">
               Novo Funcionário
               <div className="addEmployee">
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
                     {!isPending && (
                        <button type="button" onClick={submitEmployeeData}>
                           Adicionar
                        </button>
                     )}
                     {isPending && <button disabled>Salvando...</button>}
                  </form>
               </div>
            </div>
         </Model>

         {/* Modal for editing selected employee */}
         <Model
            isOpen={editMode}
            onRequestClose={() => setEditMode(false)}
            className="ReactModal__Content"
            ariaHideApp={false}
         >
            <button className="ReactModal__Close" onClick={() => setEditMode(false)}>X</button>
            <div className="ReactModal__Header">
               Editar Funcionário
               <div className="editEmployee">
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
                           {cargos.map((cargo, index) => (
                              <option key={index} value={cargo}>
                                 {cargo}
                              </option>
                           ))}
                        </select>
                     </label>
                     {!isPending && (
                        <>
                           <button type="button" onClick={handleUpdateEmployee}>
                              Atualizar
                           </button>
                           <button type="button" onClick={handleDeleteEmployee}>
                              Deletar
                           </button>
                        </>
                     )}
                     {isPending && <button disabled>Salvando...</button>}
                  </form>
               </div>
            </div>
         </Model>
      </div>
   );
}

export default Employees;
