# CHANGELOG
x6 Mark I - Robotic Arm, Change log file

## 2017-10-29
### Added
- Detailed documentation

## 2017-06-18
### Fixed
- Command G6 was responding "ok" before end of operation.
- Command G28 was responding "ok" before end of operation.

2017-05-15
        * Improvement: Added power detection before any move command.

2017-04-30
        * New feature: Added Example directory with:
          * x1_play.gcode: Ordinary x6 Mark I interaction with x1 Mark I.
          * tea_time.gcode: x6 Mark I serving tea.

2017-03-31
        * New feature: Added G4 command

2017-03-25
        * Bug fix: Command G0 was responding "ok" before end of operation
        * Bug fix: Command G6 was responding "ok" before end of operation
        * Bug fix: Command G28 was responding "ok" before end of operation

2017-03-24
        * Bug fix: Standby timer was not reseting after any move.

2017-03-01
        * Added command
          * M0

2016-10-27
        * Added R0 command. A command to repeat last command.

2015-09-26
        * Added command_uptime.

2015-06-07
        * Added standby_handler.

2015-02-28
        * Added file config.h. Imported all pin definition and main variables.

2015-02-03
        * Changed temperature sensors from LM35 to TMP36.

2015-01-09
        * I separated the main sketch file into 2 new ones to maintain code
          clear and to grow up (handlers.ino and commands.ino).

2015-01-08
        * Added this command to wait between moves.

2015-01-05
        * Added command_demo to demonstration and mechanic test purposes.

2014-12-01
        * Added CommandG3() to set axis delay.

2014-11-24
        * Added CommandM89() with detailed SRAM information.
        
2014-11-18
        * Bug fix: command_power() was working a little bit crazy.

201x-xx-xx
        * Grow a lot...

2013-06-28
        * Experimental version.
