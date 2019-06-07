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
    backgroundColor(Colors.lightBlue),
    justifyContent(`FlexStart),
    alignItems(`Center),
    width(600),
    height(450),
  ];
let gameStyle1 = 
  Style.[
    backgroundColor(Colors.cornsilk),
    justifyContent(`Center),
    alignItems(`Center),
    width(600),
    height(450),
    bottom(0),
    top(0),
    left(0),
    right(0),
  ];
let gameStyle2 = 
  Style.[
    backgroundColor(Colors.lightPink),
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
  ];

let kirbyStyle = 
  Style.[
    justifyContent(`Center),
    alignItems(`Center),
    position(`Absolute),
  ];
