.INCLUDE "..\appnotes\2313def.inc" ;??????????? ????? ??
;????????????? ????????? ?????/??????
.CSEG ;??????? ????
rjmp Reset ;?????? ??????????, ??????????? ?? ?????? ????????????????
Reset: ;?????? ?????????
;r1 ???????? ????????????? ?????
ldi r20, 0x13
ldi r16,8 ;??????? ?????
clr r0 ;??????? ????? ?????? ? r1
 loop:
 sbrs r20,0
 inc r0 ;????????? r0, ???? ??? 0 r1 ????? ???????
 lsr r20 ;?????????? ????? r1 ?? ???? ??? ??????
 dec r16
 cpi r16,0x00
 brne loop
rjmp PC ;??????????? ????

