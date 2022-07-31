import {
    EventDispatcher,
    Quaternion,
    Vector3,
    PerspectiveCamera,
    MathUtils,
    Spherical
} from 'three';

const lookDirection = new Vector3();
const spherical = new Spherical();

export default class CameraController {

    private domElement : HTMLElement;

    private _enabled : boolean;

    private _movementSpeed : number;
    private _lookSpeed : number;

    private _lookVertical : boolean;
    private _autoForward : boolean;

    private _activeLook : boolean;

    private _heightSpeed : boolean;
    private _heightCoef : number;
    private _heightMin : number;
    private _heightMax : number;

    private _constrainVertical : boolean;
    private _verticalMin : number;
    private _verticalMax : number;

    private _mouseDragOn : boolean;

    private _autoSpeedFactor : number;

    private _mouseX : number;
    private _mouseY : number;

    private _moveForward : boolean;
    private _moveBackward : boolean;
    private _moveLeft : boolean;
    private _moveRight : boolean;
    private _moveUp : boolean;
    private _moveDown : boolean;

    private _viewHalfX = 0;
    private _viewHalfY = 0;

    private _lat : number;
    private _lon : number;


    constructor(domElement : HTMLElement, private camera : PerspectiveCamera) { // API
        this._enabled = true;

        this.domElement = domElement;
        this._movementSpeed = 1.0;
        this._lookSpeed = 0.05;
        this._lookVertical = true;
        this._autoForward = false;
        this._activeLook = false;
        this._heightSpeed = false;
        this._heightCoef = 1.0;
        this._heightMin = 0.0;
        this._heightMax = 1.0;
        this._constrainVertical = false;
        this._verticalMin = 0;
        this._verticalMax = Math.PI;
        this._mouseDragOn = false;

        this._constrainVertical = false;
        this._verticalMin = 0;
        this._verticalMax = Math.PI;
        this._mouseDragOn = false;
        this._autoSpeedFactor = 0.0;
        this._mouseX = 0;
        this._mouseY = 0;

        this._moveForward = false;
        this._moveBackward = false;
        this._moveLeft = false;
        this._moveRight = false;
        this._moveUp = false;
        this._moveDown = false;

        this._viewHalfX = 0;
        this._viewHalfY = 0;

        this._lat = 0;
        this._lon = 0;

        window.addEventListener("keydown", (e : KeyboardEvent) => {

            switch (e.code) {

                case 'ArrowUp':
                case 'KeyW':
                    this._moveForward = true;
                    break;

                case 'ArrowLeft':
                case 'KeyA':
                    this._moveLeft = true;
                    break;

                case 'ArrowDown':
                case 'KeyS':
                    this._moveBackward = true;
                    break;

                case 'ArrowRight':
                case 'KeyD':
                    this._moveRight = true;
                    break;

                case 'KeyR':
                    this._moveUp = true;
                    break;
                case 'KeyF':
                    this._moveDown = true;
                    break;

            }

        });

        window.addEventListener("keyup", (e : KeyboardEvent) => {

            switch (e.code) {

                case 'ArrowUp':
                case 'KeyW':
                    this._moveForward = false;
                    break;

                case 'ArrowLeft':
                case 'KeyA':
                    this._moveLeft = false;
                    break;

                case 'ArrowDown':
                case 'KeyS':
                    this._moveBackward = false;
                    break;

                case 'ArrowRight':
                case 'KeyD':
                    this._moveRight = false;
                    break;

                case 'KeyR':
                    this._moveUp = false;
                    break;
                case 'KeyF':
                    this._moveDown = false;
                    break;
            }

        });

        this.domElement.addEventListener("mousedown", (e : MouseEvent) => {
            switch (e.button) {
                case 0:
                    this._activeLook = true;
                    break;
                default:
            }
            this._mouseDragOn = true;

        });

        this.domElement.addEventListener("mousemove", (e : MouseEvent) => {

            if (this._activeLook) {
                this._mouseX = e.pageX - this.domElement.offsetLeft - this._viewHalfX;
                this._mouseY = e.pageY - this.domElement.offsetTop - this._viewHalfY;
            }

        });

        this.domElement.addEventListener("mouseup", (e : MouseEvent) => {

            switch (e.button) {
                case 0:
                    this._activeLook = false;
                    break;
                default:
            }
            this._mouseDragOn = false;

        });

        this.domElement.addEventListener('contextmenu', this.contextmenu);


        this.onResize();

        this.setOrientation();
    }

    setOrientation() {

        const quaternion = this.camera.quaternion;

        lookDirection.set(0, 0, - 1).applyQuaternion(quaternion);
        spherical.setFromVector3(lookDirection);

        this._lat = 90 - MathUtils.radToDeg(spherical.phi);
        this._lon = MathUtils.radToDeg(spherical.theta);

    }

    onResize() {

        this._viewHalfX = this.domElement.offsetWidth / 2;
        this._viewHalfY = this.domElement.offsetHeight / 2;

    }

    update(delta : number) {

        if (this._enabled === false) {
            return;
        }

        if (this._heightSpeed) {

            const y = MathUtils.clamp(this.camera.position.y, this._heightMin, this._heightMax);
            const heightDelta = y - this._heightMin;

            this._autoSpeedFactor = delta * (heightDelta * this._heightCoef);

        } else {
            this._autoSpeedFactor = 0.0;
        }

        const actualMoveSpeed = delta * this._movementSpeed;

        if (this._moveForward || (this._autoForward && !this._moveBackward)) 
            this.camera.translateZ(-(actualMoveSpeed + this._autoSpeedFactor));
        
        if (this._moveBackward) 
            this.camera.translateZ(actualMoveSpeed);
        
        if (this._moveLeft) 
            this.camera.translateX(- actualMoveSpeed);
        
        if (this._moveRight) 
            this.camera.translateX(actualMoveSpeed);
        
        if (this._moveUp) 
            this.camera.translateY(actualMoveSpeed);
    
        if (this._moveDown) 
            this.camera.translateY(- actualMoveSpeed);
        
        let actualLookSpeed = delta * this._lookSpeed;

        if (!this._activeLook) {
            actualLookSpeed = 0;
        }

        let verticalLookRatio = 1;
        if (this._constrainVertical) {
            verticalLookRatio = Math.PI / (this._verticalMax - this._verticalMin);
        }

        this._lon -= this._mouseX * actualLookSpeed;
        if (this._lookVertical) 
            this._lat -= this._mouseY * actualLookSpeed * verticalLookRatio;
        

        this._lat = Math.max(- 85, Math.min(85, this._lat));

        let phi = MathUtils.degToRad(90 - this._lat);
        const theta = MathUtils.degToRad(this._lon);

        if (this._constrainVertical) {
            phi = MathUtils.mapLinear(phi, 0, Math.PI, this._verticalMin, this._verticalMax);
        }

        const position = this.camera.position;

        const targetPosition = new Vector3();
        targetPosition.setFromSphericalCoords(1, phi, theta).add(position);

        this.camera.lookAt(targetPosition);

    }

    contextmenu(event : MouseEvent) {
        event.preventDefault();
    }

    dispose() { 

    };

}
