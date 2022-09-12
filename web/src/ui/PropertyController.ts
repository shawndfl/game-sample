
import './scss/SceneProperties.scss'

/**
 * The property controller is used to modify different properties
 * related to the 3D simulation
 */
export class PropertyController {

    constructor(parent: HTMLElement) {
        this._createView(parent);
    }

    private _createView(parent: HTMLElement) {
        const container = document.createElement('div');
        container.classList.add('scene-properties');
        parent.append(container);

        const panel = document.createElement('div');
        panel.classList.add('property-panel');
        container.append(panel);
    }
}