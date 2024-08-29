import './Register.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function Register() {
   return (
      <div className="Register">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
      </div>
   );
}

export default Register;