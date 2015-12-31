#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"

typedef struct Machine {
	int AX;
	int PC;
	int main_mem[256];

} Machine;

int read_next_byte(FILE *input){
	char next_byte[3];
	int i;
	for(i=0; i < 3; i++){
		next_byte[i] = getc(input);
	}
	int tz = getc(input); // throw away the space between bytes
	if (tz == EOF){ // return -1 if we hit the end of the file
		return -1;
	}	
	return atoi(next_byte);
}

void init(Machine *mz) {
	mz->PC = 0;
}
int next_instruction(Machine *mz) {
	int instr = mz->main_mem[mz->PC];
	mz->PC++;
	return instr;
}

void load(Machine *mz, int val) {
	mz->AX = val;
}
void loadi(Machine *mz, int addr) {
	mz->AX = mz->main_mem[addr];
}

void store(Machine *mz, int addr) {
	mz->main_mem[addr] = mz->AX;
}
void add(Machine *mz, int val) {
	mz->AX+=val;
}
void jump(Machine *mz, int addr) {
	mz->PC = addr;
}
void output(Machine *mz) {
	printf("%d\n", mz->AX);
}

void load_instructions(Machine *mz, FILE *instructions) {
	int op_code;
	int i = 0;
	while (op_code !=-1){
		op_code = read_next_byte(instructions);
		if (op_code != -1){
			mz->main_mem[i] = op_code;
			i++;
		}
	}
}

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

			case STORE: ;
				arg = next_instruction(&m);
				store(&m, arg);
				break;

			case ADD: ;
				arg = next_instruction(&m);
				add(&m, arg);
				break;

			case JUMP: ;
				arg = next_instruction(&m);
				jump(&m, arg);
				break;
			
			case OUTPUT: ;
				output(&m);
				break;
		}
	}	

	return 0;
}
