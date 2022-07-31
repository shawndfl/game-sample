import { BoxGeometry, Mesh, MeshBasicMaterial, Object3D } from "three";

/**
 * This will build a character.
 */
export class CharacterBuilder extends Object3D {
            

    private _geoHead: BoxGeometry;    
    private _materialHead: MeshBasicMaterial;
    private _meshHead: Mesh;   

    private _geoBody: BoxGeometry;
    private _materialBody: MeshBasicMaterial;
    private _meshBody: Mesh;   

    constructor(props: CharacterProps) {
        super();    
        this._geoHead = new BoxGeometry(.5, .5, .5);
        this._materialHead = new MeshBasicMaterial({color: 0x00ffff});
        this._meshHead = new Mesh(this._geoHead, this._materialHead);

        this._geoBody = new BoxGeometry(.2, 2, .2);        
        this._materialBody = new MeshBasicMaterial({color: 0xff00e4});
        this._meshBody = new Mesh(this._geoBody, this._materialBody);

        this.add(this._meshHead);
        this.add(this._meshBody);
    }
}