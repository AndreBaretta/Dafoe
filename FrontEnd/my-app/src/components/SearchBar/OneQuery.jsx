import './OneQuery.css'

const OneQuery = ({ boldedPartBefore, normalText, boldedPartAfter , query, setQuery }) => {

   const handleClick = () => {
     setQuery(`${boldedPartBefore}${normalText}${boldedPartAfter}`);
   };

   return (
     <tr className="OneQuery" onClick={handleClick}>
       <td>
         <span className='QueryText'>{boldedPartBefore}</span>{normalText}<span className='QueryText'>{boldedPartAfter}</span>
       </td>
     </tr>
   );
 };

 export default OneQuery;