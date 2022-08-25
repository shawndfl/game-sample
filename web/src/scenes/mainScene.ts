import OrbitControls from "../controllers/OrbitControls";
import GLTFLoader from '../core/GLTFLoader';
import floorTexture from '../assets/img/ground_grass_gen_10.png';
import Sky from "../graphics/Sky"
import {
    ACESFilmicToneMapping,
    AmbientLight,
    DirectionalLight,
    MathUtils,
    Mesh,
    MeshBasicMaterial,
    MeshPhongMaterial,
    MirroredRepeatWrapping,
    Object3D,
    PCFSoftShadowMap,
    PerspectiveCamera,
    PlaneGeometry,
    RepeatWrapping,
    Scene,
    ShaderMaterial,
    SpotLight,
    sRGBEncoding,
    TextureLoader,
    Vector3,
    WebGLRenderer
} from "three";

export enum DayState {
    Day,
    Night,
    Loop
}

/**
 * This is the main scene that will be used for rendering 
 * models and lights.
 * This will get called from @ref ThreeJsInterface.
 */
export default class MainScene extends Scene {

    width : number;
    height : number;

    /**
     * The ThreeJS renderer
     */
    renderer : WebGLRenderer;

    /**
     * Sky box
     */
    sky : Sky;
    // arrowHelper : THREE.ArrowHelper;
    // arrowHelperUp : THREE.ArrowHelper;

    /**
     * Direction light
     */
    dirLight : DirectionalLight;
    sunControllerNode : Object3D;
    sunNode : Object3D;
    lightBulb : Mesh;

    /** These are controls used to orbit the camera */
    controls : OrbitControls | undefined;
    /**
     * Threejs camera
     */
    camera : PerspectiveCamera;

    /**
     * Ground mesh
     */
    groundMesh : Mesh;
    groundGeo : PlaneGeometry;
    groundMat : MeshPhongMaterial;

    /**
     * Used to show different lighting
     */
    dayState : DayState;


    /**
     *  hemisphere
     */
    overhead : THREE.SpotLight;


    /**
     * Constructor
     * @param width 
     * @param height 
     */
    constructor(width : number, height : number) {
        super();
        this.width = width;
        this.height = height;

        // Create the render
        this.renderer = new WebGLRenderer({antialias: true});

        // set up the renderer
        this.renderSetup(this.renderer, this.width, this.height);

        // main scene and camera
        this.camera = new PerspectiveCamera(75, width / height, 0.1, 1000);

        // let there be light
        this.sunNode = new Object3D(); // this will be set when the model loads
        this.sky = new Sky();
        this.sky.scale.setScalar(450000);
        this.add(this.sky);
        const skyMat = this.sky.material;
        if (skyMat instanceof ShaderMaterial) {
            const uniforms = skyMat.uniforms;

            uniforms['turbidity'].value = 10;
            uniforms['rayleigh'].value = 3;
            uniforms['mieCoefficient'].value = .005;
            uniforms['mieDirectionalG'].value = .7;
            const phi = MathUtils.degToRad(0);
            const theta = MathUtils.degToRad(20.0);

            // calculate the sun's position
            const sun = new Vector3();
            sun.setFromSphericalCoords(1, phi, theta);
            uniforms['sunPosition'].value.copy(sun);
        }

        this.dayState = DayState.Loop;

        // manually create the ground
        this.groundGeo = new PlaneGeometry(30, 30);
        this.groundGeo.rotateX(MathUtils.degToRad(-90));
        this.groundMat = new MeshPhongMaterial({color: 0x646464});
        this.groundMesh = new Mesh(this.groundGeo, this.groundMat);
        this.groundMesh.position.set(0, 0, 0);
        this.groundMesh.receiveShadow = true;
        this.add(this.groundMesh);

        // default light bulb until the model is loaded
        this.lightBulb = new Mesh();
        this.lightBulb.material = new MeshBasicMaterial({color: "#323232"});

        // helpers
        // const dir = new THREE.Vector3(1, 0, 0);
        // const origin = new THREE.Vector3(0, 0, 0);
        // const color1 = 0xffff00;
        // this.arrowHelper = new THREE.ArrowHelper(dir, origin, 20, color1);
        // this.scene.add(this.arrowHelper);

        // const north = new THREE.Vector3(0, -1, 0);
        // const color2 = 0xff0000;
        // this.arrowHelperUp = new THREE.ArrowHelper(dir, origin, 20, color2);
        // this.scene.add(this.arrowHelperUp);


        // instantiate a loader
        const texture = new TextureLoader();

        // load a resource
        texture.load(
            // resource URL
                floorTexture,

            // onLoad callback
                (texture) => { // in this example we create the material when the texture is loaded
                texture.wrapS = MirroredRepeatWrapping;
                texture.wrapT = RepeatWrapping;
                texture.repeat.set(2, 8);
                this.groundMat.map = texture;
            }
        );

        const light = new AmbientLight(0xc4c4c4); // soft white light
        this.add(light);

        const targetObject = new Object3D();
        targetObject.position.set(0, -10, 0);
        this.add(targetObject);

        this.overhead = new SpotLight("#FFE484", 1.0);
        this.overhead.castShadow = true;
        this.overhead.distance = 0;
        this.overhead.angle = MathUtils.degToRad(30);

        this.overhead.penumbra = .5;
        this.overhead.target = targetObject;

        // this light will be added to the scene when the model is loaded
        // it will use the sun as a parent node
        this.dirLight = new DirectionalLight(0xffffff);
        this.dirLight.position.set(0, 0, 0);
        this.dirLight.castShadow = true;

        // this will be set when the model is loaded
        this.sunControllerNode = new Object3D();

        this.camera.position.z = 4;
        this.camera.position.y = 4;

        this.loadModel();
    }

