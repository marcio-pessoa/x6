/* commands.ino, x6 Mark I - Robotic Arm, Arduino commands sketch file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

/* Command0
 * 
 * Description
 *   .
 * 
 *   Command0()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool Command0() {
  echoln(F("Unknown command"));
  return true;
}

/* CommandG0
 * 
 * Description
 *   .
 * 
 *   CommandG0()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG0(int x, int y, int z, int u, int v, int w, int t) {
  if (!digitalRead(power_sensor_pin)) {
    done = true;
    status(true);
    return true;
  }
  if (x != FLIMIT) {
    done = false;
    axis1.positionWrite(x);
  }
  if (y != FLIMIT) {
    done = false;
    axis2.positionWrite(y);
  }
  if (z != FLIMIT) {
    done = false;
    axis3.positionWrite(z);
  }
  if (u != FLIMIT) {
    done = false;
    axis4.positionWrite(u);
  }
  if (v != FLIMIT) {
    done = false;
    axis5.positionWrite(v);
  }
  if (w != FLIMIT) {
    done = false;
    axis6.positionWrite(w);
  }
  if (t != FLIMIT) {
    done = false;
    axis7.positionWrite(t);
  }
}

/* CommandG3
 * 
 * Description
 *   .
 * 
 *   CommandG3()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG3(int x, int y, int z, int u, int v, int w, int t) {
  if (x != FLIMIT) {
    axis1.delayWrite(x);
  }
  if (y != FLIMIT) {
    axis2.delayWrite(y);
  }
  if (z != FLIMIT) {
    axis3.delayWrite(z);
  }
  if (u != FLIMIT) {
    axis4.delayWrite(u);
  }
  if (v != FLIMIT) {
    axis5.delayWrite(v);
  }
  if (w != FLIMIT) {
    axis6.delayWrite(w);
  }
  if (t != FLIMIT) {
    axis7.delayWrite(t);
  }
  return false;
}

/* CommandG6
 * 
 * Description
 *   .
 * 
 *   CommandG6()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG6(unsigned long seconds) {
  if (!digitalRead(power_sensor_pin)) {
    done = true;
    status(true);
    return true;
  }
  if (seconds > 0) {
    standbyReset();
    if (seconds * 1000 > standby.residual()) {
      standby.set(standby.read() + (seconds * 1000 - standby.residual()));
    }
    demonstration_period.set((unsigned long)seconds * 1000);
  }
  else {
    echo("Demonstration: ");
    echoln(human_time(demonstration_period.residual()));
  }
}

/* CommandG28
 * 
 * Description
 *   .
 * 
 *   CommandG28()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG28() {
  if (!digitalRead(power_sensor_pin)) {
    done = true;
    status(true);
    return true;
  }
  done = false;
  CommandG90();  // Absolute programming
  axis1.delayWrite(40);
  axis2.delayWrite(30);
  axis3.delayWrite(20);
  axis4.delayWrite(15);
  axis5.delayWrite(10);
  axis6.delayWrite(5);
  axis7.delayWrite(1);
  axis1.positionWrite(axis1.parkRead());
  axis2.positionWrite(axis2.parkRead());
  axis3.positionWrite(axis3.parkRead());
  axis4.positionWrite(axis4.parkRead());
  axis5.positionWrite(axis5.parkRead());
  axis6.positionWrite(axis6.parkRead());
  axis7.positionWrite(axis7.parkRead());
}

/* CommandG90
 * 
 * Description
 *   .
 * 
 *   CommandG90()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG90() {
  axis1.absolute(true);
  axis2.absolute(true);
  axis3.absolute(true);
  axis4.absolute(true);
  axis5.absolute(true);
  axis6.absolute(true);
  axis7.absolute(true);
  return false;
}

/* CommandG91
 * 
 * Description
 *   .
 * 
 *   CommandG91()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG91() {
  axis1.absolute(false);
  axis2.absolute(false);
  axis3.absolute(false);
  axis4.absolute(false);
  axis5.absolute(false);
  axis6.absolute(false);
  axis7.absolute(false);
  return false;
}

/* CommandM17
 * 
 * Description
 *   Attach motors.
 * 
 *   CommandM17()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM17() {
  standby.reset();
  servo1.attach(axis1.pinRead());
  servo1.write(axis1.positionRead());
  servo2.attach(axis2.pinRead());
  servo2.write(axis2.positionRead());
  servo3.attach(axis3.pinRead());
  servo3.write(axis3.positionRead());
  servo4.attach(axis4.pinRead());
  servo4.write(axis4.positionRead());
  servo5.attach(axis5.pinRead());
  servo5.write(axis5.positionRead());
  servo6.attach(axis6.pinRead());
  servo6.write(axis6.positionRead());
  servo7.attach(axis7.pinRead());
  servo7.write(axis7.positionRead());
  return false;
}

/* CommandM18
 * 
 * Description
 *   .
 * 
 *   CommandM18()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM18() {
  CommandM0();  // Compulsory stop
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();
  servo5.detach();
  servo6.detach();
  servo7.detach();
  return false;
}

/* CommandM80
 * 
 * Description
 *   .
 * 
 *   CommandM80()
 * 
 * Parameters
 *   stage
 * 
 * Returns
 *   bool
 */
