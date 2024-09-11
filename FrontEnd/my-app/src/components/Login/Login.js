import React, { useState } from "react";
import './Login.css';

const Login = () => {
   const [id, setId] = useState("");
   const [password, setPassword] = useState("");
   const [error, setError] = useState(""); // To show any error messages.

   const handleSubmit = async (event) => {
      event.preventDefault();
   
      try {
         // Sending user credentials using fetch
         const response = await fetch('https://localhost:12354/login', {
            method: 'POST',
            headers: {
               'Content-Type': 'application/json',
            },
            body: JSON.stringify({
               id,           // sending the user id
               password,     // sending the password
            }),
         });
   
         // Check if the response is successful (status 200-299)
         if (!response.ok) {
            throw new Error("Login failed, please try again.");
         }
   
         // Assuming the response contains the token in JSON format
         const token = response.headers.get('Authorization');
   
         // Store the JWT in localStorage
         localStorage.setItem('token', token);
         localStorage.setItem('id', id);
         localStorage.setItem('password', password);
   
         // Redirect the user to the home page after successful login
         window.location.href = 'http://localhost:3000/?home';
   
      } catch (error) {
         // Set error message if login fails
         setError("Invalid credentials, please try again.");
         console.error("Login error:", error);
      }
   };
   

   return (
      <div className="Login">
         <div className="logo-container">
            <div className="logo">
               <img src={require('../../assets/images.jpg')} alt="Logo" />
               <span>
                  A<span>FO</span>E
               </span>
            </div>
         </div>
         <form onSubmit={handleSubmit}>
            <div className="input-field">
               <input 
                  type="number" 
                  placeholder="ID" 
                  value={id} 
                  onChange={(e) => setId(e.target.value)} 
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
            <button type="submit">Entrar</button>
         </form>
         
         {error && <p className="error-message">{error}</p>} {/* Error message */}
         
         <div className="watermark">
            ©dafoeformation - 2024
         </div>
      </div>
   );
};

export default Login;

