import React from "react";
import { FaUser, FaLock } from "react-icons/fa";
import './Login.css'

const Login = () => {
   return(
      <div className="Login">
         <form>
            <div>
               <input type="user" placeholder="Usuário" />
               <FaUser className="icon" />
            </div>
            <div>
               <input type="password" placeholder="Senha" />
               <FaLock className="icon" />
            </div>

            <div className="recall-forget">
               <label>
                  <input type="checkbox" />
                  Lembrar de mim
               </label>
            </div>

            <button>Entrar</button>
         </form>
      </div>
   )
};

export default Login; 