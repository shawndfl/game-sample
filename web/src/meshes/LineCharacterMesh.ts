import { Object3D, Vector3 } from "three";
import {LineMesh } from './LineMesh';
import { CircleMesh } from "./CircleMesh";

export class LineCharacterMesh extends Object3D {

    head : CircleMesh;
    body : LineMesh;
    rArm : LineMesh;
    lArm : LineMesh;
    rLeg : LineMesh;
    lLeg : LineMesh;

    customValue : number;

    constructor() {
        super();
        this.name = 'character'
        this.customValue = 0;

        this.body = new LineMesh({
            start: new Vector3(0, .6, 0),
            end: new Vector3(0, 0, 0),
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.body.name = 'body';
        this.body.position.set(0, .5, 0);
        this.add(this.body);

        this.head = new CircleMesh({
            center: new Vector3(0, .1, 0),
            size: .1,
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.head.name = 'head';
        this.head.position.set(0, .6, 0)
        this.body.add(this.head);

        this.rArm = new LineMesh({
            start: new Vector3(0, 0, 0),
            end: new Vector3(-.3, -.3, 0),
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.rArm.name = 'rArm';
        this.rArm.position.set(0, .5, 0);
        this.body.add(this.rArm);

        this.lArm = new LineMesh({
            start: new Vector3(0, 0, 0),
            end: new Vector3(.3, -.3, 0),
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.lArm.name = 'lArm';
        this.lArm.position.set(0, .5, 0);
        this.body.add(this.lArm);

        this.rLeg = new LineMesh({
            start: new Vector3(0, 0, 0),
            end: new Vector3(-.5, -.5, 0),
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.rLeg.name = 'rLeg';
        this.body.add(this.rLeg);

        this.lLeg = new LineMesh({
            start: new Vector3(0, 0, 0),
            end: new Vector3(.5, -.5, 0),
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.lLeg.name = 'lLeg';
        this.body.add(this.lLeg);
    }

}