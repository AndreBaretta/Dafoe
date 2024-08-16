import { FaSearch} from "react-icons/fa";
import './SearchBar.css'

const SearchBar = ({query, setQuery}) => {

   
   return (
      <div className="SearchBar">
        <FaSearch className="icon" />
        <input type="text" value={query} />
   </div>
   );
}

export default SearchBar;