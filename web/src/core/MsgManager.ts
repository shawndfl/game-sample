export enum EventNames {
    SceneLoaded
}

/**
 * A wrapper around a callback function for an event.
 */
export class Event {
    callback : (data : any) => void;

    constructor(callback : (data : any) => void) {
        this.callback = callback;
    }

    call(data : any) {
        this.callback(data);
    }
}

/**
 * Manages all events. This is a singleton that can be access using MsgManager
 */
class _MsgManager {
    private _events : Map < EventNames,
    Event [] >;

    constructor() {
        this._events = new Map<EventNames, Event[]>();
    }

    subscribe(eventName : EventNames, callback : (data : any) => void): Event {

        if (!this._events.has(eventName)) {
            this._events.set(eventName, []);
        }

        const event = new Event(callback);
        this._events.get(eventName) ?. push(new Event(callback));
        return event;
    }

    raise(event : EventNames, data : any, autoRemove : boolean = false) {
        const eventMap = this._events.get(event);
        if (eventMap) {
            eventMap.forEach(callback => {
                callback.call(data);
            })
        }
    }

    unsubscribe(event : Event) {
        this._events.forEach((events) => {
            events = events.filter(e => e !== event);
        });
    }
}

export const MsgManager = new _MsgManager();
