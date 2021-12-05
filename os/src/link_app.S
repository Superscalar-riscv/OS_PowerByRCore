# os/src/link_app.S

.align 3
    .section .data
    .global _num_app
_num_app:
    .quad 3
    .quad app_0_start
    .quad app_1_start
    .quad app_2_start
    .quad app_2_end

    .section .data
    .global app_0_start
    .global app_0_end
app_0_start:
    .incbin "/home/asker/rCore/OS_PowerByRCore/user/build/00hello_world-riscv64.bin"
app_0_end:

    .section .data
    .global app_1_start
    .global app_1_end
app_1_start:
    .incbin "/home/asker/rCore/OS_PowerByRCore/user/build/01store_fault-riscv64.bin"
app_1_end:

    .section .data
    .global app_2_start
    .global app_2_end
app_2_start:
    .incbin "/home/asker/rCore/OS_PowerByRCore/user/build/02power-riscv64.bin"
app_2_end:

