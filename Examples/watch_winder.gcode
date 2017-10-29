; watch_winder.gcode, x6 Mark I - Robotic Arm, G-code example file
; This program use x6 Mark I to wind an automatic watch.
; 
; Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
; Contributors: none
; 
; Change log:
; 2017-07-21
;         Experimental version.

; Turn on and go to start position
M80  ; Turn on
G28  ; Go to start position

G0 Y90 V90
G4 P1200  ; Wait for 1200 milliseconds

G0 U0 W0
G4 P1200  ; Wait for 1200 milliseconds

G0 U155 W160
G4 P1200  ; Wait for 1200 milliseconds

G0 U82 W75
G4 P1200  ; Wait for 1200 milliseconds

G0 Z170
G4 P1200  ; Wait for 1200 milliseconds

G0 U0 W0
G4 P1200  ; Wait for 1200 milliseconds

G0 U155 W160
G4 P1200  ; Wait for 1200 milliseconds

G0 U82 W75
G0 Z0
G4 P1200  ; Wait for 1200 milliseconds

; Go home and shutdown
G28  ; Go to start position
G4 S1  ; Wait for 1 second
M81  ; Turn off
