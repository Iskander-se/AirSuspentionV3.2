void GetKey()
{
  if (digitalRead(bN1pin) == LOW) {
    tone(piPin, 400, 10);
    cMenu.wait = 25;
    if (cStatus.alert && !cStatus.mute) cStatus.mute = true;
    cMenu.nom++;
    cMenu.shift = 0;
  }

  if (digitalRead(bN2pin) == LOW) {
    tone(piPin, 200, 10);
    cMenu.wait = 20;
    cMenu.shift--;
  }

  if (digitalRead(bN3pin) == LOW) {
    tone(piPin, 300, 10);
    cMenu.wait = 20;
    cMenu.shift++;
  }

}

void GetFlags() {
  if (digitalRead(ePin) == LOW || !cStatus.fcheckEngine) {
    if (cStatus.engine < 200)cStatus.engine++;
  } else cStatus.engine = 0;

  if (digitalRead(dPin) == LOW || !cStatus.fcheckDoor || cStatus.servicemode) {
    if (cStatus.door < 500)cStatus.door++;
  } else cStatus.door = 0;
}
