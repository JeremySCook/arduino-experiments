void buttonSequence(){
  if(buttonState == 0){
    if(digitalRead(auxRightButton) == 0){ //button depressed, turn on beat
      buttonState = 1;
      //MIDI.sendNoteOn(48, 1, 1); //for testing
      beatOn = 1;
      delay(50);
    }
  }
  if(buttonState == 1){
    if(digitalRead(auxRightButton) == 1){ //button released, leave beat on
      buttonState = 2;
      //MIDI.sendNoteOn(48, 2, 1); //for testing
      delay(50);
    }    
  }
  if(buttonState == 2){
    if(digitalRead(auxRightButton) == 0){ //button depressed, turn off beat, turn on random
      buttonState = 3;
      //MIDI.sendNoteOn(48, 3, 1); //for testing
      beatOn = 0; // controls autobeat
      beatStep = 0; //reset auto beat seqeunce to step 0 when turned off
      randomNotesOn = 1; //turn randomNotes routine on
      delay(50);
    }
  }
  if(buttonState == 3){
    if(digitalRead(auxRightButton) == 1) //button released, leave random notes on
      buttonState = 4;
      //MIDI.sendNoteOn(48, 4, 1); //for testing
      delay(50);
  }
  if(buttonState == 4){
    if(digitalRead(auxRightButton) == 0) //button depressed
      buttonState = 5;
      //MIDI.sendNoteOn(48, 5, 1); //for testing
      randomNotesOn = 1; //turn randomNotes routine off
      delay(50);
  }
  if(buttonState == 5){
    if(digitalRead(auxRightButton) == 1) //button released, go to start conditions
      buttonState = 0;
      randomNotesOn = 0; //turn randomNotes routine off
      delay(50);
  }
}
