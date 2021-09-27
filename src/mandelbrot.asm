

section	.text
global  mandel

;============
;	[ebp+8] - X coordinate mapped as real part of a complex number in 16.16 format
;	[ebp+12]- Y coordinate mapped as imaginary part of a complex number in 16.16 format
;	ebx		- iteration counter
;	esi		- x
;	edi		- y

mandel:
	; prologue
	push 	ebp
	mov 	ebp, esp
	push 	ebx
	push 	esi
	push	edi

	xor 	esi, esi
	xor 	edi, edi
	xor 	ebx, ebx
iter_loop:
	; while (x*x + y*y ≤ 2*2 AND iteration < max_iteration) do
    ;    xtemp := x*x - y*y + x0
    ;    y := 2*x*y + y0
    ;    x := xtemp
    ;    iteration := iteration + 1

	mov		eax, esi
	imul	esi				; x*x
	shrd	eax, edx, 16
	mov		ecx, eax		; xtemp = x*x

	mov 	eax, edi
	imul	edi
	shrd	eax, edx, 16
	mov		edx, eax		; temp = y*y

	sub		ecx, edx		; xtemp = x*x - y*y
	add		ecx, [ebp+8]	; xtemp = x*x - y*y + x0

	mov		eax, esi
	imul	edi
	shrd	eax, edx, 16
	mov 	edi, eax		; y = x*y
	sal		edi, 1			; y = 2*x*y
	add		edi, [ebp+12]	; y = 2*x*y + y0

	mov 	esi, ecx		; x = xtemp

	mov		eax, esi
	imul	esi
	shrd	eax, edx, 16
	mov		ecx, eax		; = x*x

	mov		eax, edi
	imul	edi
	shrd	eax, edx, 16
	mov 	edx, eax		; y*y

	add 	ecx, edx		; = x*x + y*y

	inc		ebx				; iteration = iteration + 1

	cmp		ecx, 0x00040000	; x*x + y*y ≤ 2*2
	ja		return

	cmp		ebx, 255		; iteration < max_iteration
	jb		iter_loop

return:
	mov 	eax, ebx 		; return iteration counter

	; epilogue
	pop 	edi
	pop		esi
	pop		ebx
	pop		ebp
	ret
