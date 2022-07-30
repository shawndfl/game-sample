import { GameContainer } from "./GameContainer";
import GameEngine from './GameEngine';

class _App {
    private _engine: GameEngine;

    get Engine(): GameEngine {
        return this._engine;
    }    

    constructor(root: HTMLElement) {
        this._initializeView(root);
        this._engine = new GameEngine(root);
    }

    private _initializeView(root: HTMLElement) {
        root.style.height = "100vh";
        root.style.width = "100%"
        root.style.background = "#646464";
        root.style.border = "1";    
    }
}

export const App = new _App(document.getElementById("gameContainer") as HTMLElement);