import './Home.css';
import Sidebar from '../Sidebar/sidebar';
import Menu from '../Menu/Menuu';

function Home() {
   return (
      <div className="Home">
            <header className='Menu-header'>
               <Sidebar />
               <Menu />
            </header>
      </div>
   );
}

export default Home;