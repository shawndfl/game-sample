import CameraController from '../controllers/CameraController';
import Terrain from './Terrain';
import './scss/GameEngine';
import {
    Scene,
    Renderer,
    PerspectiveCamera,
    WebGLRenderer,   
    Clock,
    Vector3,   
    AmbientLight
} from "three";
import CharacterController from '../controllers/CharacterController'
import CharacterComponent from '../components/CharacterComponent';
import SoundManager from './SoundManager';

/**
 * The game engin is used to manage the scenes, user input,
 * and controller lifecycle.
 */
export default class GameEngine {
    private _scene : Scene;
    private _camera : PerspectiveCamera;
    private _cameraController : CameraController;
    private _container: HTMLElement;

    private _characterCtl : CharacterController;
    private _characterComp : CharacterComponent;
    private _soundManager: SoundManager;    

    private renderer : Renderer;
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

        this._camera = new PerspectiveCamera(45, 1.25, .01, 1000);        

        this._soundManager.assignToCamera(this._camera);
        //this._soundManager.play();

        this.renderer = new WebGLRenderer();

        // create a new container for the graphics
        this._container = document.createElement('div');
        this._container.classList.add('graphics-container');

        root.append(this._container);

        this._cameraController = new CameraController(this._container, this._camera);
        this._camera.position.add(new Vector3(0, 1, 0));

        const light = new AmbientLight( 0x404040 ); // soft white light
        this._scene.add( light );
        this.onResize();
        this._terrain = new Terrain();
        this._initialize(this._container)

        // make a character
        this._characterComp = new CharacterComponent({});
        this._characterCtl = new CharacterController(this._characterComp);
        this._characterComp.load();


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
