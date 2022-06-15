void GetKey()
{
  if (digitalRead(bN1pin) == LOW) {
    tone(piPin, 400, 10);
    cMenu.wait = 40;
    if (cStatus.alert && !cStatus.mute) cStatus.mute = true;
    cMenu.nom++;
    cMenu.shift = 0;
  }

  if (digitalRead(bN2pin) == LOW) {
    tone(piPin, 200, 10);
    cMenu.wait = 22;    
    cMenu.shift--;
  } 

  if (digitalRead(bN3pin) == LOW) {
    tone(piPin, 300, 10);
    cMenu.wait = 22;
    cMenu.shift++;
  } 

}

void GetFlags() {
  if (!digitalRead(ePin)) {
    if (cStatus.engine < 200)cStatus.engine++;
  } else cStatus.engine = 0;

  if (!digitalRead(dPin)) {
    if (cStatus.door < 500)cStatus.door++;
  } else cStatus.door = 0;
}
