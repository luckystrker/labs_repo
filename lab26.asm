.INCLUDE "..\appnotes\2313def.inc" 
.DSEG
.org 0x60
arr: .byte 8
.CSEG
rjmp Reset 
Reset: 
ldi ZH,HIGH(arr_const*2)
ldi ZL,LOW(arr_const*2)
ldi r20,0x02
ldi r16, 8
clr r5

cycle:
	lpm
	sbrs r0,0
	inc r5
	adiw ZL,1
	dec r16
	cpi r16,0x00
	brne cycle
rjmp PC
	
arr_const: .db 1,1,1,0,1,1,1,0
