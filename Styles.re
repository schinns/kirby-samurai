open Revery;
open Revery.UI;

let appStyle =
  Style.[
    position(`Absolute),
    justifyContent(`Center),
    alignItems(`Center),
    bottom(0),
    top(0),
    left(0),
    right(0),
    backgroundColor(Colors.black)
  ];

let gameStyle = 
  Style.[
    backgroundColor(Colors.white),
    justifyContent(`Center),
    alignItems(`Center),
    width(400),
    height(400),
  ];

let textStyle = 
  Style.[
    color(Colors.black),
    fontFamily("Roboto-Regular.ttf"),
    fontSize(20),
  ];

