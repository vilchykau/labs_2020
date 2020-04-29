.686P

.MODEL FLAT, STDCALL

.STACK 4096

.DATA

MB_OK    EQU 0

STR1     DB 'Моя первая программа', 0

STR2     DB 'Привет всем!', 0

HW       DD ?

EXTERN MessageBoxA@16:NEAR

.CODE

START :

mov ax,0B800h 
mov es,ax   
mov di,0 


RET

END START