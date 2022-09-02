import {AnimationClip, NumberKeyframeTrack, Quaternion, Vector3, VectorKeyframeTrack} from "three";


function rotation(axis: Vector3, angleFrom: number, angleTo: number, step: number ): number[] {
    const values: number[] = [];
    for(let i =angleFrom; i < angleTo; i+=step){
        const rotation = new Quaternion().setFromAxisAngle(axis, i);
        values.push(...rotation);
    }
    return values;
}

/**
 * Simple idle animation
 */
export class AnimationIdle extends AnimationClip { 
        
   
    /**
     * Creates a simple walk animation for a character
     * @returns 
     */
    constructor() {      
        
        const times = [0, 2, 4];        
        
        const name2 = 'rArm.position';        
        const values2 = [0,0.5,0,  0.0,0.56,0.0,   0,0.5,0];
        const rArmTrack = new NumberKeyframeTrack(name2, times, values2);

        const name3 = 'lArm.position';        
        const values3 = [0,0.5,0,  0.0,0.56,0.0,   0,0.5,0];
        const lArmTrack = new NumberKeyframeTrack(name3, times, values3);

        const name4 = '.customValue';        
        const values4 = [0,0,0];
        const customTrack = new NumberKeyframeTrack(name4, times, values4);

        const tracks = [rArmTrack, lArmTrack, customTrack];        

        super ('idle', 4.0, tracks);
    }
}
