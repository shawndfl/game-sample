import GameEngine from 'core/GameEngine';
import { Scene } from 'three';
import { EventNames, MsgManager } from '../core/MsgManager';
import {ScenePanel} from './ScenePanel';
import './scss/Designer';
/**
 * The designer is used to manage ui elements around the 3d simulation.
 */
export default class Designer {

    private _container : HTMLElement;
    private _scenePanel : ScenePanel;

    constructor(root : HTMLElement) { // create a new container for the graphics
        this._container = document.createElement('div');
        this._container.classList.add('designer-container');
        root.append(this._container);

        this._buildView(this._container);

        this._scenePanel = new ScenePanel(this._container);

        MsgManager.subscribe(EventNames.SceneLoaded, (engine: GameEngine)=>{
            this.buildSceneGraph(engine.scene);
        });
    }

    private buildSceneGraph(scene: Scene) {
        // clean scene graph
        // add nodes
    }

    private _buildView(container : HTMLElement) {
        console.debug("Building view for designer...");        
    }
}
