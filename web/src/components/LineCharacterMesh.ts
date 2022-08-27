import {
    BufferGeometry,
    CatmullRomCurve3,
    Color,
    Float32BufferAttribute,
    Line,
    LineBasicMaterial,
    Mesh,
    Object3D,
    Scene,
    Vector3
} from "three";
import {hilbert3D} from "three/examples/jsm/utils/GeometryUtils";


export class LineCharacterMesh extends Object3D {

    private _geo : BufferGeometry;
    private _mat : LineBasicMaterial;
    // private _mesh: Mesh;

    constructor(scene : Scene) {
        super();
        this._geo = new BufferGeometry();
        this._mat = new LineBasicMaterial();

        const hilbertPoints = hilbert3D(new Vector3(0, 0, 0), 200.0, 1, 0, 1, 2, 3, 4, 5, 6, 7);
        console.debug("creating line ", hilbertPoints);
        const geometry1 = new BufferGeometry();

        const subdivisions = 6;

        let points = [];
        let colors = []
        points.push(0, 0, 0);
        points.push(0, 100, 0);

        colors.push(1,0,0);
        colors.push(0,0,0);

        const point = new Vector3();

        geometry1.setAttribute('position', new Float32BufferAttribute(points, 3));
        geometry1.setAttribute('color', new Float32BufferAttribute(colors, 3));


        // Create lines and add to scene

        var material = new LineBasicMaterial({color: 0xff0000, vertexColors: true});

        const line = new Line(geometry1, material);
        console.debug("adding line ", line.position);
        scene.add(line);

    }
}
