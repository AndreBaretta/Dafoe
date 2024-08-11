import './App.css';
import Sidebar from './components/Sidebar/sidebar';

function App() {
  return (
    <div className="App">
      <div className="App-glass">
        <Sidebar />
        <div className="content">
          {/* Menu */}
          <div className="menu">
            <div className="menuItem">
              <div className="icon">📈</div>
              <span>Vendas</span>
            </div>
            <div className="menuItem">
              <div className="icon">📦</div>
              <span>Estoque</span>
            </div>
            <div className="menuItem">
              <div className="icon">⚙️</div>
              <span>Configurações</span>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
