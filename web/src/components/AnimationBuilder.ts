import {AnimationClip, NumberKeyframeTrack, Vector3, VectorKeyframeTrack} from "three";

export class AnimationBuilder { 
    
    /**
     * Creates a simple walk animation for a character
     * @returns 
     */
    static createIdleClip(): AnimationClip {
        //let name1 = '.position[y]';
        //let times1 = [0, 3, 6];
        //let values1 = [0, .02, 0.0];
        //const positionTrack = new NumberKeyframeTrack(name1, times1, values1);

        const name2 = 'body.scale';
        const times2 = [0, 2, 4];
        const values2 = [1,1,1,  1.0,1.2,1.0,   1,1,1];
        const scaleTrack = new NumberKeyframeTrack(name2, times2, values2);

        const name3 = '.customValue';
        const times3 = [0, 2, 4];
        const values3 = [0,0,0];
        const customTrack = new NumberKeyframeTrack(name3, times3, values3);

        const tracks = [scaleTrack, customTrack];        

        return new AnimationClip('idle', 4.0, tracks);
    }
}
