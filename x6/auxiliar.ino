/* auxiliar.ino, x6 Mark I - Robotic Arm, Arduino auxiliar sketch file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

bool isAllDone() {
  if (axis1.isDone() and
      axis2.isDone() and
      axis3.isDone() and
      axis4.isDone() and
      axis5.isDone() and
      axis6.isDone() and
      axis7.isDone()) {
    return true;
  }
  else {
    return false;
  }
}

int HighValue(float value1, float value2) {
  if (value1 > value2) {
    return value1;
  }
  else if (value2 > value1) {
    return value2;
  }
  else {
    return value1;
  }
}

void powerFailure() {
  if (digitalRead(power_sensor_pin) == LOW and stage3.status() == true) {
    CommandM81(3);  // Power off stage 3
  }
}

void powerStandby() {
  if (standby.check()) {
    if (!standby_status) {
      echo("Entering in standby... ");
      standby_status = true;
      standby_done = false;
      CommandG28();  // Home axes
    }
  }
  else {
    standby_status = false;
  }
  if (isAllDone() and !standby_done) {
    delay(1000);
    CommandM81();  // Power off
    standby_done = true;
    Serial.println("Done.");
  }
}

void standbyReset() {
  if (stage2.status() and stage3.status() and digitalRead(power_sensor_pin)) {
    standby.reset();
  }
}

/* spinCounter
 * 
 * Description
 *   Fan spin counter.
 * 
 *   spinCounter()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void spinCounter() {
  fan_control.counter();
}
