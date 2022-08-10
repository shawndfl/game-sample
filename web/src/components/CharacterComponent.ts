import { CharacterBuilder } from "../builders/CharacterBuilder";
import { AnimationClip, AnimationMixer, BoxGeometry, Mesh, MeshBasicMaterial, Object3D } from "three";
import { CharacterWalkAnimation } from "../builders/CharacterWalkAnimation";

export enum CharacterAnimations {
    Walk,
}
/**
 * This is a character in the game. It can be a controllable character or an 
 * NPC or an enemy or end boss.
 */
export default class CharacterComponent extends Object3D {
    

    private _character: CharacterBuilder;    
    private _animationClip: CharacterWalkAnimation;
    private _mixer: AnimationMixer;

    constructor(props: CharacterProps) {
        super();

        // build the character
        this._character = new CharacterBuilder({});
        this.add(this._character);        

        // create the animations
        this._animationClip = new CharacterWalkAnimation();                
        this._mixer = new AnimationMixer(this);
    }

    play(animation: CharacterAnimations) {

    }

   update(dt: number) {
       this._mixer.update(dt);
   }
}