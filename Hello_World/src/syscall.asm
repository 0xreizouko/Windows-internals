.data
    ssn DWORD 0
.code 
    public SetSSN
    public NtWriteFileSyscall

SetSSN proc
    mov ssn, ecx
    ret
SetSSN endp

NtWriteFileSyscall proc 
    mov r10, rcx
    mov eax, ssn
    syscall
    ret 
NtWriteFileSyscall endp

end