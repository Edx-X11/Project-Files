section .data
    buffer_size equ 65536  ; Maximum size for the packet buffer

section .bss
    buffer resb buffer_size  ; Buffer to store the captured packet

section .text
    global _start

_start:
    ; Create socket
    mov rax, 41            ; syscall number for socket
    mov rdi, 2             ; AF_INET (IPv4)
    mov rsi, 1             ; SOCK_RAW (raw socket)
    mov rdx, 0             ; Protocol (0 for IP)
    syscall

    ; Check for errors
    test rax, rax
    js error               ; If negative, error occurred

    mov rdi, rax           ; Socket descriptor

capture_loop:
    ; Receive packet
    mov rax, 29            ; syscall number for recvfrom
    mov rsi, buffer        ; Buffer to store packet
    mov rdx, buffer_size   ; Buffer size
    xor r8, r8             ; Flags (0)
    mov rcx, rdi           ; Socket descriptor
    xor r9, r9             ; Sender address
    xor r10, r10           ; Sender address length
    syscall

    ; Check for errors
    test rax, rax
    js error               ; If negative, error occurred

    ; Print packet contents (example)
    mov rdi, buffer        ; Pointer to buffer
    call print_packet

    ; Continue capturing packets
    jmp capture_loop

error:
    ; Handle error
    ; You can implement error handling code here

    ; Exit program
    mov rax, 60            ; syscall number for exit
    xor rdi, rdi           ; Exit code 0
    syscall

print_packet:
    ; Example function to print packet contents
    ; Implement parsing and printing logic as needed
    ; This is just a placeholder for demonstration
    ret
