
import { Object3D, Scene } from 'three';
import SceneNodeItem from './SceneNodeItem';
import './scss/ScenePanel';
/**
 * This is a scene graph panel. this panel allows the user to select 
 * a node in the scene graph.
 */
export class ScenePanel {

    private _sceneGraphList: HTMLElement;
    private _sceneNodes: SceneNodeItem[];

    constructor(container: HTMLElement) {

        this._sceneGraphList = document.createElement('ul');
        this._sceneNodes = [];        
        this._createView(container);
    }

    _createView(container: HTMLElement) {

        // create a main panel
        const root = document.createElement('div');
        root.classList.add('scene-panel');

        // add a panel container        
        root.append(this._sceneGraphList);
        

        container.append(root);
    }

    clear() {
        this._sceneNodes = [];
        this._sceneGraphList.innerHTML ='';
    }

    addNodes(node: Object3D) {
        
        this._appendChild(node, 0);
    }

    private _appendChild(node: Object3D, depth: number) {
        const nodeData = new SceneNodeItem(node, depth);

        // keep track of the node
        this._sceneNodes.push(nodeData);        

        // add the item to the view
        this._sceneGraphList.append(nodeData.itemContainer);
        const childDepth = depth+1;

        // append all children
        node.children.forEach((child) =>{
            this._appendChild(child, childDepth);
        });
    }
}