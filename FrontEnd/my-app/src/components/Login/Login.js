import React, { useState } from "react";
import './Login.css';
import Image from '../../assets/images.jpg'; 

const Login = () => {
   const [username, setUsername] = useState("");
   const [password, setPassword] = useState("");

   const handleSubmit = (event) => {
      event.preventDefault();
      alert("enviando dados " + username + " - " + password);
   };

   return (
      <div className="Login">
         <div className="logo-container">
            <div className="logo">
               <img src={Image} alt="Logo" />
               <span>
                  DA<span>FO</span>E
               </span>
            </div>
         </div>

         <form onSubmit={handleSubmit}>
            <div className="input-field">
               <input type="text" placeholder="Usuário" onChange={(e) => setUsername(e.target.value)} />
            </div>
            <div className="input-field">
               <input type="password" placeholder="Senha" onChange={(e) => setPassword(e.target.value)} />
            </div>
            <div className="recall">
               <label>
                  <input type="checkbox" />
                  Lembrar de mim
               </label>
            </div>
            <button type="submit">Entrar</button>
         </form>

         <div className="watermark">
            ©dafoeformation - 2024
         </div>
      </div>
   );
};

export default Login;
