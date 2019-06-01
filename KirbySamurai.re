open Revery;
open Revery.UI;
open Styles;

type t = 
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
};

type action =
  | DetermineWinner(t);

let reducer = (action, state) =>
  switch(action) {
  | DetermineWinner(player) => {...state, winner: player }
  };

let handleKeyPress = (event: NodeEvents.keyPressEventParams) => {
  print_endline("keypressed");
  print_endline(event.character)
};

let handleKeyDown= (event: NodeEvents.keyEventParams) => {
  print_endline(event.key |> Revery_Core.Key.toString);
}

let component = React.component("KirbySamurai");

let createElement = (~children as _, ()) => 
  component(hooks => {
    let (state, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={
          winner: Tie,
          timer: 3,
          time: 0.
        },
        reducer,
        hooks
      );

    (hooks,
     <View 
       style=gameStyle
       onKeyPress=handleKeyPress
       onKeyDown=handleKeyDown
     >
       <Text style=textStyle text="Kirby Samurai" />
     </View>
    )
  });



