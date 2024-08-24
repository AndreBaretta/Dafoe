import './Home.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';
import Daily from '../Daily/Daily';

function Home() {
  return (
    <div className="Home">
      <div className="Home-glass">
        <header className='Menu-header'>
          <Sidebar />
          <div className='content'>
          <Menu />
          </div>
        </header>
        <Daily />
      </div>
    </div>
  );
}

export default Home;