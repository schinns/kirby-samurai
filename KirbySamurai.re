open Revery;
open Revery_Core;
open Revery.UI;
open Revery.UI.Components;
open Styles;

type gameStateT = 
  | Stop
  | PreDuel 
  | Duel;

type state = {
  threshold: float,
  keyEvents: list(string),
  gameState: gameStateT,
  seconds: float,
};

type action =
  | SetKeyEvents(list(string))
  | SetGameState(gameStateT)
  | Count(float)
  | ResetState(state);

let reducer = (action, state) =>
  switch(action) {
  | SetKeyEvents(events) => { ...state, keyEvents: events }
  | SetGameState(newState) => { ...state, gameState: newState }
  | Count(_deltaSeconds) => {...state, seconds: state.seconds +. 1. }
  | ResetState(initState) => initState 
  };

let initialState ={
  //random timer value between 2-5
  threshold: Random.float(4.) +. 2.,
  keyEvents: [],
  gameState: Stop,
  seconds: 0.,
};

let component = React.component("KirbySamurai");

let createElement = (~children as _, ()) => 
  component(hooks => {
    let (state, dispatch, hooks) =
      React.Hooks.reducer(
        initialState,
        reducer,
        hooks
      );

    (hooks,
      switch(state.gameState) {
      | Stop => (
        <KeyboardInput
            onKeyDown=((event: NodeEvents.keyEventParams) => {
              //key event
              let key = event.key |> Key.toString;
              //press spacebar to start game
              if(key == " ") {
                dispatch(SetGameState(PreDuel)) 
              }
        })>
        <game>
          //<Image src="kirby1.png" width=50 height=50 />
          <Image src="start.png" width=600 height=450 />
        </game>
        </KeyboardInput>
      )
      | PreDuel => {
        let tickFn = t => dispatch(Count(t |> Time.toSeconds));
        let interval = 
        Revery_Core.Tick.interval(tickFn, Time.Seconds(1.)); 
        //when the elapsed seconds is greater than the 3-5 second threshold
        if(state.seconds > state.threshold) {
          //clear interval fn
          interval();
          //set game state Running
          dispatch(SetGameState(Duel));
        };
        <game>
          <Image
            src="frame1.png"
            width=600
            height=450
          />
        </game>
      }
      | Duel => (
        <KeyboardInput
          onKeyDown=((event: NodeEvents.keyEventParams) => {
            //key event
            let key = event.key |> Key.toString;
            if(key == "a" || key == "'") {
              // new key event state
              let newKeyEvents = List.append(state.keyEvents, [key]);
              //dispatch only up to 2 events
              if(state.keyEvents |> List.length < 2) {
                dispatch(SetKeyEvents(newKeyEvents))
              }
            }
            if(key == " ") {
                dispatch(ResetState(initialState));
            }
          })>
        <game>
          (
            if(state.keyEvents |> List.length > 0) {
               switch(List.nth(state.keyEvents, 0)) {
               | "a" => <Image src="frame3a.png" width=600 height=450 />
               | "'" => <Image src="frame3b.png" width=600 height=450 />
               | _   => <Image src="frame2.png" width=600 height=450 />
              }
            } else {
              <Image src="frame2.png" width=600 height=450 />
            }
          )
        </game>
        </KeyboardInput>
      )
     }
    )
  });



