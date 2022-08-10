import { AnimationClip, KeyframeTrack, Vector3 } from "three";

/**
 * Creates a walk animation
 */
export class CharacterWalkAnimation extends AnimationClip {    

    constructor() {        
        super("walk", 1.0);

        this.tracks = [];
        const time: number[] = [];
        const position: Vector3[] = [];        

        time.push(0);
        position.push(new Vector3(0,0,0));

        time.push(.5);
        position.push(new Vector3(0,1,0));

        time.push(1);
        position.push(new Vector3(0,0,0));

        this.tracks.push(new KeyframeTrack("position",time, position));
    }    

}