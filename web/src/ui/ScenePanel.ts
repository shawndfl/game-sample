
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

        for(let x = 0; x < 100; x++) {            
            this.addNode('node_' + x.toString());
        }
    }

    _createView(container: HTMLElement) {

        // create a main panel
        const root = document.createElement('div');
        root.classList.add('scene-panel');

        // add a panel container        
        root.append(this._sceneGraphList);
        

        container.append(root);
    }

    addNode(node:string) {

        const nodeData = new SceneNodeItem(node);

        // keep track of the node
        this._sceneNodes.push(nodeData);        

        // add the item to the view
        this._sceneGraphList.append(nodeData.itemContainer);
    }
}