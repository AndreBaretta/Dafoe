import img from './images.jpg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="Name-header">
        <p>DAFOE</p>
      </header>
      <header className="App-header">
        <img src={img} className="App-logo" alt="logo" />
        <p>Facilitando suas vendas</p>
        <a
          className="App-link"
          href="https://github.com/AndreBaretta/Dafoe"
          target="_blank"
          rel="noopener noreferrer"
        >
          Veja nosso código
        </a>
      </header>
    </div>
  );
}

export default App;
