import { AnimationClip, NumberKeyframeTrack, Vector3, VectorKeyframeTrack } from "three";

export class AnimationBuilder {
    
    /**
     * Creates a simple walk animation for a character
     * @returns 
     */
    static createIdleClip(): AnimationClip {
        const name = '.position[y]';
        const times = [0,1,2];
        const values = [0, .2, 0.0];
        const positionTrack = new NumberKeyframeTrack(name, times, values);

        const tracks = [positionTrack];

        return new AnimationClip('idle', 2.0, tracks);
    }
}