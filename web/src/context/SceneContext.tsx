
import React from "react"
import { createContext } from "react";

export enum DayState {
    Day,
    Night,
    Loop
}

export enum CameraState {
    Free,
    Top,
    Loop
}

/**
 * This is the scene data that will be shared
 * between react components and the main scene.
 */
export interface ISceneData {
    dayState: DayState,
    cameraState: CameraState,    
}

/**
 * The context that will be pass to other
 * react components. The set state function
 * will be used to allow child components to set
 * the state
 */
export interface ISceneProviderProps {
    data?: ISceneData,
    setState: (data:ISceneData) => void,
}

/**
 * The default provider value
 */
export class DefaultProviderValue implements ISceneProviderProps {

    data = undefined;    
    setState = (data: ISceneData) => {
        //NOP
    };
}
  

/**
 * The provider context for the scene
 */
export const MainSceneContext = createContext<ISceneProviderProps>(new DefaultProviderValue());