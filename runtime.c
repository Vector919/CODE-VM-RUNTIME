#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"
#include "machine.h"

int main(int argc, char *argv[]) {
	
	// initalize the machine
	FILE *input_asm = fopen(argv[1], "r+");
	Machine m;
	load_instructions(&m, input_asm);
	init(&m);

	int OPCODE;
	int arg;

	while (OPCODE != HALT){
		OPCODE = next_instruction(&m);
		switch(OPCODE){
			case LOAD: ;
				arg = next_instruction(&m);
				load(&m, arg);
				break;

			case LOADI: ;
				arg = next_instruction(&m);
				loadi(&m, arg);
				break;

			case STORE: ;
				arg = next_instruction(&m);
				store(&m, arg);
				break;

			case ADD: ;
				arg = next_instruction(&m);
				add(&m, arg);
				break;

			case SUB: ;
				arg = next_instruction(&m);
				subtract(&m, arg);
				break;

			case JUMP: ;
				arg = next_instruction(&m);
				jump(&m, arg);
				break;
			case JMPZ: ;
				arg = next_instruction(&m);
				jump_if_zero(&m, arg);
			case JNZ: ;
				arg = next_instruction(&m);
				jump_if_not_zero(&m, arg);
			
			case OUTPUT: ;
				output(&m);
				break;
		}
	}	

	return 0;
}
