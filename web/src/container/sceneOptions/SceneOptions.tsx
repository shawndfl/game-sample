import SpeedDial from '@mui/material/SpeedDial';
import SpeedDialIcon from '@mui/material/SpeedDialIcon';
import SpeedDialAction from '@mui/material/SpeedDialAction';
import CameraAltIcon from '@mui/icons-material/CameraAlt';
//import ThreeDRotationIcon from '@mui/icons-material/ThreeDRotation';
//import BrightnessMediumIcon from '@mui/icons-material/BrightnessMedium';
//import KitchenIcon from '@mui/icons-material/Kitchen';
import LightbulbIcon from '@mui/icons-material/Lightbulb';
import TableRestaurantIcon from '@mui/icons-material/TableRestaurant';
import { useContext } from 'react';
import { MainSceneContext } from 'context/SceneContext';

/**
 * This component will create a speed dial component that allows the 
 * user to select different options that affect the scene.
 */
export default function SceneOptions() {  

  //const sceneData: props.sceneData;

  const actions = [
    { icon: <CameraAltIcon />, name: 'Rotate', handler: rotate },
    { icon: <LightbulbIcon />, name: 'Lighting', handler: adjustLight  },  
    { icon: <TableRestaurantIcon />, name: 'Add Table', handler: addTable  },  
  ];

  function addTable() {
    console.debug("Add table");
  }

  function rotate() {
    console.debug("rotate");
  }

  function adjustLight() {

    /*
    // set the new state to cycle through night and day and loop
    let newState = sceneContext.data;
    if(newState.dayState  === DayState.Day) {
      newState.dayState = DayState.Loop;

    } else if(newState.dayState  === DayState.Loop) {
      newState.dayState = DayState.Night;
    } else {
      newState.dayState = DayState.Day;
    }    
    sceneContext.setState(newState);
    */
  }

  return   <SpeedDial
    ariaLabel="SpeedDial basic example"
    sx={{ position: 'absolute', bottom: 16, right: 16 }}
    icon={<SpeedDialIcon />}
  >
    {actions.map((action) => (
      <SpeedDialAction
        key={action.name}
        icon={action.icon}
        tooltipTitle={action.name}
        onClick ={action.handler}
      />
    ))}
  </SpeedDial>  
}