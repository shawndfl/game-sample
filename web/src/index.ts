import GameEngine from './core/GameEngine';
import Designer from './ui/Designer';
import './scss/index';

/**
 * The main application
 */
class _App {
    private _engine: GameEngine;
    private _designer: Designer;

    get Engine(): GameEngine {
        return this._engine;
    }    

    get Designer(): Designer {
        return this._designer;
    }

    constructor(root: HTMLElement) {               
        this._designer = new Designer(root);
        this._engine = new GameEngine(root);
    }
}

export const App = new _App(document.getElementById("game-container") as HTMLElement);