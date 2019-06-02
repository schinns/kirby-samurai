open Revery;
open Revery_Core;
open Revery.UI;
open Styles;

type t = 
  | NA
  | Tie
  | Kirby
  | MetaKnight;

type gameState = 
  | Stop
  | PreStart
  | Start;

type state = {
  winner: t,
  timer: int,
  time: float,
  keyEvents: list(string),
};

type action =
  | SetKeyEvents(list(string))
  | DetermineWinner(t);

let reducer = (action, state) =>
  switch(action) {
  | SetKeyEvents(events) => {...state, keyEvents: events }
  | DetermineWinner(player) => {...state, winner: player }
  };

let component = React.component("KirbySamurai");

let createElement = (~children as _, ()) => 
  component(hooks => {
    let (state, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={
          winner: NA,
          timer: 3,
          time: 0.,
          keyEvents: []
        },
        reducer,
        hooks
      );

    (hooks,
     <View 
       ref={r => Focus.focus(r)}
       style=gameStyle
       onKeyDown=((event: NodeEvents.keyEventParams) => {
         //key event
         let key = event.key |> Key.toString;
         // new key event state
         let newKeyEvents = List.append(state.keyEvents, [key]);
         //dispatch only up to 2 events
         if(state.keyEvents |> List.length < 2) {
           dispatch(SetKeyEvents(newKeyEvents))
         }
       })
     >
       <Text style=textStyle text="Kirby Samurai" />
       <Text 
         style=textStyle 
         text=(
           if(state.keyEvents |> List.length > 0) {
             List.nth(state.keyEvents, 0) == "a" ?
               "Kirby Wins!"
               : "Meta Knight Wins!"
           } else {
             "Go!"
           }
         )
       />
     </View>
    )
  });