bool CommandM80(byte stage) {
  switch (stage) {
    case 0:
      stage2.on();
      delay(50);
      if (digitalRead(power_sensor_pin)) {
        standbyReset();
        stage3.on();
        CommandM17();  // Attach motors
        return !stage3.status();
      }
      return true;
    case 1:
      return false;
    case 2:
      stage2.on();
      return !stage2.status();
    case 3:
      if (!stage2.status()) {
        debugln("Please, power on stage 2 first.");
        return true;
      }
      if (!digitalRead(power_sensor_pin)) {
        debugln("Please, check power cable.");
        return true;
      }
      stage3.on();
      return !stage3.status();
    default:
      echo("Power status");
      if ((debug_mode)) {
        echoln(String("\n") +
               "  " + 
               stage2.nameRead() + ": " + (stage2.status() ? "On" : "Off") +
               "\n" + "  " + 
               stage3.nameRead() + ": " + (stage3.status() ? "On" : "Off") +
               "\n" + "  DC current: " +
               (digitalRead(power_sensor_pin) ? "Yes" : "No"));
      }
      else {
        Serial.println(String(": ") +
                       (digitalRead(power_sensor_pin) ? "On" : "Off"));
      }
      return !digitalRead(power_sensor_pin);
      break;
  }
}

/* CommandM81
 * 
 * Description
 *   .
 * 
 *   CommandM81()
 * 
 * Parameters
 *   stage
 * 
 * Returns
 *   bool
 */
bool CommandM81(byte stage) {
  switch (stage) {
    case 0:
      CommandM18();  // Detach motors
      stage2.off();
      stage3.off();
      delay(50);
      return stage3.status();
    case 1:
      return true;
    case 2:
      CommandM18();  // Detach motors
      stage2.off();
      return stage2.status();
    case 3:
      CommandM18();  // Detach motors
      stage3.off();
      return stage3.status();
    default:
      return CommandM80(254);  // Power on (display status)
  }
}

/* CommandM99
 * 
 * Description
 *   Reset system.
 * 
 *   CommandM99()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM99() {
  echoln("Reseting...\n");
  CommandM18();  // Detach motors
  CommandM81();  // Power off
  x6.reset();
}

/* CommandM100
 * 
 * Description
 *   Shows help messages.
 * 
 *   CommandM100()
 * 
 * Parameters
 *   letter: The command initial letter. It's used to display a specific help
 *           about a letter.
 *           If letter equals to zero, all help messages will be shown.
 * 
 * Returns
 *   void
 */
bool CommandM100(char letter = 0) {
  if (letter == 'G' or letter == 0) {
    echoln(F("G0\tMove axes"));
    echoln(F("G3\tDelay between moves"));
    echoln(F("G4\tDwell"));
    echoln(F("G6\tDemonstratio mode"));
    echoln(F("G28\tHome axes"));
    echoln(F("G90\tAbsolute programming"));
    echoln(F("G91\tIncremental programming"));
  }
  if (letter == 'M' or letter == 0) {
    echoln(F("M0\tCompulsory stop"));
    echoln(F("M15\tSystem info"));
    echoln(F("M17\tAttach motors"));
    echoln(F("M18\tDetach motors"));
    echoln(F("M70\tLaser status"));
    echoln(F("M71\tLaser on"));
    echoln(F("M72\tLaser off"));
    echoln(F("M80\tPower on"));
    echoln(F("M81\tPower off"));
    echoln(F("M86\tAxes information"));
    echoln(F("M87\tIs all done?"));
    echoln(F("M88\tDistance measure"));
    echoln(F("M89\tMemory information"));
    echoln(F("M90\tFan information"));
    echoln(F("M91\tTemperature information"));
    echoln(F("M92\tSystem information"));
    echoln(F("M99\tReset system"));
    echoln(F("M100\tThis help message"));
    echoln(F("M111\t(debug_mode) mode"));
    echoln(F("M124\tStop all axes"));
    echoln(F("M400\tWait for current moves to finish"));
  }
  if (letter == 'R' or letter == 0) {
    echoln(F("R0\tRepeat last command"));
  }
}

