; x1_play.gcode, x6 Mark I - Robotic Arm, G-code example file
; This program use x6 Mark I to play and interact with x1 Mark I.
; 
; Author: Márcio Pessoa <marcio.pessoa@gmail.com>
; Contributors: none
; 
; Change log:
; 2017-06-18
;         Added some comments.
; 
; 2017-03-29
;         Code optimization.
; 
; 2017-03-27
;         Experimental version.

; Turn on and go to start position
M80  ; Turn on
G28  ; Go to start position
G0 X160 Y100 Z180 U82 V180 W145
G4 P200  ; Wait for 200 ms
G0 Y81 X157  ; Rapid move

; Turn switch on and go back
G0 U70
G0 X160 Y90 U82
G4 P200  ; Wait for 200 ms

; Keep out
G0 X170 Y100
G4 S4 P500  ; Wait for 4 seconds and a half

; Park and turn off
G28  ; Go to start position
G4 S1  ; Wait for 1 second
M81  ; Turn off
