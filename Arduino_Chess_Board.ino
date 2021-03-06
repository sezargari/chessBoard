
//Set up chess board names
String squareName[64] =
{ "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

//set up chess board positions, since squares make the input low, then 0 represent peices
int chessBoard[64] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};



void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);

  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);

  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);

  pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  pinMode(A15, INPUT_PULLUP);
  pinMode(A14, INPUT_PULLUP);
  pinMode(A13, INPUT_PULLUP);
  pinMode(A12, INPUT_PULLUP);
  pinMode(A11, INPUT_PULLUP);
  pinMode(A10, INPUT_PULLUP);
  pinMode(A9, INPUT_PULLUP);
  pinMode(A8, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
}


/*
   Loop though to current array to see if it matches the prevous board state
   If a square does not match its previous value, it takes the name of the square
   Usualy, two squares should change value each move
   Special Cases:
   If a piece is taken, two pieces will be taken off the board before one being placed back
   When castling, the same thing happens, but two are placed back
   Pawn Promotion: piece gets placed back on itself. We can assume queen.
   For the Following code to work, Pin 2 needs to be connected to square A8, Pin 3 to square A7, and so on.
*/

String currMove = "";
String firstSquare = "";
int pos = 2;
bool computerTurn = false; //Player will make the first move
void loop() {
  if (computerTurn) {
    //read in serial from Raspberry Pi
    //Flip the value of the two spots read from USB
    /*if(Serial.available() > 0) {
      String compmove = Serial.readStringUntil(' ');
      for(int x=0;x<64;x++){
        if(squareName[x] == compmove){
          chessBoard[x] = !chessBoard[x];
        }
      }
      compmove = Serial.readStringUntil(' ');
      for(int x=0;x<64;x++){
        if(squareName[x] == compmove){
          chessBoard[x] = !chessBoard[x];
        }
      }*/

    computerTurn = false;
    //}

  }
  if (!computerTurn) {
    pos = 2; //start with pin2, as pin 0 and 1 are used for serial communication

    for (int x = 0; x < 64; x++) { //Loop through the chess board
      if (pos < 54) {
        if (chessBoard[x] != digitalRead(pos)) { //if the square does not match the previous value of the position on the chess board
          if (currMove == "") { //if no move is in progress
            firstSquare = squareName[pos - 2]; //store initial square;
            currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
            //Since pos starts at 2, subtract 2 to get correct square
            chessBoard[x] = !chessBoard[x];   //update the square to new value
          }
          else {    //if move is in progress
            if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
              currMove = currMove + squareName[pos - 2]; //append second square to inital string
              if (chessBoard[x] == 0) { //if a piece is being taken
                while (digitalRead(pos)); //wait for peice to take it's place
              }
              else {
                chessBoard[x] = !chessBoard[x];   //update the empty square to new value
              }
              firstSquare = ""; //clear firstSquare string
              Serial.println(currMove); //print move just made to the screen
              currMove = "";   //clear current move
              computerTurn = true;
            }
            else { //if the player does place the piece back on inital square
              currMove = "";  //reset the move
              firstSquare = "";
              chessBoard[x] = !chessBoard[x];   //update the square to original value
            }
          }
        }
      }
      else { //Since pos cant account for analog pins, they need seperate if statements
        if (pos == 54) {
          if (chessBoard[x] != digitalRead(A15)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                if (squareName[pos - 2] == 1) { //if a piece is being taken
                  //dont store the value of the taken piece
                } else {
                  currMove = currMove + squareName[pos - 2]; //append second square to inital string
                  if (chessBoard[x] == 0) { //if a piece is being taken
                    while (digitalRead(pos)); //wait for peice to take it's place
                  }
                  else {
                    chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                  }
                  firstSquare = ""; //clear firstSquare string
                  Serial.println(currMove); //print move just made to the screen
                  currMove = "";   //clear current move
                  computerTurn = true;
                }
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 55) {
          if (chessBoard[x] != digitalRead(A14)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 56) {
          if (chessBoard[x] != digitalRead(A13)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 57) {
          if (chessBoard[x] != digitalRead(A12)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 58) {
          if (chessBoard[x] != digitalRead(A11)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 59) {
          if (chessBoard[x] != digitalRead(A10)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 60) {
          if (chessBoard[x] != digitalRead(A9)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 61) {
          if (chessBoard[x] != digitalRead(A8)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 62) {
          if (chessBoard[x] != digitalRead(A7)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 63) {
          if (chessBoard[x] != digitalRead(A6)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 64) {
          if (chessBoard[x] != digitalRead(A5)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
        else if (pos == 65) {
          if (chessBoard[x] != digitalRead(A4)) {
            if (currMove == "") { //if no move is in progress
              firstSquare = squareName[pos - 2]; //store initial square;
              currMove = "m" + squareName[pos - 2]; //add m before the square to signal start of a move
              chessBoard[x] = !chessBoard[x];   //update the square to new value
            }
            else {    //if move is in progress
              if (squareName[pos - 2] != firstSquare) { //if the player doesn't place the piece back on inital square
                currMove = currMove + squareName[pos - 2]; //append second square to inital string
                if (chessBoard[x] == 0) { //if a piece is being taken
                  while (digitalRead(pos)); //wait for peice to take it's place
                }
                else {
                  chessBoard[x] = !chessBoard[x];   //update the empty square to new value
                }
                firstSquare = ""; //clear firstSquare string
                Serial.println(currMove); //print move just made to the screen
                currMove = "";   //clear current move
                computerTurn = true;
              }
              else { //if the player does place the piece back on inital square
                currMove = "";  //reset the move
                firstSquare = "";
                chessBoard[x] = !chessBoard[x];   //update the square to original value
              }
            }
          }
        }
      }
      pos += 1; //go to next square
    }
  }
}
