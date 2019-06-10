open Revery;
open Revery.UI;
open Styles;

let init = app => {
  let window = App.createWindow(app, "Kirby Samurai");
  let element = 
    <View style=appStyle>
      <KirbySamurai />
    </View>;

  let _ = UI.start(window, element);
}

App.start(init);
      


