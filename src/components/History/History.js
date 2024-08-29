import './History.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function History() {
   return (
      <div className="History">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
      </div>
   );
}

export default History;