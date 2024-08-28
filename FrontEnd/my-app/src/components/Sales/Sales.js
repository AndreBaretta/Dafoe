import './Sales.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function Sales() {
   return (
      <div className="Sales">
        
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
         
      </div>
   );
}

export default Sales;