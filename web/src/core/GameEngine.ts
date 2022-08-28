import CameraController from '../controllers/CameraController';
import Terrain from './Terrain';
import './scss/GameEngine';
import {
    Scene,
    PerspectiveCamera,
    WebGLRenderer,
    Clock,
    Vector3,
    AmbientLight,
    SpotLight,
    PCFShadowMap
} from "three";

import CharacterController from '../controllers/CharacterController'
import CharacterComponent from '../components/CharacterComponent';
import SoundManager from './SoundManager';
import {LineCharacterMesh} from '../components/LineCharacterMesh';

/**
 * The game engin is used to manage the scenes, user input,
 * and controller lifecycle.
 */
export default class GameEngine {
    private _scene : Scene;
    private _camera : PerspectiveCamera;
    private _cameraController : CameraController;
    private _container : HTMLElement;

    private _characterCtl : CharacterController;
    private _characterComp : LineCharacterMesh;
    private _soundManager : SoundManager;

    private renderer : WebGLRenderer;
    private _clock : Clock;

    private _terrain : Terrain;

    /**
     * Gets the sound manager
     */
    get SoundManager() {
        return this._soundManager;
    }

    constructor(root : HTMLElement) {
        this._scene = new Scene();
        this._clock = new Clock();
        this._soundManager = new SoundManager();

        this._camera = new PerspectiveCamera(33, 1.25, .01, 1000);
        this._soundManager.assignToCamera(this._camera);
        // this._soundManager.play();

        this.renderer = new WebGLRenderer({antialias: true});
        this.renderer.setPixelRatio(window.devicePixelRatio);
        this.renderer.setClearColor(0x646464, 1);
        this.renderer.shadowMap.enabled = true;
        this.renderer.shadowMap.type = PCFShadowMap;

        // test light
        const light = new SpotLight(0xffffff, 1.5);
        light.position.set(0, 5, -5);
        light.angle = Math.PI * 0.2;
        light.castShadow = true;
        light.shadow.camera.near = 0.1;
        light.shadow.camera.far = 100;
        light.shadow.bias = -0.000222;
        light.shadow.mapSize.width = 1024;
        light.shadow.mapSize.height = 1024;
        this._scene.add(light);

        // soft white light    
        const lightAmbient = new AmbientLight(0x404040);
        this._scene.add(lightAmbient);

        // create a new container for the graphics
        this._container = document.createElement('div');
        this._container.classList.add('graphics-container');

        root.append(this._container);

        this._cameraController = new CameraController(this._container, this._camera);
        this._camera.position.add(new Vector3(0, 1, 5));

                    
        this.onResize();
        this._terrain = new Terrain();

        this._initialize(this._container);

        // make a character
        this._characterComp = new LineCharacterMesh(this._scene);
        this._characterCtl = new CharacterController(this._container, this._characterComp);
        // this._characterComp.load();

        this._scene.add(this._characterComp);
    }


    /**
     * Creates a scene
     * @param parent html node
     */
    private _initialize(container : HTMLElement) {

        this.renderer.setSize(container.clientWidth, container.clientHeight);
        container.appendChild(this.renderer.domElement);

        window.addEventListener("resize", () => {
            this.onResize()
        })

        this._scene.add(this._terrain.mesh);

        requestAnimationFrame(this.update);
    }

    onResize() {
        this._camera.aspect = window.innerWidth / window.innerHeight;
        this._camera.updateProjectionMatrix();
        this.renderer.setSize(this._container.clientWidth, this._container.clientHeight);
        this._cameraController.onResize();
    }

    update = (() => { // get dt
        const dt = this._clock.getDelta();

        // update stuff
        this._cameraController.update(dt);

        this._characterCtl.update(dt);
        requestAnimationFrame(this.update);

        // render
        this.renderer.render(this._scene, this._camera);
    });


}
