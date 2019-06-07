open Revery;
open Revery_Core;
open Revery.UI;
open Revery_UI_Components;
open Styles;

type t = 
  | NA
  | Tie
  | Kirby
  | MetaKnight;

type gameStateT = 
  | Stop
  | PreRunning
  | Running;

type state = {
  winner: t,
  timer: int,
  keyEvents: list(string),
  gameState: gameStateT,
  seconds: float,
};

type action =
  | SetKeyEvents(list(string))
  | SetGameState(gameStateT)
  | Count(float)
  | ResetState(state)
  | DetermineWinner(t);

let reducer = (action, state) =>
  switch(action) {
  | SetKeyEvents(events) => { ...state, keyEvents: events }
  | DetermineWinner(player) => { ...state, winner: player }
  | SetGameState(newState) => { ...state, gameState: newState }
  | Count(_deltaSeconds) => {...state, seconds: state.seconds +. 1. }
  | ResetState(initState) => initState 
  };

let initialState ={
  winner: NA,
  timer: 3,
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
        <View 
        ref={r => Focus.focus(r)}
        style=gameStyle
        onKeyDown=((event: NodeEvents.keyEventParams) => {
          //key event
          let key = event.key |> Key.toString;
          //press spacebar to start game
          if(key == " ") {
            dispatch(SetGameState(PreRunning)) 
          }
        })
        >
          <Image 
            src=Assets.start.image
            width=Assets.start.width
            height=Assets.start.height
          />
          //<Text style=textStyle text="Kirby Samurai" />
          <Clickable onClick=(() => {
            print_endline(Random.float(4.) |> string_of_float);
           // dispatch(SetGameState(PreRunning))
          })>
            <Text style=textStyle text="Play!" />
          </Clickable>
        </View>
      )
      | PreRunning => {
        let interval = Revery_Core.Tick.interval(t => dispatch(Count(t |> Time.toSeconds)), Time.Seconds(1.)); 
        if(state.seconds > 3.) {
          interval();
          dispatch(SetGameState(Running));
        };
        <View style=gameStyle1>
          <Image 
            src=Assets.kirby1.image
            width=50
            height=50
            style=kirbyStyle
          />
          <Image
            src="frame1.png"
            width=Assets.bkg.width
            height=Assets.bkg.height
          />
        </View>
      }
      | Running => (
        <View 
          style=gameStyle2
          ref={r => Focus.focus(r)}
          onKeyDown=((event: NodeEvents.keyEventParams) => {
            //key event
            let key = event.key |> Key.toString;
            // new key event state
            let newKeyEvents = List.append(state.keyEvents, [key]);
            //dispatch only up to 2 events
            if(state.keyEvents |> List.length < 2) {
              dispatch(SetKeyEvents(newKeyEvents))
            }
            if(key == " ") {
              dispatch(ResetState(initialState));
            }
          })
        >
          (if(state.keyEvents |> List.length > 0) {
             switch(List.nth(state.keyEvents, 0)) {
             | "a" => <Image src="frame3a.png" width=600 height=450 />
             | "'" => <Image src="frame3b.png" width=600 height=450 />
             | _   => <Image src="frame2.png" width=600 height=450 />
            }
          } else {
            <Image src="frame2.png" width=600 height=450 />
          })
        </View>
      )
     }
    )
  });



