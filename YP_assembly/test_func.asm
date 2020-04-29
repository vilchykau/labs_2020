.model flat, c
.code


test_func proc

;.............Prologue...........
push ebp
mov ebp, esp
;................................

;Imput values:
;	f0 = ebp + 8
;	f1 = ebp + 12
;	f2 = ebp + 16
;   n = ebp + 20
;   x = ebp + 24

sub esp, 12 ; Created space for values:
			; f0_v in epb-4
			; f1_v in epb-8
			; f2_v in epb-12
push edi    ;save edi, edi we will be using for saving the sum


;-------------------calc f2_v----------------------
mov eax, [ebp+8] ; move f0 to eax
imul dword ptr [ebp+12];multiply f0(eax) by ebp+12(f1)
mov ecx, dword ptr [ebp+16]; move f2(ebp+16) to ecx
sub ecx, eax; subscract f1*f0(eax) from f2(ecx)
mov dword ptr [ebp-12], ecx; save result to f2_v
;.................................................


;------------------------calc f1_v----------------------
mov eax, dword ptr [ebp-12]; move f2_v to eax
imul dword ptr [ebp+8] ; multyply f2_v(eax) by f0(ebp+8)
mov ecx, dword ptr[ebp+12]; move f1(ebp+12) to ecx
sub ecx, eax; substract f2_v*f0(eax) from f1
mov dword ptr[ebp-8], ecx; save result to f1_v
;......................................................



;-------------------calc f2_v-------------------------
mov eax, dword ptr [ebp-12]   ; move f2_v to eax
imul dword ptr[ebp-8]         ; multiply f2_v(eax) by f1_v(ebp-8)
mov ecx, dword ptr[ebp+8]     ; move f0(ebp+8) to ecx
sub ecx, eax                  ; substract f2_v*f1_v(eax) from f0(ebp+8)
mov dword ptr[ebp-4], ecx     ; save result to f0_v
;...............................................................


mov ecx, dword ptr[ebp+20]    ; move n(ebp+20) to ecx
add ecx, 1					  ; add 1 to n(ecx)
mov eax, [ebp+24]             ; move x(ebp+24) to eax
xor edi, edi                  ; clear edi
; in edi we will be saving the sum
_loop:
	mov eax, dword ptr[ebp-12] ; move f2_v to eax
	imul dword ptr[ebp-8]      ; multiply f2_v by f1_v
	add eax, dword ptr[ebp-4]  ; add f0_v to f1_v*f2_v
	
	imul edi, [ebp+24]         ; 
	add edi, eax

	mov edx, dword ptr [ebp-8]
	mov dword ptr [ebp-4], edx

	mov edx, dword ptr [ebp-12]
	mov dword ptr [ebp-8], edx

	mov dword ptr [ebp-12], eax

	loop _loop

	
mov eax, edi

pop edi      ; return edi
;...................... Clear f0, f1, f2 ..............
add esp, 12
;---------------------------------------------------

;-----------Epiloge----------
pop ebp
ret
;----------------------------

test_func endp
end 