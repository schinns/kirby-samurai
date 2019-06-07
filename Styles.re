open Revery;
open Revery.UI;
open Revery.UI.Components;

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

let game = (~children, ()) => {
    <Center>
        <Container width=600 height=450>
            ...children
        </Container>
    </Center>
};

let textStyle = 
  Style.[
    color(Colors.black),
    fontFamily("Roboto-Regular.ttf"),
    fontSize(20),
  ];
/*
let kirby1 = 
  Style.[
    position(`Absolute),
  ];
  */
