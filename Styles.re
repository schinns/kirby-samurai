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
    justifyContent(`FlexStart),
    alignItems(`Center),
    width(600),
    height(450),
  ];

let textStyle = 
  Style.[
    color(Colors.black),
    fontFamily("Roboto-Regular.ttf"),
    fontSize(20),
    marginTop(10),
  ];

