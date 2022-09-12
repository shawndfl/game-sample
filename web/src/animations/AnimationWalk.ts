import {
    AnimationClip,
    NumberKeyframeTrack,
    Quaternion,
    Vector3,
    VectorKeyframeTrack
} from "three";

export interface ITrack<T> {    
    time: number,
    value: T

}

export class AnimationData {    
    rotation?: ITrack<number[]>[];
    position?: ITrack<number[]>[];    
    scale?: ITrack<number[]>[]; 
    event?: ITrack<string>[];
}


export class AnimationWalk extends AnimationClip {   

    /**
     * Creates a simple walk animation for a character
     * @returns 
     */
    constructor() {

        const animationData = {
            rotation: [{
                time: 0,
                value:[0,0,0]
            },
        ]
        }
        const times = [0, 2, 4];

        const name2 = 'rArm.rotation';
        const times2 = [0, 2, 4];
        const values2 = AnimationWalk.rot(new Vector3(1, 0, 0), 0, 90, 20);
        const rArmTrack = new NumberKeyframeTrack(name2, times2, values2);

        const name3 = 'lArm.position';
        const times3 = [0, 2, 4];
        const values3 = [
            0,
            0.5,
            0,
            0.0,
            0.56,
            0.0,
            0,
            0.5,
            0
        ];
        const lArmTrack = new NumberKeyframeTrack(name3, times3, values3);

        const name4 = '.customValue';
        const times4 = [0, 2, 4];
        const values4 = [0, 0, 0];
        const customTrack = new NumberKeyframeTrack(name4, times4, values4);

        const tracks = [rArmTrack, lArmTrack, customTrack];

        super('walk', 4.0, tracks);
    }


    /**
     * 
     * @param axis 
     * @param angleFrom 
     * @param angleTo 
     * @param step 
     * @returns 
     */
    static rot(axis : Vector3, angleFrom : number, angleTo : number, step : number): number[]{
        const values: number[] = [];
        for (let i = angleFrom; i < angleTo; i += step) {
            const rotation = new Quaternion().setFromAxisAngle(axis, i);
            values.push(... rotation);
        }
        return values;
    }
}
