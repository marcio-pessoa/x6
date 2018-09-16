/* gcode.ino, x6 Mark I - Robotic Arm, G-code parser sketch file
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 */

#define BUFFER_SIZE 48

char buffer[BUFFER_SIZE];
int buffer_pointer = 0;

char last_buffer[BUFFER_SIZE];
int last_buffer_pointer = 0;

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void status(bool i) {
  // Get last successfull command
  if (!i) {
    strncpy(last_buffer, buffer, buffer_pointer);
    last_buffer_pointer = buffer_pointer;
  }
  // Display return status
  Serial.println(i == false ? F("ok") : F("nok"));
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void echo(String message) {
  Serial.print(message);
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void echoln(String message) {
  echo(message + "\n");
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void debug(String message) {
  if (debug_mode) {
    echo(message);
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void debugln(String message) {
  if (debug_mode) {
    echoln(message);
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void GcodeReady() {
  buffer_pointer = 0;
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void GcodeCheck() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (buffer_pointer < BUFFER_SIZE-1) {
      buffer[buffer_pointer++] = c;
    }
    if (c == '\n') {
      buffer[buffer_pointer] = 0;
      GcodeParse();
      GcodeReady();
    }
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
float GcodeNumber(char code, float val) {
  char *ptr = buffer;
  while(ptr && *ptr && ptr < buffer + buffer_pointer) {
    if(*ptr == code) {
      return atof(ptr + 1);
    }
    ptr = strchr(ptr, ' ') + 1;
  }
  return val;
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void GcodeCopyCommand() {
  strncpy(last_buffer, buffer, buffer_pointer);
  last_buffer_pointer = buffer_pointer;
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
void GcodeRepeat() {
  strncpy(buffer, last_buffer, last_buffer_pointer);
  buffer_pointer = last_buffer_pointer;
  echo(String(last_buffer));
  GcodeParse();
  GcodeReady();
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int GcodeParse() {
  // 
  bool retval = false;
  bool skip_status = false;
  char letter = buffer[0];
  byte number = GcodeNumber(letter, -1);
  // 
  switch (letter) {
    case 'G':
      switch (number) {
        case 0:
          retval = CommandG0(GcodeNumber('X', FLIMIT),
                             GcodeNumber('Y', FLIMIT),
                             GcodeNumber('Z', FLIMIT),
                             GcodeNumber('U', FLIMIT),
                             GcodeNumber('V', FLIMIT),
                             GcodeNumber('W', FLIMIT),
                             GcodeNumber('T', FLIMIT));
          skip_status = true;
          break;
        case 3:
          retval = CommandG3(GcodeNumber('X', FLIMIT),
                             GcodeNumber('Y', FLIMIT),
                             GcodeNumber('Z', FLIMIT),
                             GcodeNumber('U', FLIMIT),
                             GcodeNumber('V', FLIMIT),
                             GcodeNumber('W', FLIMIT),
                             GcodeNumber('T', FLIMIT));
          break;
        case 4:
          retval = CommandG4(GcodeNumber('P', FLIMIT),
                             GcodeNumber('S', FLIMIT));
          skip_status = true;
          break;
        case 6:
          retval = CommandG6(GcodeNumber('T', 0));
          skip_status = true;
          break;
        case 28:
          retval = CommandG28();
          skip_status = true;
          break;
        case 90:
          retval = CommandG90();
          break;
        case 91:
          retval = CommandG91();
          break;
        default:
          retval = Command0();
          break;
      }
      break;
    case 'M':
      switch(number) {
        case 0:
          retval = CommandM0();
          break;
        case 15:
          retval = CommandM15();
          break;
        case 17:
          retval = CommandM17();
          break;
        case 18:
          retval = CommandM18();
          break;
        case 80:
          retval = CommandM80(GcodeNumber('S', 0));
          break;
        case 81:
          retval = CommandM81(GcodeNumber('S', 0));
          break;
        case 87:
          retval = CommandM87();
          break;
        case 89:
          retval = CommandM89();
          break;
        // case 91:
          // retval = CommandM91();
          // break;
        case 92:
          retval = CommandM92();
          break;
        case 99:
          retval = CommandM99();
          break;
        case 100:
          retval = CommandM100();
          break;
        case 111:
          retval = CommandM111();
          break;
        default:
          retval = Command0();
          break;
      }
      break;
    case 'R':
      switch(number) {
        case 0:
        default:
          CommandR0();
          return 0;
      }
      break;
    default:
      if (buffer_pointer > 2) {
        Command0();
      }
      break;
  }
  if (buffer_pointer > 2 and skip_status == false) {
    status(retval);
  }
}
