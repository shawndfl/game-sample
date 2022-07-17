import * as THREE from 'three';
import { randFloat } from 'three/src/math/MathUtils';

/**
 * This class will create the ground terrain
 */
export class GroundTerrain {

    private _geometry : THREE.BufferGeometry;
    private _material : THREE.MeshPhongMaterial;
    private _diffused : THREE.Texture | undefined;
    private _mesh : THREE.Mesh;

    /**
     * Get the mesh so it can be added to a scene
     */
    get mesh() {
        return this._mesh;
    }

    constructor(width : number, length : number, texturePath : string, scene : THREE.Scene) { // manually create the ground

        this._geometry = this._buildGeometry(width, length);
        this._material = new THREE.MeshPhongMaterial({color: 0x646464});
        this._mesh = new THREE.Mesh(this._geometry, this._material);

        this._mesh.position.set(0, 0, 0);
        this._mesh.receiveShadow = true;

        // instantiate a loader
        const loader = new THREE.TextureLoader();

        this.loadTexture(loader, texturePath).then((value : THREE.Texture) => {
            this._diffused = value;
            this._diffused.wrapS = THREE.MirroredRepeatWrapping;
            this._diffused.wrapT = THREE.RepeatWrapping;
            this._diffused.repeat.set(8, 8);
            this._material.map = this._diffused;
        }).then(() => {
            scene.add(this._mesh);
        });
    }

    async loadTexture(loader : THREE.TextureLoader, texturePath : string) {
        const myPromise: Promise<THREE.Texture> = new Promise((resolve) => { // load a resource
            loader.load(
                // resource URL
                    texturePath,

                // onLoad callback
                    (texture) => { // in this example we create the material when the texture is loaded
                    resolve(texture);
                }
            );
        });
        return await myPromise;
    }

    private _buildGeometry(width : number, length : number): THREE.BufferGeometry {
        // const geo = new THREE.PlaneGeometry(width, length);
        // geo.rotateX(THREE.MathUtils.degToRad(-90));

        const geo = new THREE.BufferGeometry();

        const width_half = width / 2;
        const length_half = length / 2;
        const segment = 10;

        const gridX = Math.floor(segment);
        const gridY = Math.floor(segment);

        const gridX1 = gridX + 1;
        const gridY1 = gridY + 1;

        const segment_width = width / gridX;
        const segment_length = length / gridY;

        //

        const indices = [];
        const vertices = [];
        const normals = [];
        const uvs = [];

        
        for(let iz = 0; iz < gridY1; iz++) {
            const z = iz * segment_length - length_half;
            for (let ix = 0; ix < gridX1; ix++) {
                const x = ix * segment_width - width_half;
                const y = randFloat(0,10);
                
                vertices.push(x, y, z);
                normals.push(0, 1, 0);
                uvs.push(ix / gridX);
                uvs.push(1 - (iz / gridY));
            }
        }

        for(let iy = 0; iy < gridY; iy++) {
            for (let ix = 0; ix < gridX; ix++) {

                const a = ix + gridX1 * iy;
                const b = ix + gridX1 * (iy + 1);
                const c = (ix + 1) + gridX1 * (iy + 1);
                const d = (ix + 1) + gridX1 * iy;

                indices.push(a, b, d);
                indices.push(b, c, d);
            }
        }

        geo.setIndex(indices);
        geo.setAttribute('position', new THREE.Float32BufferAttribute(vertices, 3));
        geo.setAttribute('normal', new THREE.Float32BufferAttribute(normals, 3));
        geo.setAttribute('uv', new THREE.Float32BufferAttribute(uvs, 2));

        return geo;
    }

    /**
     * Clean up
     */
    dispose() {
        if (this._geometry != undefined) {
            this._geometry.dispose();
        }
        if (this._material != undefined) {
            this._material.dispose();
        }
        if (this._diffused != undefined) {
            this._diffused.dispose();
        }
    }
}
