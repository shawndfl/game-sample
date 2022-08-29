import { AnimationBuilder } from "../components/AnimationBuilder";
import { LineCharacterMesh } from "../components/LineCharacterMesh";
import { AnimationMixer, Vector3 } from "three";
import CharacterComponent from "../components/CharacterComponent";

/**
 * This class will be used to control the character 
 * on screen. It will handle inputs and other events
 * that will be passed to the CharacterComponent.
 */
export default class CharacterController {
    
    private _velocity : Vector3;
    private _moveSpeed: number;     /// in meters / second 
    private _animationMixer: AnimationMixer;

    constructor(private _container: HTMLElement,  private _component: LineCharacterMesh) {

        this._animationMixer = new AnimationMixer(_component);
        const clip = AnimationBuilder.createIdleClip();
        const action = this._animationMixer.clipAction( clip );
        action.play();        

        this._velocity = new Vector3();
        this._moveSpeed = 1.4;

        window.addEventListener("keydown", (e) => {this._keydown(e);});
        window.addEventListener("keyup", (e) => {this._keyup(e);});

    }

    private _keyup(e: KeyboardEvent) {
        if(e.key=='ArrowDown') {
            this._velocity.z = 0;
        } else if(e.key=='ArrowRight') {
            this._velocity.x = 0;
        } else if(e.key=='ArrowLeft') {
            this._velocity.x = 0;
        } else if(e.key=='ArrowUp') {
            this._velocity.z = 0;
        }
    }

    private _keydown(e: KeyboardEvent) {
        if(e.key=='ArrowDown') {
            this._velocity.z = -this._moveSpeed;
        } else if(e.key=='ArrowRight') {
            this._velocity.x = this._moveSpeed;
        } else if(e.key=='ArrowLeft') {
            this._velocity.x = -this._moveSpeed;
        } else if(e.key=='ArrowUp') {
            this._velocity.z = this._moveSpeed;
        }        
    }

    update(dt: number) {
        const currentPos = this._component.position.clone();
        this._animationMixer.update(dt);
        this._component.position.add(this._velocity.multiplyScalar(dt));

        if(this._component.customValue > 0) {
            console.debug(' custom value: ', this._component.customValue);
        }
    }

    dispose() {

    }


}