    /**
     * 
     * @param parent The parent html element that holds the scene
     */
    initializeControls(parent : HTMLDivElement) {

        this.controls = new OrbitControls(this.camera, parent);

        this.controls.dampingFactor = .05;
        this.controls.enableDamping = true;
        this.controls.minDistance = 1;
        this.controls.maxDistance = 10;
        this.controls.maxPolarAngle = MathUtils.degToRad(88);
        this.controls.target.set(0, 0.35, 0);
        this.controls.update();

        // perform a resize with the new parent
        this.resize(parent.clientWidth, parent.clientHeight);
    }

    renderSetup(renderer : THREE.WebGLRenderer, width : number, height : number) { // set color for clearing the buffer
        renderer.setClearColor('#8d8d8d');

        // set the render size
        renderer.setSize(width, height);

        // we want shadows
        renderer.shadowMap.enabled = true;
        renderer.shadowMap.type = PCFSoftShadowMap;

        // setup tone mapping for awesome lighting!
        renderer.outputEncoding = sRGBEncoding;
        renderer.toneMapping = ACESFilmicToneMapping;

        // initial exposure. This will be changed in the main scene as the sun sets
        renderer.toneMappingExposure = 0.1100;
    }

    /**
     * Load the model for this scene
     */
    loadModel() { // instantiate a loader
        const loader = new GLTFLoader();

        // load a resource
        loader.load(
            // resource URL
                process.env.PUBLIC_URL + '/models/chair.gltf',

            // called when resource is loaded
                (gltf : any) => { // turn on shadows
                gltf.scene.traverse((child : any) => {
                    if ((child as THREE.Mesh).isMesh) {
                        child.castShadow = true
                    }
                });

                // cast shadows onto the table
                const tableTop: THREE.Mesh = gltf.scene.getObjectByName('Table');
                tableTop.receiveShadow = true;

                // setup the overhead light
                const overheadNode: THREE.Object3D = gltf.scene.getObjectByName('Overhead');
                this.overhead.position.x = overheadNode.position.x;
                this.overhead.position.y = overheadNode.position.y;
                this.overhead.position.z = overheadNode.position.z;
                overheadNode.add(this.overhead);

                // set up the sun
                this.sunNode = gltf.scene.getObjectByName('Sun');
                this.sunNode.add(this.dirLight);

                // overhead light
                this.lightBulb = gltf.scene.getObjectByName('LightBulb');
                this.lightBulb.material = new MeshBasicMaterial({color: "#ffffff"});

                // the sun controller used to simulate sun rise and sun set
                this.sunControllerNode = gltf.scene.getObjectByName('SunController');

                this.add(gltf.scene);

            },
            // called when loading is in progresses
                (xhr : XMLHttpRequest) => { // console.log((xhr.loaded / xhr.total * 100) + '% loaded');

            },
            // called when loading has errors
                (error : string) => {

                console.log(`An error happened ${error}`);

            }
        );
    }

