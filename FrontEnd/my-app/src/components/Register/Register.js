import './Register.css';
import Sidebar from '../Sidebar/sidebar';
import '../Buttons/BackButton.css'

function Register() {
  return (
    <div className="Register">
      <div className="Register-glass">
        <div className="backButtonDisplay">
            <div className="backButton">
              <button onClick={()=>window.open('http://localhost:3000?home','_self')}></button>
              <div className="icon">⬅</div>
              <span>voltar</span>
            </div>
          </div>
        <Sidebar />
      </div>
    </div>
  );
}

export default Register;