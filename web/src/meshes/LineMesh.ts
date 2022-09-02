import {
    BufferGeometry,    
    Float32BufferAttribute,
    Line,
    LineBasicMaterial,    
    Object3D,    
    Vector3
} from "three";

export interface LineParams {
    start: Vector3;
    end: Vector3;
    startColor: Vector3;
    endColor: Vector3;
}

/**
 * A simple line mesh 
 */
export class LineMesh extends Object3D {
    private _geo : BufferGeometry;
    private _mat : LineBasicMaterial;
    mesh : Line;

    constructor(params : LineParams) {
        super();

        this._geo = new BufferGeometry();
        this._mat = new LineBasicMaterial();

        let points: number[] = [];
        let colors: number[] = [];

        // create the points for the line
        points.push(params.start.x, params.start.y, params.start.z);
        colors.push(params.startColor.x, params.startColor.y, params.startColor.z);

        points.push(params.end.x, params.end.y, params.end.z);
        colors.push(params.endColor.x, params.endColor.y, params.endColor.z);

        //this._geo.setPositions(points);
        this._geo.setAttribute('position', new Float32BufferAttribute(points, 3));
        this._geo.setAttribute('color', new Float32BufferAttribute(colors, 3));

        var material = new LineBasicMaterial({color: 0xffffff, vertexColors: true});
        this.mesh = new Line(this._geo, material);
        this.mesh.castShadow = true;
        this.add(this.mesh);
    }
}

