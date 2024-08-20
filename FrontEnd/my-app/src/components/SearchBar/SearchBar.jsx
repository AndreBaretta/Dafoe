import { FaSearch} from "react-icons/fa";
import './SearchBar.css'

const SearchBar = ({results, setResults}) => {

   
   return (
      <div className="SearchBar">
        <FaSearch className="icon" />
        <input type="text" value={results} />
   </div>
   );
}

export default SearchBar;