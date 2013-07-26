@; Don't know how to objcopy a .bin file address-aligned => easier to use .incbin
.align 4
.globl font
font:
.incbin "font.bin"