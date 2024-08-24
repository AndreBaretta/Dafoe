import './History.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function History() {
  return (
    <div className="History">
      <div className="History-glass">
        <header className='Menu-header'>
        <Sidebar />
        <Menu />
        </header>
      </div>
    </div>
  );
}

export default History;