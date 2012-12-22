[BITS 16]
[ORG 0x7C00]

JMP _START

#include "../include/stage0.h"

_START:

_HALT:
	HLT
	JMP _HALT

TIMES 510 - ( $ - $$ ) DB 0

DW BIOS_SIG