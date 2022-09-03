import {BufferGeometry, Float32BufferAttribute, Line, Mesh, Object3D, ShaderMaterial, Vector2} from "three";
import lineVert from '../shaders/line.vert'
import lineFrag from '../shaders/line.frag'

/**
 * Renders a line
 */
class LineMaterial extends ShaderMaterial {

    constructor() {
        console.debug("vert: ", lineVert, " Frag: ", lineFrag);
        super({
            uniforms: {
                time: {
                    value: 1.0
                }
            },

            vertexShader: lineVert,
            fragmentShader: lineFrag

        });
    }
}

export class CurveLineMesh extends Object3D {
    line : Line;
    _geo : BufferGeometry;
    _mat : LineMaterial;

    constructor() {
        super();
        this._geo = new BufferGeometry();
        this._mat = new LineMaterial();

        const points = [];
        points.push(-1, 0, 0);
        points.push(1, 0, 0);        
        this._geo.setAttribute('position', new Float32BufferAttribute(points, 3) );

        this.line = new Line(this._geo, this._mat);
        this.add(this.line);
    }    
}
