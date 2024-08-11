import React from 'react'
import Image from '../../images.jpg';
import './Sidebar.css'
const Sidebar = () => {
  return (
    <div className="Sidebar">
        {/*logo*/}
        <div className="logo">
            <img src={Image} alt=""/>
            <span>
                Da<span>fo</span>e
            </span>
        </div>
    </div>
  )
}

export default Sidebar