import {
    Mesh,
    PlaneGeometry,
    MathUtils,
    Texture,
    TextureLoader,
    Vector2,
    MirroredRepeatWrapping,
    RepeatWrapping,
    MeshStandardMaterial,
    ShadowMaterial,
    MeshPhongMaterial
} from 'three';

import ground from "../assets/img/ground_grass_gen_10.png";

export default class Terrain {

    private _mesh : Mesh;
    private _geometry : PlaneGeometry;
    private _material : MeshStandardMaterial;
    private _diffused : Texture;

    get mesh(): Mesh {
        return this._mesh;
    }

    constructor() {
        this._geometry = new PlaneGeometry(100, 100, 100);
        this._geometry.rotateX(MathUtils.DEG2RAD * -90);
        this._material = new MeshStandardMaterial({color: 0x00ffff});
        this._diffused = new TextureLoader().load(ground);
        this._diffused.wrapS = RepeatWrapping;
        this._diffused.wrapT = RepeatWrapping;

        this._material.map = this._diffused;
        this._material.map.repeat = new Vector2(50, 50);        

        this._mesh = new Mesh(this._geometry, this._material);
        this._mesh.receiveShadow = true;
        this._mesh.castShadow = false;
    }
}
