import Box from "@mui/material/Box"
import React, {useRef, useEffect} from "react";
import MainScene from 'container/engine/MainScene';

export interface SceneProps {
    width: number;
    height: number;  
    //sceneData: ISceneData;  
}

interface Controls {
    start: () => void,
    stop: () => void
}

/**
 * This function will create a threeJs render and  create the @ref MainScene
 * @param props This is the width and height of the webGL window.
 * @returns Something cool!
 */
export default function ThreeJsInterface(props : SceneProps) {    
    //const sceneData = props.sceneData

    const mount = useRef < HTMLDivElement > (null);
    
    const controls = useRef < Controls > ();                

    useEffect(() => {

        if (mount.current === undefined || mount.current === null) {
            console.error("mount undefined");
            return;
        }

        let width = mount.current.clientWidth;
        let height = mount.current.clientHeight
        let frameId: number;                   
        
        const scene = new MainScene(width, height);

        // Render something awesome!
        const renderScene = () => {
            scene.render();            
        }

        // resize the container
        const handleResize = () => {
            if (mount.current !== undefined && mount.current !== null) {

                width = mount.current.clientWidth
                height = mount.current.clientHeight                                
                scene.resize(width, height);
                
                renderScene();
            }
        }

        const animate = () => {                                 

            renderScene()
            frameId = window.requestAnimationFrame(animate)
        }

        const start = () => {
            if (! frameId) {
                frameId = requestAnimationFrame(animate)
            }
        }

        const stop = () => {
            cancelAnimationFrame(frameId)
            frameId = 0
        };

        // connect dom to WebGL
        mount.current?.appendChild(scene.renderer.domElement);
        scene.initializeControls( mount.current);

        // add resize listener
        window.addEventListener('resize', handleResize);
        start();

        controls.current = {
            start,
            stop                
        }        
        return() => {    
            stop();
            window.removeEventListener('resize', handleResize);
            if (mount.current !== undefined && mount.current !== null) {
                mount.current.removeChild(scene.renderer.domElement)
            }

            scene.dispose();
        }
    }, [])    

    return <Box sx={{
        width:"100%",
        height: "100%"
    }}
        ref={mount}></Box>
}
