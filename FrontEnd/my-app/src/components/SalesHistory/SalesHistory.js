import './SalesHistory.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function SalesHistory() {
   return (
      <div className="SalesHistory">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
      </div>
   );
}

export default SalesHistory;