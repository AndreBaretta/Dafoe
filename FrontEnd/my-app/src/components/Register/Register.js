import React, { useState } from "react";
import './Register.css';

const Register = () => {
   const [username, setUsername] = useState("");
   const [password, setPassword] = useState("");

   const handleSubmit = (event) => {
      event.preventDefault();
      alert("Enviando dados: " + username + " - " + password);
      window.location.href = 'http://localhost:3000?home'; 
   };

   return (
      <div className="Login">
         <div className="logo-container">
            <div className="logo">
               <img src={require('../../assets/images.jpg')} alt="Logo" />
               <span>
                  DA<span>FO</span>E
               </span>
            </div>
         </div>
         <form onSubmit={handleSubmit}>
            <div className="input-field">
               <input 
                  type="text" 
                  placeholder="Usuário" 
                  value={username} 
                  onChange={(e) => setUsername(e.target.value)} 
               />
            </div>
            <div className="input-field">
               <input 
                  type="password" 
                  placeholder="Senha" 
                  value={password} 
                  onChange={(e) => setPassword(e.target.value)} 
               />
            </div>
            <div className="recall">
               <label>
                  <input type="checkbox" />
                  Lembrar de mim
               </label>
            </div>
            <button type="submit">Finalizar Cadastro</button>
         </form>
         <div className="watermark">
            ©dafoeformation - 2024
         </div>
      </div>
   );
};

export default Register;