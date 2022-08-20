import {
    BoxGeometry,
    Mesh,
    MeshBasicMaterial,
    MeshPhysicalMaterial,
    Object3D,
    SphereGeometry,
    Vector3
} from "three";


interface material{
    texture: string,

}

interface IMeshBuilder{
    name: string,
    parent: string,
    scale: Vector3,
    offset: Vector3,
    material: MeshBasicMaterial
}

/**
 * This will build a character.
 */
export class CharacterBuilder extends Object3D {


    private _geoSphere : SphereGeometry;
    private _geoCube : BoxGeometry;
    private _meshes: Map<string, Mesh>;
    private _materials: Map<string, MeshBasicMaterial>;

    private _materialHead : MeshBasicMaterial;
    private _meshHead : Mesh;

    private _materialBody : MeshBasicMaterial;
    private _meshBody : Mesh;

    private _materialRArm : MeshBasicMaterial;
    private _meshRArm : Mesh;

    private _materialLArm : MeshBasicMaterial;
    private _meshLArm : Mesh;

    constructor(props : CharacterProps) {
        super();

        this._geoSphere = new SphereGeometry(1, 6, 6);
        this._geoCube = new BoxGeometry(1, 1, 1);

        this._meshes = new Map<string, Mesh>();
        this._materials = new Map<string, MeshBasicMaterial>();

        const headScale = new Vector3(.5, .5, .5);
        const armScale = new Vector3(.5, .2, .2);
        const bodyScale = new Vector3(.5, .5, .2);
        const legScale = new Vector3(.5, .2, .2);
     
        // pivot at the bottom of the head
        const headOffset = new Vector3(0, 1.0, 0);

        // pivot at the center of the shoulder
        const rArmOffset = new Vector3(.75, .75, 0);
        const lArmOffset = new Vector3(-.75, .75, 0);

        // pivot at the top of the legs
        const lLegOffset = new Vector3(-.25, -.5, 0);
        const rLegOffset = new Vector3(.25, -.5, 0);

        // pivot at the bottom
        const bodyOffset = new Vector3(0, .5, 0);

        this._materialBody = new MeshBasicMaterial({color: 0xff00e4});
        //this._materialBody.wireframe = true;
        this._meshBody = new Mesh(this._geoCube, this._materialBody);
        this._meshBody.scale.copy(bodyScale);
        this._meshBody.position.copy(bodyOffset);
        this.add(this._meshBody);

        // create a pivot point at the bottom of the head
        this._materialHead = new MeshBasicMaterial({color: 0x00ffff});
        this._materialHead.wireframe = true;
        this._meshHead = new Mesh(this._geoSphere, this._materialHead);
        this._meshHead.scale.copy(headScale);
        this._meshHead.position.copy(headOffset);
        this._meshBody.add(this._meshHead);
       
        this._materialRArm = new MeshBasicMaterial({color: 0x00ffff});
        ///this._materialRArm.wireframe = true;
        this._meshRArm = new Mesh(this._geoCube, this._materialRArm);
        this._meshRArm.scale.copy(armScale);
        this._meshRArm.position.copy(rArmOffset);
        this._meshBody.add(this._meshRArm);
        
        this._materialLArm = new MeshBasicMaterial({color: 0xff0000});
        //this._materialLArm.wireframe = true;
        this._meshLArm = new Mesh(this._geoCube, this._materialLArm);        
        this._meshLArm.scale.copy(armScale);
        this._meshLArm.position.copy(lArmOffset);
        this._meshBody.add(this._meshLArm);


        //this._materialLArm = new MeshBasicMaterial({color: 0x00dde4});
        //this._materialLArm.wireframe = true;
        //this._meshLArm = new Mesh(this._geoCube, this._materialLArm);
        // this._meshRArm.translateX(0.5);
        //this.add(this._meshLArm);
    }

    private _meshBuilder(data: IMeshBuilder) {


    }
}
