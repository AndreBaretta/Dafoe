import React, { useState, useEffect } from 'react';
import './User.css';

function User() {
  const [showPasswordForm, setShowPasswordForm] = useState(false);
  const [userDetails, setUserDetails] = useState({
    id: '',
    currentPassword: '',
    newPassword: '',
    confirmPassword: '',
  });
  const [isPending, setIsPending] = useState(false);
  const [showPassword, setShowPassword] = useState(false);

  useEffect(() => {
    // Fetch the current user information
    const fetchUserData = async () => {
      try {
        // For demonstration, using dummy data since no specific API provided
        setUserDetails(prevState => ({
          ...prevState,
          name: localStorage.getItem('id'),
        }));
      } catch (error) {
        console.error('Error fetching user data:', error);
      }
    };
    fetchUserData();
  }, []);

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setUserDetails(prevState => ({
      ...prevState,
      [name]: value,
    }));
  };

  const togglePasswordVisibility = () => {
    setShowPassword(prevState => !prevState);
  };

  const submitData = async () => {
    if (userDetails.newPassword !== userDetails.confirmPassword) {
      alert('Nova senha e confirmação não coincidem');
      return;
    }

    setIsPending(true);
    try {
      const response = await fetch(`https://localhost:12354/api/user/${localStorage.getItem('id')}`, {
        method: 'PUT',
        headers: { 
          'Content-Type': 'application/json',
          "token": localStorage.getItem('token'),
        },
        body: JSON.stringify({
          password: userDetails.currentPassword,
          newPassword: userDetails.newPassword,
        }),
      });
      if(!response.ok){
        alert('Senha nao foi atualizada!'); // Popup confirmation
      }else{
        alert('Senha atualizada com sucesso!'); // Popup confirmation
      }

    } catch (error) {
      console.error('Erro ao atualizar a senha:', error);
    } finally {
      setIsPending(false);
    }
  };

  // Function to navigate back to the home screen
  const goToHomeScreen = () => {
    window.open('http://localhost:3000?home', '_self');
  };

  const goToLogin = () => {
    window.open('http://localhost:3000?self', '_self');
  }

  return (
    <div className="user-profile">
      <h2>Editar Perfil</h2>
      {!showPasswordForm ? (
        <>
          <button 
            className="change-password-button" 
            onClick={() => setShowPasswordForm(true)}
          >
            Mudar Senha
          </button>
          <button className="back-to-home-button" onClick={goToHomeScreen}>
            Voltar para a Tela Inicial
          </button>
          <button className="back-to-login" onClick={goToLogin}>
            Logout
          </button>
        </>
      ) : (
        <form>
          <label>Senha Atual:
            <input 
              type={showPassword ? "text" : "password"} // Toggle between text and password
              name="currentPassword" 
              value={userDetails.currentPassword} 
              onChange={handleInputChange} 
              placeholder="Digite a senha atual"
            />
          </label>
          <label>Nova Senha:
            <input 
              type={showPassword ? "text" : "password"} // Toggle between text and password
              name="newPassword" 
              value={userDetails.newPassword} 
              onChange={handleInputChange} 
              placeholder="Digite a nova senha"
            />
          </label>
          <label>Confirmar Nova Senha:
            <input 
              type={showPassword ? "text" : "password"} // Toggle between text and password
              name="confirmPassword" 
              value={userDetails.confirmPassword} 
              onChange={handleInputChange} 
              placeholder="Confirme a nova senha"
            />
          </label>
          <button 
            type="button" 
            onClick={togglePasswordVisibility} 
            className="toggle-password-button"
          >
            {showPassword ? 'Esconder' : 'Mostrar'} Senha
          </button>
          <button 
            type="button" 
            onClick={submitData} 
            disabled={isPending}
          >
            {isPending ? 'Salvando...' : 'Salvar'}
          </button>
          <button 
            type="button" 
            onClick={() => setShowPasswordForm(false)}
            className="back-to-settings-button"
          >
            Voltar
          </button>
        </form>
      )}
    </div>
  );
}

export default User;
