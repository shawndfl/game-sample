import GameEngine from 'core/GameEngine';
import { Scene } from 'three';
import { EventNames, MsgManager } from '../core/MsgManager';
import { PropertyController } from './PropertyController';
import {ScenePanel} from './ScenePanel';
import './scss/Designer';
/**
 * The designer is used to manage ui elements around the 3d simulation.
 */
export default class Designer {

    private _container : HTMLElement;
    private _scenePanel : ScenePanel;
    private _properties : PropertyController;

    constructor(root : HTMLElement) { // create a new container for the graphics
        this._container = document.createElement('div');
        this._container.classList.add('designer-container');
        root.append(this._container);        

        this._scenePanel = new ScenePanel(this._container);
        this._properties = new PropertyController(this._container);
        
        MsgManager.subscribe(EventNames.SceneLoaded, (engine: GameEngine)=>{
            this.buildSceneGraph(engine.scene);
        });
    }

    private buildSceneGraph(scene: Scene) {
        console.debug(scene);

        // clean scene graph
        this._scenePanel.clear();        
        // add nodes
        this._scenePanel.addNodes(scene);
    }
}
