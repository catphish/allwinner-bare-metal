_reset:
cpsid if
mov sp, #0x4000
b startup

.globl _ivt
_ivt:
ldr pc, _reset_h
ldr pc, _undefined_instruction_vector_h
ldr pc, _software_interrupt_vector_h
ldr pc, _prefetch_abort_vector_h
ldr pc, _data_abort_vector_h
ldr pc, _unused_handler_h
ldr pc, _interrupt_vector_h
ldr pc, _fast_interrupt_vector_h
_reset_h:                           .word   _reset
_undefined_instruction_vector_h:    .word   _reset
_software_interrupt_vector_h:       .word   _reset
_prefetch_abort_vector_h:           .word   _reset
_data_abort_vector_h:               .word   _reset
_unused_handler_h:                  .word   _reset
_interrupt_vector_h:                .word   interrupt
_fast_interrupt_vector_h:           .word   _reset
