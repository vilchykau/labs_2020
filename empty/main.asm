.686P

.MODEL FLAT, STDCALL

.STACK 4096

.DATA

MB_OK    EQU 0

STR1     DB '��� ������ ���������', 0

STR2     DB '������ ����!', 0

HW       DD ?

EXTERN MessageBoxA@16:NEAR

.CODE

START :

mov ax,0B800h 
mov es,ax   
mov di,0 


RET

END START