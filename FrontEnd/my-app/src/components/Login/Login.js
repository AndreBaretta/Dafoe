import React, { useState } from "react";
import { FaUser, FaLock } from "react-icons/fa";
import './Login.css'

const Login = () => {

   const [username, setUsername] = useState("");
   const [password, setPassword] = useState("");

   const handleSubmit = (event) => {
      event.preventDefault();

      alert("enviando dados " + username + " - " + password);
   };

   return(
      <div className="Login">
         <div className="Login-glass">
            <form onSubmit={handleSubmit}>
               <div className="input-field">
                  <input type="user" placeholder="Usuário" onChange={(e) => setUsername(e.target.value)} />
                  <FaUser className="icon" />
               </div>
               <div className="input-field">
                  <input type="password" placeholder="Senha" onChange={(e) => setPassword(e.target.value)} />
                  <FaLock className="icon" />
               </div>

               <div className="recall">
                  <label>
                     <input type="checkbox" />
                     Lembre de mim
                  </label>
               </div>
               <button onClick={()=>window.open('http://localhost:3000?home','_self')}>Entrar</button>
            </form>
         </div>
      </div>
   )
};

export default Login; 