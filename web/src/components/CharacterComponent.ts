import {CharacterBuilder} from "../builders/CharacterBuilder";
import {
    AnimationClip,
    AnimationMixer,
    BoxGeometry,
    Mesh,
    MeshBasicMaterial,
    Object3D
} from "three";
import {CharacterWalkAnimation} from "../builders/CharacterWalkAnimation";
import GLTFLoader from "../core/GLTFLoader";

export enum CharacterAnimations {
    Walk
}
/**
 * This is a character in the game. It can be a controllable character or an 
 * NPC or an enemy or end boss.
 */
export default class CharacterComponent extends Object3D {


    private _character : CharacterBuilder;        

    constructor(props : CharacterProps) {
        super();

        // build the character
        this._character = new CharacterBuilder({});
        this.add(this._character);        
    }

    load() {
        const loader = new GLTFLoader();
        const path = 'assets/models/character.gltf';
        loader.load(path, (gltf : any) => {
            console.debug("model", gltf);
            this.add(gltf.scene);
        });

    }
}
