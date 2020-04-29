.model flat
.code


@sum_fast_call@8 PROC

push ebp
mov ebp, esp

push ecx
push edx

xor eax, eax
ff:
	add eax, dword ptr[edx + 4*ecx - 4]
	loop ff

pop edx
pop ecx

;-----------Epiloge----------
pop ebp
ret
;---

@sum_fast_call@8  ENDP
end