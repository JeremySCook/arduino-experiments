void buttonSequence(){
  if(buttonState == 0){
    if(digitalRead(auxRightButton) == 0){ //button depressed, turn on beat
      buttonState = 1;
      beatOn = 1;
      delay(10);
    }
  }
  if(buttonState == 1){
    if(digitalRead(auxRightButton) == 1){ //button released, leave beat on
      buttonState = 2;
      //beatOn = 1;
      delay(10);
    }    
  }
  if(buttonState == 2){
    if(digitalRead(auxRightButton) == 0){ //button depressed, turn off beat, turn on random
      //MIDI.sendNoteOff(48, 63, 1); //needed???
      buttonState = 3;
      beatOn = 0;
      beatStep = 0; //reset auto beat seqeunce to step 0 when turned off
      randomNotesOn = 1; //turn randomNotes routine on
      delay(10);
    }
  }
  if(buttonState == 3){
    if(digitalRead(auxRightButton) == 1) //button released, leave random notes on
      buttonState = 4;
      delay(10);
  }
  if(buttonState == 4){
    if(digitalRead(auxRightButton) == 0) //button depressed
      buttonState = 5;
      randomNotesOn = 0; //turn randomNotes routine off
      delay(10);
  }
  if(buttonState == 5){
    if(digitalRead(auxRightButton) == 1) //button released, go to start conditions
      buttonState = 0;
      delay(10);
  }
}
