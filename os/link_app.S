# os/src/link_app.S

.align 3
    .section .data
    .global _num_app
_num_app:
    .quad 3
    .quad_0_start
    .quad_1_start
    .quad_2_start
    .quad_2_end

    .section .data
    .global app_0_start
    .global app_0_end
app_0_start:
    .incbin "../user/src/bin/01store_fault.c"
app_0_end:

    .section .data
    .global app_1_start
    .global app_1_end
app_1_start:
    .incbin "../user/src/bin/02power.c"
app_1_end:

    .section .data
    .global app_2_start
    .global app_2_end
app_2_start:
    .incbin "../user/src/bin/00hello_world.c"
app_2_end:

