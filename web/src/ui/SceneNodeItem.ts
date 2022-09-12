import { Object3D } from 'three';
import expand from '../svgs/solid/square-plus.svg'

/**
 * This is a ui scene node item. This node can have children or not.
 * and be expanded or not.
 * It will also have an icon for the type of node it is.
 */
export default class SceneNodeItem {

    private _itemContainer : HTMLLIElement;
    private _headerNode : HTMLElement;    
    private _detailNode : HTMLElement;    
    private _expandNode: HTMLImageElement;
    private _expanded : boolean;
    private _children : SceneNodeItem[];

    /**
     * get the header text
     */
    get HeaderText(): string {
        return this._headerNode.innerText;
    }

    /**
     * Gets the children for this scene node
     */
    get children(): SceneNodeItem[]{
        return this._children;
    }

    /**
     * gets the html container for this item.
     * A calling class will want to use this to add 
     * it to the dom.
     */
    get itemContainer(): HTMLLIElement {
        return this._itemContainer;
    }

    constructor(node: Object3D, depth: number) {
        this._children = [];
        this._expanded = false;
        this._itemContainer = document.createElement('li');
        this._itemContainer.style.marginLeft = (depth * 10) + 'px';

        this._expandNode = document.createElement('img');
        this._expandNode.classList.add('expand');
        this._expandNode.src = expand;

        this._headerNode = document.createElement('h2');        
        this._headerNode.innerHTML = node.name;

        this._detailNode = document.createElement('span');
        this._detailNode.innerHTML = node.type;               

        this._itemContainer.append(this._expandNode, this._headerNode, this._detailNode);
    }

    decorateItem() {
        
    }

    setHeaderText(name : string) {
        this._headerNode.innerHTML = name;
    }

}