/* command_minimum
 * 
 * Description
 *   Set soft minimum position (limit) for axes.
 * 
 *   command_minimum()
 * 
 * Parameters
 *   Receive all parameters from SerialCommand next() method.
 * 
 * Returns
 *   none
 */
bool Command_minimum(int x, int y, int z, int u, int v, int w, int t) {
  axis1.softMinimumWrite(x);
  axis2.softMinimumWrite(y);
  axis3.softMinimumWrite(z);
  axis4.softMinimumWrite(u);
  axis5.softMinimumWrite(v);
  axis6.softMinimumWrite(w);
  axis7.softMinimumWrite(t);
}

/* command_maximum
 * 
 * Description
 *   Set soft maximum position (limit) for axes.
 * 
 *   command_maximum()
 * 
 * Parameters
 *   Receive all parameters from SerialCommand next() method.
 * 
 * Returns
 *   none
 */
bool Command_maximum(int x, int y, int z, int u, int v, int w, int t) {
  axis1.softMaximumWrite(x);
  axis2.softMaximumWrite(y);
  axis3.softMaximumWrite(z);
  axis4.softMaximumWrite(u);
  axis5.softMaximumWrite(v);
  axis6.softMaximumWrite(w);
  axis7.softMaximumWrite(t);
}

/* command_wait
 * 
 * Description
 *   .
 * 
 *   command_wait()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandG4(int p, int s) {
  unsigned long d = 0;
  if (p != FLIMIT) {
    d += p;
  }
  if (s != FLIMIT) {
    d += (s * 1000);
  }
  // delay(d);
  // return 0;
  wait.set(d);
  done = false;
}

/* command_wait
 * 
 * Description
 *   .
 * 
 *   command_wait()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool Command_wait(int x, int y, int z, int u, int v, int w, int t) {
  if (x != FLIMIT) {
    wait1.set(x);
  }
  if (y != FLIMIT) {
    wait2.set(y);
  }
  if (z != FLIMIT) {
    wait3.set(z);
  }
  if (u != FLIMIT) {
    wait4.set(u);
  }
  if (v != FLIMIT) {
    wait5.set(v);
  }
  if (w != FLIMIT) {
    wait6.set(w);
  }
  if (t != FLIMIT) {
    wait7.set(t);
  }
}

/* CommandM0
 * 
 * Description
 *   Stop all axes.
 * 
 *   CommandM0()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM0() {
  // Stop demonstration (if it's running)
  demonstration_period.set(0);
  wait.set(0);
  // Set next position as current position (stop)
  axis1.positionWrite(axis1.positionRead());
  axis2.positionWrite(axis2.positionRead());
  axis3.positionWrite(axis3.positionRead());
  axis4.positionWrite(axis4.positionRead());
  axis5.positionWrite(axis5.positionRead());
  axis6.positionWrite(axis6.positionRead());
  axis7.positionWrite(axis7.positionRead());
  return false;
}

/* CommandM15
 * 
 * Description
 *   .
 * 
 *   CommandM15()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM15() {
  CommandM92();
  CommandM89();
  CommandM80();
  CommandM91();
  command_fan();
  command_uptime();
  command_standby();
  command_axes();
}

/* CommandM87
 * 
 * Description
 *   .
 * 
 *   CommandM87()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM87() {
  if (isAllDone()) {
    echoln("Move (OK): Done");
  }
  else {
    echoln("Move (Pending): On going");
  }
}

/* CommandM89
 * 
 * Description
 *   .
 * 
 *   CommandM89()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM89() {
  int total = 8 * 1024;
  int free = freeMemory();
  int used = total - free;
  int percent = (float)used * 100 / total;
  // 
  Alarm memory(75, 85);
  memory.nameWrite("Memory");
  memory.unitWrite("%");
  memory.check(percent);
  // 
  echoln(memory.nameRead() + " (" + memory.status_name() + "): " + 
         percent + memory.unitRead() + " used");
  if ((debug_mode)) {
    echoln("  SRAM:\t" + String(total) + " B\n" +
           "  Used:\t" + used + " B\n" +
           "  Free:\t" + free + " B\n" +
           "  Warning: " + memory.max_warningRead() + memory.unitRead() + "\n" +
           "  Critical: " + memory.max_criticalRead() + memory.unitRead());
  }
}

/* CommandM91
 * 
 * Description
 *   .
 * 
 *   CommandM91()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM91() {
  // Power Supply Temperature
  echoln(power_supply_temperature.nameRead() + " (" +
         power_supply_temperature.status_name() + "): " + 
         power_supply_temperature.valueRead() +
         power_supply_temperature.unitRead());
  if ((debug_mode))
    echoln("  Warning low: " +
           String(power_supply_temperature.min_warningRead()) +
           power_supply_temperature.unitRead() + "\n" +
           "  Critical low: " +
           String(power_supply_temperature.min_criticalRead()) +
           power_supply_temperature.unitRead() + "\n" +
           "  Warning high: " +
           String(power_supply_temperature.max_warningRead()) +
           power_supply_temperature.unitRead() + "\n" +
           "  Critical high: " +
           String(power_supply_temperature.max_criticalRead()) +
           power_supply_temperature.unitRead());
  // Microcontroller Temperature
  echoln(microcontroller_temperature.nameRead() + " (" +
         microcontroller_temperature.status_name() + "): " + 
         microcontroller_temperature.valueRead() +
         microcontroller_temperature.unitRead());
  if ((debug_mode))
    echoln("  Warning: " +
           String(microcontroller_temperature.min_warningRead()) +
           microcontroller_temperature.unitRead() + "\n" +
           "  Critical low: " +
           String(microcontroller_temperature.min_criticalRead()) +
           microcontroller_temperature.unitRead() + "\n" +
           "  Warning high: " +
           String(microcontroller_temperature.max_warningRead()) +
           microcontroller_temperature.unitRead() + "\n" +
           "  Critical high: " +
           String(microcontroller_temperature.max_criticalRead()) +
           microcontroller_temperature.unitRead());
}

/* CommandM92
 * 
 * Description
 *   .
 * 
 *   CommandM92()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM92() {
  echoln(x6.version());
  if ((debug_mode) or (millis() < 100)) {
    echoln(x6.owner());
    echoln(x6.compiled());
    echoln(x6.license());
    echoln(x6.website());
    echoln(x6.contact());
  }
}

/* CommandM111
 * 
 * Description
 *   .
 * 
 *   CommandM111()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM111() {
  debug_mode = !debug_mode;
  return false;
}

/* CommandR0
 * 
 * Description
 *   .
 * 
 *   Command0()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandR0() {
  GcodeRepeat();
}

/* command_fan
 * 
 * Description
 *   .
 * 
 *   command_fan()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool command_fan() {
  echoln(fan.nameRead() + " (" +
         fan.status_name() + "): " +
         (int)fan.valueRead() +
         fan.unitRead());
  if ((debug_mode)) {
    echoln("  Warning: " + String(fan.max_warningRead()) + fan.unitRead() + "\n" +
           "  Critical: " + String(fan.max_criticalRead()) + fan.unitRead());
  }
}

/* command_standby
 * 
 * Description
 *   .
 * 
 *   command_standby()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool command_standby() {
  echo("Standby: ");
  echoln(human_time(standby.residual()));
}

/* command_uptime
 * 
 * Description
 *   .
 * 
 *   command_uptime()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool command_uptime() {
  echo("Uptime: ");
  echo(human_time(millis()));
  if ((debug_mode)) {
    echo(" (");
    echo(String(millis()));
    echo(")");
  }
  echoln("");
}

/* command_axes
 * 
 * Description
 *   .
 * 
 *   command_axes()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool command_axes() {
  echoln(String("Axes position: ") +
                axis1.nameRead() + axis1.positionRead() + " " +
                axis2.nameRead() + axis2.positionRead() + " " +
                axis3.nameRead() + axis3.positionRead() + " " +
                axis4.nameRead() + axis4.positionRead() + " " +
                axis5.nameRead() + axis5.positionRead() + " " +
                axis6.nameRead() + axis6.positionRead() + " " +
                axis7.nameRead() + axis7.positionRead());
  echoln(String("Axes delay: ") +
                axis1.nameRead() + axis1.delayRead() + " " +
                axis2.nameRead() + axis2.delayRead() + " " +
                axis3.nameRead() + axis3.delayRead() + " " +
                axis4.nameRead() + axis4.delayRead() + " " +
                axis5.nameRead() + axis5.delayRead() + " " +
                axis6.nameRead() + axis6.delayRead() + " " +
                axis7.nameRead() + axis7.delayRead());
  if ((debug_mode)) {
    echoln(axis1.status() + "\n" +
           axis2.status() + "\n" +
           axis3.status() + "\n" +
           axis4.status() + "\n" +
           axis5.status() + "\n" +
           axis6.status() + "\n" +
           axis7.status());
  }
}
