import React from 'react'
import Image from '../../assets/images.jpg';
import './Sidebar.css'

const Sidebar = () => {
   return (
      <div className="Sidebar">
         <div className="logo">
            <img src={Image} alt="" />
            <span>
               A<span>FO</span>E
            </span>
         </div>
      </div>
   )
}

export default Sidebar
