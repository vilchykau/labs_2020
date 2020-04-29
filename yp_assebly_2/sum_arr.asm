.model flat, c
.code


sum_arr proc

;.............Prologue...........
push ebp
mov ebp, esp

;................................
;n dword ptr[ebp + 12]
;a* dword ptr[ebp + 8]
mov ebx, dword ptr[ebp + 8]
xor eax, eax
mov ecx, dword ptr[ebp + 12]
ff:
	add eax, dword ptr[ebx + 4*ecx - 4]
	loop ff

;-----------Epiloge----------
pop ebp
ret
;----------------------------

sum_arr endp
end 