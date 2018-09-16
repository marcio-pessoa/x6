/* handlers.ino, x2 Mark I - Two Axes Platform, Arduino handlers sketch file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

bool AxesHandler() {
  // Don't move axes if system is in CRITICAL state
  if (general_status == CRITICAL) {
    return true;
  }
  // Don't move axes if power is down
  if (!digitalRead(power_sensor_pin) and done == false) {
    done = true;
    status(true);
    return true;
  }
  // Abandon handle if power if down
  if (!digitalRead(power_sensor_pin)) {
    return true;
  }
  // 
  if (axis1.positionReadRelative() or
      axis2.positionReadRelative() or
      axis3.positionReadRelative() or
      axis4.positionReadRelative() or
      axis5.positionReadRelative() or
      axis6.positionReadRelative() or
      axis7.positionReadRelative()) {
    standby.reset();
  }
  // 
  if (wait.check()) {
    // Check axis move after wait time
    if (wait1.check()) {
      axis1.run();
    }
    if (wait2.check()) {
      axis2.run();
    }
    if (wait3.check()) {
      axis3.run();
    }
    if (wait4.check()) {
      axis4.run();
    }
    if (wait5.check()) {
      axis5.run();
    }
    if (wait6.check()) {
      axis6.run();
    }
    if (wait7.check()) {
      axis7.run();
    }
    // Send data to servo motors
    servo1.write(axis1.positionRead());
    servo2.write(axis2.positionRead());
    servo3.write(axis3.positionRead());
    servo4.write(axis4.positionRead());
    servo5.write(axis5.positionRead());
    servo6.write(axis6.positionRead());
    servo7.write(axis7.positionRead());
    // 
    if (isAllDone() and done == false and wait.check()) {
      done = true;
      status(false);
    }
  }
}

void DemonstrationHandler() {
  if (!demonstration_period.check()) {
    done = false;
    if (axis1.isDone()) {
      axis1.positionWrite(random(axis1.hardMinimumRead(), axis1.hardMaxiumRead()));
      axis1.delayWrite(random(40 ,90));
    }
    if (axis2.isDone()) {
      axis2.positionWrite(random(0 ,100));
      axis2.delayWrite(random(30 ,80));
    }
    if (axis3.isDone()) {
      axis3.positionWrite(random(0, 80));
      axis3.delayWrite(random(20 ,70));
    }
    if (axis4.isDone()) {
      axis4.positionWrite(random(axis4.hardMinimumRead(), axis4.hardMaxiumRead()));
      axis4.delayWrite(random(10 ,60));
    }
    if (axis5.isDone()) {
      axis5.positionWrite(random(axis5.hardMinimumRead(), axis5.hardMaxiumRead()));
      axis5.delayWrite(random(10 ,50));
    }
    if (axis6.isDone()) {
      axis6.positionWrite(random(axis6.hardMinimumRead(), axis6.hardMaxiumRead()));
      axis6.delayWrite(random(5 ,20));
    }
    if (axis7.isDone()) {
      axis7.positionWrite(random(axis7.hardMinimumRead(), axis7.hardMaxiumRead()));
      axis7.delayWrite(random(1 ,10));
    }
  }
}

// void HealthCheckHandler() {
  // Temperature check
  // if (health_check_period.check()) {
    // Check sensor with high temperature
    // float high_temperature = HighValue(microcontroller_temperature.valueRead(), 
                                       // power_supply_temperature.valueRead());
    // Set fan speed
    // fan_control.writeSpeed(map(constrain(high_temperature, 20, 40),  // temperature
                             // 20, 40,    // From (minimum and maximum)
                             // 0, 100));  // To (minimum and maximum)
    // Join alarm status
    //~ byte general_status = UNKNOWN;
    // if (microcontroller_temperature.status() == OK and
        // power_supply_temperature.status() == OK) {
      // general_status = OK;
    // }
    // else if (microcontroller_temperature.status() == WARNING or
             // power_supply_temperature.status() == WARNING) {
      // general_status = WARNING;
    // }
    // else if (microcontroller_temperature.status() == CRITICAL or
             // power_supply_temperature.status() == CRITICAL) {
      // general_status = CRITICAL;
    // }
    // else {
      // general_status = UNKNOWN;
    // }
    // Check fan
    // if (fan.status() == CRITICAL and debug) {
      // command_fan();
    // }
    // If there are some temperature CRITICAL alarm
    // if (microcontroller_temperature.status() == CRITICAL or
        // power_supply_temperature.status() == CRITICAL) {
        // if (debug) {
          // CommandM91();
        // }
        // CommandM81(3);  // Power off stage 3
    // }
    // Notify status via LED
    // switch (general_status) {
      // case OK: {
        // led.set(0, 0, 255);
        // break;
      // }
      // case WARNING: {
        // led.set(255, 255, 0);
        // break;
      // }
      // case CRITICAL: {
        // led.set(255, 0, 0);
        // break;
      // }
      // case UNKNOWN: 
      // default: {
        // led.set(0, 255, 0);
        // break;
      // }
    // }
  // }
// }

void NotificationHandler() {
  // LED
  led.brightness(wave.sine());
  // Speaker
  if (speaker_period.check()) {
    speaker_beep_counter = (speaker_beep_counter + 1) % 8;
    if (general_status > speaker_beep_counter) {
      tone(speaker_pin, 2217, 60);
    }
  }
}

void PowerHandler() {
  powerStandby();
  powerFailure();
}

// void SensorsHandler() {
  // Temperature check
  // if (temperature_status.check()) {
    //~ microcontroller_temperature.check(microcontroller_TMP36.read());
    //~ power_supply_temperature.check(power_supply_TMP36.read());
  // }
  // Fan check
  // if (fan_status.check()) {
    // fan.check(fan_control.readSpeed());
  // }
// }
