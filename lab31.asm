.INCLUDE "..\appnotes\2313def.inc" ;??????????? ????? ??
;????????????? ????????? ?????/??????
.CSEG ;??????? ????
rjmp Reset ;?????? ??????????, ??????????? ?? ?????? ????????????????
Reset: ;?????? ?????????
ldi r20,0xAF;r1 ???????? ????????????? ?????
ldi ZH,HIGH(num_of_ones*2) ;????????? Z ?????????????????? ?????????
ldi ZL,LOW(num_of_ones*2) ;?????? ?????? ??????? ???????? num_of_ones
 clr r2
 ldi r17,0x0F
 and r17,r20 ;??????? ??????? ?????????????? ?????
 ld r21, Z
 add ZL,r17 ;?????????? ?????? ?????????? ???????? ???????
 adc ZL,r2 ;

lpm ;??????????? ? r0 ??????????? ?????? Flash, ??
;??????? ????????? Z]
mov r15,r0
swap r20

 clr r2
 ldi ZH,HIGH(num_of_ones*2) ;????????? Z ?????????????????? ?????????
 ldi ZL,LOW(num_of_ones*2)
 ldi r17,0x0F
 and r17,r20 ;??????? ??????? ?????????????? ?????
 add ZL,r17 ;?????????? ?????? ?????????? ???????? ???????
 adc ZL,r2 ;
lpm
add r15,r0


rjmp PC ;??????????? ????
;??????? ???????? ????? ?????? ? ???????? ????????????? ????? ?? 0 ?? 15
num_of_ones:
.DB 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
