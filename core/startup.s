
.syntax unified
.cpu cortex-m7
.thumb

.global _estack
.global Reset_Handler

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object

g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler

Reset_Handler:
    bl SystemInit
    bl main
    b .

Default_Handler:
    b .

SystemInit:
    bx lr
