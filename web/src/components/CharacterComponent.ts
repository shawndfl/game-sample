import { CharacterBuilder } from "../builders/CharacterBuilder";
import { BoxGeometry, Mesh, MeshBasicMaterial, Object3D } from "three";

/**
 * This is a character in the game. It can be a controllable character or an 
 * NPC or an enemy or end boss.
 */
export default class CharacterComponent extends Object3D {
    
    private _character: CharacterBuilder;    

    constructor(props: CharacterProps) {
        super();
        this._character = new CharacterBuilder({});
        this.add(this._character);        
    }
}