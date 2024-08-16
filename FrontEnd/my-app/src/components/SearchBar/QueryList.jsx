import OneQuery from "./OneQuery";
import './QueryList.css'
import React, {useState, useEffect} from "react";

const QueryList = ({results,  query, setQuery}) => {
    const [shownResults, setShownResults] = useState ([]);

    useEffect(() => {
        let newShownResults  = [];
        results.forEach((result) => {
           // this code will find the overlap between the query and 
           // the result and split it based on it 
          const fullquery = result.fullquery.replace(/\s+/g, " ");
          const queryWithoutSpaces = query.replace(/\s+/g, " ");
          const indexOfQuery = fullquery
            .toLocaleLowerCase()
            .indexOf(queryWithoutSpaces.toLocaleLowerCase());
          const beforeQuery = fullquery.slice(0, indexOfQuery);
          const afterQuery = fullquery.slice(
            indexOfQuery + queryWithoutSpaces.length
          );
         // only show the result if the overlap actually exists
          if( indexOfQuery >= 0 ){
            newShownResults.push({
                boldedPartBefore: beforeQuery,
                normalText: queryWithoutSpaces,
                boldedPartAfter: afterQuery,
                popularity: result.popularity,
              });
            }
        });
     // Sort the newShownQueries array based on popularity in descending order
     newShownResults.sort((a, b) => b.popularity - a.popularity);
     setShownResults(newShownResults);
   }, [query, results]);

     return (
       <>
         {shownResults.length > 0 && query && (
           <table className="Table">
             <tbody>
               {shownResults.map((shownQuery, key) => {
                 return (
                   <OneQuery
                     key={key}
                     boldedPartBefore={shownQuery.boldedPartBefore}
                     normalText={shownQuery.normalText}
                     boldedPartAfter={shownQuery.boldedPartAfter}
                     query={query}
                      setQuery={setQuery}
                   />
                 );
               })}
             </tbody>
           </table>
         )}
       </>
     );
   };

   export default QueryList;