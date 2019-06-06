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
  seconds: int,
};

type action =
  | SetKeyEvents(list(string))
  | SetGameState(gameStateT)
  | CountDown
  | DetermineWinner(t);

let reducer = (action, state) =>
  switch(action) {
  | SetKeyEvents(events) => { ...state, keyEvents: events }
  | DetermineWinner(player) => { ...state, winner: player }
  | SetGameState(newState) => { ...state, gameState: newState }
  | CountDown => {...state, seconds: state.seconds + 1}
  };

let component = React.component("KirbySamurai");

let createElement = (~children as _, ()) => 
  component(hooks => {
    let (state, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={
          winner: NA,
          timer: 3,
          keyEvents: [],
          gameState: Stop,
          seconds: 0,
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
         //press spacebar to start game
         if(key == " ") {
           dispatch(SetGameState(PreRunning)) 
         }
       })
     >
       <Text style=textStyle text="Kirby Samurai" />
       (
         switch(state.gameState) {
         | Stop => (
           <Clickable onClick=(() => dispatch(SetGameState(PreRunning)))>
             <Text style=textStyle text="Play!" />
           </Clickable>
         )
         | PreRunning => {
           
           <View>
             <Text style=textStyle text="..." />
           </View>
         }
         | Running => (
           <View 
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
                 dispatch(SetKeyEvents([]))
               }
             })
           >
             <Text 
               style=textStyle 
               text=(
                 if(state.keyEvents |> List.length > 0) {
                   switch(List.nth(state.keyEvents, 0)) {
                   | "a" => "Kirby Wins!"
                   | "'" => "Meta Knight Wins!"
                   | _   => "Go!"
                   }
                 } else {
                   "Go!"
                 }
               )
             />
           </View>
         )
         }
    )
     </View>
    )
  });



