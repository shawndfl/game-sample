import CameraController from './controllers/CameraController';
import Terrain from './Terrain';

import {
    Scene,
    Renderer,
    PerspectiveCamera,
    WebGLRenderer,   
    Clock,
    Vector3,
    AudioListener,
    Audio,
    AudioLoader
} from "three";
import CharacterController from './controllers/CharacterController';
import CharacterComponent from './components/CharacterComponent';

import bgSound from './assets/sound/TownTheme.mp3'

export default class GameEngine {
    private _scene : Scene;
    private _camera : PerspectiveCamera;
    private _cameraController : CameraController;

    private _characterCtl : CharacterController;
    private _characterComp : CharacterComponent;

    private renderer : Renderer;
    private _clock : Clock;

    private _terrain : Terrain;
    private _audio : Audio;

    constructor(private _container : HTMLElement) {
        this._scene = new Scene();
        this._clock = new Clock();
        const listen = new AudioListener ();

        this._camera = new PerspectiveCamera(45, 1.25, .01, 1000);
        this._camera.add(listen);
        this.renderer = new WebGLRenderer();
        this._cameraController = new CameraController(this._container, this._camera);
        this._camera.position.add(new Vector3(0, 1, 0));

        this.onResize();
        this._terrain = new Terrain();
        this._initialize(this._container)

        // make a character
        this._characterComp = new CharacterComponent({});
        this._characterCtl = new CharacterController(this._characterComp);

        this._scene.add(this._characterComp);
        this._audio = new Audio(listen);

        const audioLoader = new AudioLoader();
        audioLoader.load(bgSound, (buffer) => {
            this._audio.setBuffer(buffer);
            this._audio.setLoop(true);
            this._audio.setVolume(0.5);
            this._audio.play();
        });
    }


    /**
     * Creates a scene
     * @param parent html node
     */
    private _initialize(container : HTMLElement) {


        this.renderer.setSize(window.innerWidth, window.innerHeight);
        container.appendChild(this.renderer.domElement);

        window.addEventListener("resize", () => {
            this.onResize()
        })

        this._scene.add(this._terrain.mesh);


        this._camera.position.z = 5;
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
        requestAnimationFrame(this.update);

        // render
        this.renderer.render(this._scene, this._camera);
    });


}
