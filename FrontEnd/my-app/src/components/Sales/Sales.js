import './Sales.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function Sales() {
   return (
      <div className="Sales">
         <div className="Sales-glass">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
         </div>
      </div>
   );
}

export default Sales;