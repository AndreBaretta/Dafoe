import './Home.css';
import Sidebar from '../Sidebar/sidebar';
import '../Buttons/Menu.css'
import Daily from '../Daily/Daily';

function Home() {
  return (
    <div className="Home">
      <div className="Home-glass">
        <header className='Home-header'>
          <Sidebar />
          <div className="content">
            {/* Menu */}
            <div className="Menu">
              <div className="MenuItem">
                <button onClick={()=>window.open('http://localhost:3000?sales','_self')}></button>
                <div className="icon">📈</div>
                <span>Vendas</span>
              </div>
              <div className="MenuItem">
                <button onClick={()=>window.open('http://localhost:3000?stock','_self')}></button>
                <div className="icon">📦</div>
                <span>Estoque</span>
              </div>
              <div className="MenuItem">
                <button onClick={()=>window.open('http://localhost:3000?register','_self')}></button>
                <div className="icon">⚙️</div>
                <span>Cadastros</span>
              </div>
            </div>
          </div>
        </header>
        <Daily />
      </div>
    </div>
  );
}

export default Home;