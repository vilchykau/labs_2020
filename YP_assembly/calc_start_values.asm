.model flat, c
.code


calc_stat_values proc

; f2 = ebp+16
; f1 = ebp+12
; f0 = ebp+8


mov eax, [ebp+8] ; move f0 to eax
imul dword ptr [ebp+12];multiply f0(eax) by ebp+12(f1)
mov ecx, dword ptr [ebp+16]; move f2(ebp+16) to ecx
sub ecx, eax; subscract f1*f0(eax) from f2(ecx)
mov dword ptr [ebp+16], ecx; save result to f2


;------------------------calc f1_v----------------------
mov eax, dword ptr [ebp+16]; move f2_v to eax
imul dword ptr [ebp+8] ; multyply f2_v(eax) by f0(ebp+8)
mov ecx, dword ptr[ebp+12]; move f1(ebp+12) to ecx
sub ecx, eax; substract f2_v*f0(eax) from f1
mov dword ptr[ebp+12], ecx; save result to f1
;......................................................

mov eax, dword ptr [ebp+16]   ; move f2_v to eax
imul dword ptr[ebp+12]         ; multiply f2_v(eax) by f1_v(ebp-8)
mov ecx, dword ptr[ebp+8]     ; move f0(ebp+8) to ecx
sub ecx, eax                  ; substract f2_v*f1_v(eax) from f0(ebp+8)
mov dword ptr[ebp+8], ecx     ; save result to f0_v
;...............................................................


calc_stat_values endp
end