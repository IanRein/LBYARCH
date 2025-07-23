.code
imgCvtGrayDoubleToInt PROC
    ; RCX = src (double*)
    ; RDX = dst (uint8_t*)
    ; R8  = count (int)

    push    rbx
    xor     rbx, rbx                ; i = 0

loop_start:
    cmp     rbx, r8
    jge     loop_end

    movsd   xmm0, qword ptr [rcx + rbx*8]    ; xmm0 = src[i]
    movsd   xmm1, qword ptr [scale]          ; xmm1 = 255.0
    mulsd   xmm0, xmm1                       ; xmm0 = src[i] * 255.0
    cvttsd2si eax, xmm0                      ; eax = (int)src[i]*255.0 (truncate)
    cmp     eax, 255
    jle     no_clip
    mov     eax, 255
no_clip:
    cmp     eax, 0
    jge     store_val
    mov     eax, 0
store_val:
    mov     byte ptr [rdx + rbx], al         ; dst[i] = (uint8_t) value
    inc     rbx
    jmp     loop_start

loop_end:
    pop     rbx
    ret
imgCvtGrayDoubleToInt ENDP

scale REAL8 255.0

end
