import './Register.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function Register() {
   return (
      <div className="Register">
         <div className="Register-glass">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
         </div>
      </div>
   );
}

export default Register;