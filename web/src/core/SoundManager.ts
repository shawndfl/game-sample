import {Audio, AudioListener, AudioLoader, Camera} from 'three';
import bgSound from '../assets/sound/TownTheme.mp3'

/**
 * Manages sounds
 */
export default class SoundManager {

    private _audio : Audio;
    private _listen : AudioListener;

    constructor() {
        this._listen = new AudioListener();
        this._audio = new Audio(this._listen);
    }

    assignToCamera(camera: Camera) {
        camera.add(this._listen);
    }

    play() {
        this._audio = new Audio(this._listen);

        const audioLoader = new AudioLoader();
        audioLoader.load(bgSound, (buffer) => {
            this._audio.setBuffer(buffer);
            this._audio.setLoop(true);
            this._audio.setVolume(0.5);
            this._audio.play();
        });
    }
}
