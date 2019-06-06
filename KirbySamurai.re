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

type dispose = unit => unit;
let noop = () => ();

type gameStateT = 
  | Stop
  | PreRunning
  | Running;

type state = {
  dispose,
  winner: t,
  timer: int,
  time: float,
  keyEvents: list(string),
  gameState: gameStateT,
  timerIsRunning: bool,
  elapsedTime: float, 
};

type action =
  | TimerTick(float)
  | StartTimer(dispose)
  | StopTimer
  | SetKeyEvents(list(string))
  | SetGameState(gameStateT)
  | DetermineWinner(t);

let reducer = (action, state) =>
  switch(action) {
  | SetKeyEvents(events) => { ...state, keyEvents: events }
  | DetermineWinner(player) => { ...state, winner: player }
  | StartTimer(fn) => { ...state, dispose: fn, timerIsRunning: true, elapsedTime: 0. }
  | StopTimer => 
    state.dispose();
    let retain = {...state, dispose: noop, timerIsRunning: false, elapsedTime: 0.};
    retain;
  | SetGameState(newState) => { ...state, gameState: newState }
  | TimerTick(deltaTime) => {
    ...state,
    elapsedTime: 
      state.timerIsRunning ? deltaTime +. state.elapsedTime : state.elapsedTime
  }
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
          keyEvents: [],
          gameState: Stop,
          dispose: noop,
          timerIsRunning: false,
          elapsedTime: 0.
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
           let dispose = Tick.interval(t => dispatch(TimerTick(t |> Time.toSeconds)), Seconds(0.));
           dispatch(StartTimer(dispose));

           <View
             onKeyDown=((event: NodeEvents.keyEventParams) => {
               //key event
               let key = event.key |> Key.toString;
               print_endline(key);
               //press spacebar to start game
               if(key == " ") {
                 print_endline("stop");
                 dispatch(StopTimer);
                 //dispatch(SetGameState(Running)) 
               }
             })
           >
             <Text style=textStyle text=(state.elapsedTime |> string_of_float) />
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



