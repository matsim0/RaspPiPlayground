.section .init
.globl _start
_start:
b startup

.section .text
startup:
mov sp, #0x8000
bl main

