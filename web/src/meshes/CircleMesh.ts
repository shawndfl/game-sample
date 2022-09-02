import {
    BufferGeometry,    
    Float32BufferAttribute,
    Line,
    LineBasicMaterial,    
    Object3D,    
    Vector3
} from "three";

export interface CircleParams {
    center: Vector3;
    size: number;
    startColor: Vector3;
    endColor: Vector3;

}

export class CircleMesh extends Object3D {
    private _geo : BufferGeometry;
    private _mat : LineBasicMaterial;
    mesh : Line;

    constructor(params : CircleParams) {
        super();

        this._geo = new BufferGeometry();
        this._mat = new LineBasicMaterial();

        let points = [];
        let colors = [];
        const center = params.center;
        const step = Math.PI / 40.0;
        const size = params.size;
        const endAngle = Math.PI * 2.0
        let colorFade = 0;

        // create the circle
        for (let angle = 0; angle <= endAngle; angle += step) {
            const x = Math.cos(angle) * size;
            const y = Math.sin(angle) * size;


            points.push(center.x + x, center.y + y, center.z);
            const color1 = params.startColor.clone().multiplyScalar(1.0 - colorFade);
            const color2 = params.endColor.clone().multiplyScalar(colorFade);
            const color = color1.add(color2);

            colors.push(color.x, color.y, color.z);
            colorFade += step / endAngle;

        }

        points.push(center.x + size, center.y, center.z);
        colors.push(1, 0, 0);

        this._geo.setAttribute('position', new Float32BufferAttribute(points, 3));
        this._geo.setAttribute('color', new Float32BufferAttribute(colors, 3));

        var material = new LineBasicMaterial({color: 0xff0000, vertexColors: true});
        this.mesh = new Line(this._geo, material);
        this.mesh.castShadow = true;
        this.add(this.mesh);
    }
}