    /**
     * This function will set the sun's az and elevation. 
     * based on the transformation of the sun controller in world space.
     * The sky shader will also be updated         
     */
    setSunAngle(render : THREE.WebGLRenderer) {

        const sunPosition = new Vector3();
        this.dirLight.getWorldPosition(sunPosition);
        const controllerPos = new Vector3();
        const sunPos = new Vector3();

        this.sunControllerNode.getWorldPosition(controllerPos);
        this.sunNode.getWorldPosition(sunPos);
        let sunDirection = controllerPos.sub(sunPos);
        sunDirection.normalize();
        sunDirection.negate();

        const sunTransform = sunDirection;

        // is the sun up
        const up = new Vector3(0, 1, 0);
        const isSunUp = up.dot(sunTransform) >= 0;

        // Toggle lights based on the sun position
        if (isSunUp) {
            this.overhead.visible = false;
            this.dirLight.visible = true;
            this.lightBulb.material = new MeshBasicMaterial({color: "#323232"})
        } else {
            this.overhead.visible = true;
            this.dirLight.visible = false;
            this.lightBulb.material = new MeshBasicMaterial({color: "#ffffff"})
        }

        // helpers
        // this.arrowHelper.setDirection(sunDirection);
        // this.arrowHelperUp.setDirection(up);

        // simulate exposure change
        const nightExposure = .5;
        const dayExposure = .35;
        const exposureStep = .005;
        if (isSunUp && render.toneMappingExposure > dayExposure) {
            render.toneMappingExposure -= exposureStep;
        } else if (! isSunUp && render.toneMappingExposure < nightExposure) {
            render.toneMappingExposure += exposureStep;
        }

        // clamp the exposure value
        render.toneMappingExposure = MathUtils.clamp(render.toneMappingExposure, dayExposure, nightExposure);

        const skyMat = this.sky.material;
        if (skyMat instanceof ShaderMaterial) {
            const uniforms = skyMat.uniforms;
            uniforms['sunPosition'].value.copy(sunTransform);
        }
    }

    /**
     * Does the rendering
     */
    render() {

        if (this.dayState === DayState.Loop) {
            this.sunControllerNode.rotateX(.001);
        } else if (this.dayState === DayState.Day) {
            const axis = new Vector3(0, 0, -1);
            this.sunControllerNode.setRotationFromAxisAngle(axis, 0);
        } else if (this.dayState === DayState.Night) {
            const axis = new Vector3(0, 0, -1);
            this.sunControllerNode.setRotationFromAxisAngle(axis, 180);
        }

        this.setSunAngle(this.renderer);

        // may not have been initialized yet
        if (this.controls !== undefined) {
            this.controls.update();
        }

        // do the WebGL render
        this.renderer.render(this, this.camera)
    }

    /**
     * When the container is resized this will be called.
     * @param width
     * @param height 
     */
    resize(width : number, height : number) {
        this.width = width;
        this.height = height;

        this.camera.aspect = width / height;
        this.camera.updateProjectionMatrix();

        this.renderer.setSize(width, height)
    }

    /**
     * Clean up webGL resources code  
     */
    dispose() {
        console.log("Dispose");
        this.remove(this.groundMesh);
        this.groundGeo.dispose();
        this.groundMat.dispose();
    }
}