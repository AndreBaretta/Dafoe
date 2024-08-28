import { FaSearch } from "react-icons/fa";
import './SearchBar.css'

const SearchBar = ({ results, setResults }) => {


   return (
      <div className="SearchBar">
         <FaSearch className="icon" />
         <input type="search" value={results} onChange={(e) => setResults(e.target.value)} />
      </div>
   );
}

export default SearchBar;