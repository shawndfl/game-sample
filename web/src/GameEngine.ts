import CameraController from './CameraController';
import Terrain from './Terrain';

import {
    Scene, Renderer, PerspectiveCamera, WebGLRenderer, Mesh, MeshBasicMaterial, BoxGeometry, Clock, Vector3
}
from "three";

export default class GameEngine {
    scene: Scene;
    private _camera: PerspectiveCamera;
    private _cameraController: CameraController;
    renderer: Renderer;
    private _clock: Clock;

    private _terrain : Terrain;

    constructor(private _container: HTMLElement) {
        this.scene = new Scene();
        this._clock = new Clock();

        this._camera = new PerspectiveCamera(45, 1.25, .01, 1000);
        this.renderer = new WebGLRenderer();        
        this._cameraController = new CameraController(this._container, this._camera);
        this._camera.position.add(new Vector3(0,1,0));

        this._terrain = new Terrain();
        this._initialize(this._container)
    }


    /**
     * Creates a scene
     * @param parent html node
     */
    private _initialize(container : HTMLElement) {



        this.renderer.setSize(window.innerWidth, window.innerHeight);
        container.appendChild(this.renderer.domElement);

        window.addEventListener("resize", (e:UIEvent)=> { this.onResize(e)})

        const geometry = new BoxGeometry(1, 1, 1);
        const material = new MeshBasicMaterial({color: 0x00ff00});
        const cube = new Mesh(geometry, material);
        this.scene.add(cube);

        this.scene.add(this._terrain.mesh);


        this._camera.position.z = 5;
        requestAnimationFrame(this.update);
    }

    onResize(e:UIEvent) {
        this._camera.aspect = window.innerWidth / window.innerHeight;
        this._camera.updateProjectionMatrix();
        this.renderer.setSize(this._container.clientWidth, this._container.clientHeight);
        this._cameraController.onResize();
    }

    update = (() => { 
        // get dt
        const dt = this._clock.getDelta();
        
        // update stuff
        this._cameraController.update(dt);
        requestAnimationFrame(this.update); 

        //render
        this.renderer.render(this.scene, this._camera); 
    });


}
