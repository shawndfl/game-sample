import {
    BufferGeometry,
    CatmullRomCurve3,
    Color,
    Float32BufferAttribute,
    Line,
    LineBasicMaterial,
    MathUtils,
    Mesh,
    Object3D,
    Scene,
    Vector3
} from "three";
import {hilbert3D} from "three/examples/jsm/utils/GeometryUtils";

interface CircleParams {
    center: Vector3;
    size: number;
    startColor: Vector3;
    endColor: Vector3;

}

class Circle2D extends Object3D {
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

        // create the head
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

interface LineParams {
    start: Vector3;
    end: Vector3;
    startColor: Vector3;
    endColor: Vector3;
}


class Line2D extends Object3D {
    private _geo : BufferGeometry;
    private _mat : LineBasicMaterial;
    mesh : Line;

    set testPosition(value: Vector3) {
        this.position.copy(value);
    }

    constructor(params : LineParams) {
        super();

        this._geo = new BufferGeometry();
        this._mat = new LineBasicMaterial();

        let points: number[] = [];
        let colors: number[] = [];

        // create the head
        points.push(params.start.x, params.start.y, params.start.z);
        colors.push(params.startColor.x, params.startColor.y, params.startColor.z);

        points.push(params.end.x, params.end.y, params.end.z);
        colors.push(params.endColor.x, params.endColor.y, params.endColor.z);
        
        this._geo.setAttribute('position', new Float32BufferAttribute(points, 3));
        this._geo.setAttribute('color', new Float32BufferAttribute(colors, 3));

        var material = new LineBasicMaterial({color: 0xffffff, vertexColors: true});
        this.mesh = new Line(this._geo, material);
        this.mesh.castShadow = true;
        this.add(this.mesh);
    }
}

export class LineCharacterMesh extends Object3D {

    head : Circle2D;
    body : Line2D;
    rArm : Line2D;
    lArm : Line2D;
    rLeg : Line2D;
    lLeg : Line2D;    

    constructor(scene : Scene) {
        super();        

        this.body = new Line2D({
            start: new Vector3(0, .5, 0),
            end: new Vector3(0, 0, 0),
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.body.position.set(0, .5, 0);
        this.add(this.body);

        this.head = new Circle2D({
            center: new Vector3(0, .1, 0),
            size: .1,
            startColor: new Vector3(1, 1, 1),
            endColor: new Vector3(1, 1, 1)
        });
        this.head.position.set(0,.5, 0)
        this.body.add(this.head);
        

        this.rArm = new Line2D({
            start: new Vector3(0, 0, 0),
            end: new Vector3(-.5, -.5, 0),
            startColor: new Vector3(1, 0, 0),
            endColor: new Vector3(1, 0, 0)
        });
        this.rArm.position.set(0, .5, 0);
        this.body.add(this.rArm);

        this.lArm = new Line2D({
            start: new Vector3(0, 0, 0),
            end: new Vector3(.5, -.5, 0),
            startColor: new Vector3(0, 0, 1),
            endColor: new Vector3(0, 0, 1)
        });
        this.lArm.position.set(0, .5, 0);
        this.body.add(this.lArm);

        this.rLeg = new Line2D({
            start: new Vector3(0, 0, 0),
            end: new Vector3(-.5, -.5, 0),
            startColor: new Vector3(1, 1, 0),
            endColor: new Vector3(1, 1, 0)
        });
        //this.rLeg.position.set(0, .5, 0);
        this.body.add(this.rLeg);

        this.lLeg = new Line2D({
            start: new Vector3(0, 0, 0),
            end: new Vector3(.5, -.5, 0),
            startColor: new Vector3(0, 1, 1),
            endColor: new Vector3(0, 1, 1)
        });
        //this.lLeg.position.set(0, .5, 0);
        this.body.add(this.lLeg);
    }   

}
