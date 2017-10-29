; tea_time.gcode, x6 Mark I - Robotic Arm, G-code example file
; This program use x6 Mark I to make a tea.
; 
; Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
; Contributors: none
; 
; Change log:
; 2017-06-18
;         Added some comments.
; 
; 2017-04-19
;         Added "Please like and follow" message.
;
; 2017-03-30
;         Experimental version.

; Turn on and go to start position
M80  ; Turn on
G28  ; Go to start position
G3 X20 Y18 Z10 U12 V10 W8 T2
G0 X30 Y120 Z10 V150
G3 X20 Y20 Z12 U12 V10 W8 T2

; Put in and Put out tea bag
G0 V80
G4 S3 P100  ; Wait for 3 seconds and 100 milliseconds
G0 V120
G4 P100  ; Wait for 100 ms
G0 V80
G4 S3 P100
G0 V120
G4 P100
G0 V80
G4 S3 P100  ; Wait for 3 seconds and 100 milliseconds
G0 V120
G4 P100  ; Wait for 100 ms
G0 V80
G4 S3 P100  ; Wait for 3 seconds and 100 milliseconds
G0 V120
G4 P100  ; Wait for 100 ms

; Drop down tea bag
G0 X60
G0 U155 V90 W160
G4 P400  ; Wait for 400 ms

; Lets serve the tea
G0 X30 Y120 Z10 V0 W75 U82
G0 Y150 Z10 V20
G3 Y40 Z30 V30
G0 Y180 Z40 V90
G3 X20 Y20 Z12 U12 V10 W8 T2  ; Set axis delay
G0 Y140 Z50 V20

; Please like and follow
G0 X0 Z80 Y180 V90
G0 V30 U45
G0 V0

; Go home and shutdown
G28  ; Go to start position
G4 S1  ; Wait for 1 second
M81  ; Turn off
