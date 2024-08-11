import './App.css';
import Sidebar from './components/Sidebar/sidebar';

function App() {
  return (
    <div className="App">
      <div className="App-glass">
        <Sidebar/>
        <div></div>
        <div></div>

        {/* menu */}
        <div className="menu">
          <div className="menuItem">
              <div>
                  icon
              </div>
              <span>Menu inicial</span>
            </div> 
        </div>
      </div>
    </div>
  );
}

export default App;
