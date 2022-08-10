import {
    BoxGeometry, Mesh, MeshBasicMaterial, MeshPhysicalMaterial, Object3D, SphereGeometry
}
from "three";

/**
 * This will build a character.
 */
export class CharacterBuilder extends Object3D {


    private _geoHead: SphereGeometry;
    private _materialHead: MeshBasicMaterial;
    private _meshHead: Mesh;

    private _geoBody: BoxGeometry;
    private _materialBody: MeshBasicMaterial;
    private _meshBody: Mesh;

    private _geoRArm: BoxGeometry;
    private _materialRArm: MeshBasicMaterial;
    private _meshRArm: Mesh;

    private _geoLArm: BoxGeometry;
    private _materialLArm: MeshBasicMaterial;
    private _meshLArm: Mesh;

    constructor(props: CharacterProps) {
        super();

        const headSize = .2;
        this._geoHead = new SphereGeometry(headSize, 6, 6);
        // create a pivot point at the bottom of the head
        this._geoHead.translate(0, headSize, 0);         
        this._materialHead = new MeshBasicMaterial({color: 0x00ffff});
        this._materialHead.wireframe = true;
        this._meshHead = new Mesh(this._geoHead, this._materialHead);
        //this._meshHead.translateY(0.80);
        this.add(this._meshHead);

        this._geoBody = new BoxGeometry(.4, .4, .2);
        this._geoBody.translate(0,.2,0);
        this._materialBody = new MeshBasicMaterial({color: 0xff00e4});
        this._materialBody.wireframe = true;
        this._meshBody = new Mesh(this._geoBody, this._materialBody);
        //this._meshBody.translateY(0.5);
        this.add(this._meshBody);

        this._geoRArm = new BoxGeometry(.4, .4, .2);
        this._geoRArm.translate(.2, -.2, 0);
        this._materialRArm = new MeshBasicMaterial({color: 0xffdde4});
        this._materialRArm.wireframe = true;
        this._meshRArm = new Mesh(this._geoRArm, this._materialRArm);
        //this._meshRArm.translateX(0.5);
        this.add(this._meshRArm);

        this._geoLArm = new BoxGeometry(.4, .4, .2);
        this._geoLArm.translate(-.2, -.2, 0);
        this._materialLArm = new MeshBasicMaterial({color: 0x00dde4});
        this._materialLArm.wireframe = true;
        this._meshLArm = new Mesh(this._geoLArm, this._materialLArm);
        //this._meshRArm.translateX(0.5);
        this.add(this._meshLArm);

    }
}
