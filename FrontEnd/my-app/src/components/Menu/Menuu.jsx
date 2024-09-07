import './Menu.css'

function Menu() {
   return (
      <div className="Menu">
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?home', '_self')}></button>
            <div className="Menu-icon">🏠</div>
            <span>Home</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?sales', '_self')}></button>
            <div className="Menu-icon">📈</div>
            <span>Vendas</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?clients', '_self')}></button>
            <div className="Menu-icon">👥</div>
            <span>Clientes</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?stock', '_self')}></button>
            <div className="Menu-icon">📦</div>
            <span>Estoque</span>
         </div>
         <div className="MenuItem">
            <button onClick={() => window.open('http://localhost:3000?history', '_self')}></button>
            <div className="Menu-icon">🕒</div>
            <span>Histórico</span>
         </div>
      </div>
   )
}

export default Menu;
