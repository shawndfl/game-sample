
/**
 * The designer is used to manage ui elements around the 3d simulation.
 */
export default class Designer {

    private _container: HTMLElement;

    constructor(root: HTMLElement) {
         // create a new container for the graphics
         this._container = document.createElement('div');
         this._container.classList.add('graphics-container');
         root.append(this._container);

        this._buildView(this._container);
    }

    private _buildView(container: HTMLElement) {
        console.debug("Building view for designer...");
    }
}