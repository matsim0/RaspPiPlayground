.section .data
.align 4
.globl FrameBufferInfo
FrameBufferInfo:
.int 640 /* #0 Physical Width */
.int 480 /* #4 Physical Height */
.int 640 /* #8 Virtual Width */
.int 480 /* #12 Virtual Height */
.int 0 /* #16 GPU - Pitch */
.int 16 /* #20 Bit Depth */
.int 0 /* #24 X */
.int 0 /* #28 Y */
.int 0 /* #32 GPU - Pointer */
.int 0 /* #36 GPU - Size */
