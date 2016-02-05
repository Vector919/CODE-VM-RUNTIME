#include <stdlib.h>
#include <stdio.h>

#include "machine.h"

#define ERROR_NEWLINE -2

int read_next_byte(FILE *input){
	char next_byte[4];
	int i;
	char next_c;
	for(i=0; i<3; i++){
		next_c = getc(input);
		if (next_c == EOF){
			return EOF;
		}
		if (next_c == '\n'){
			return ERROR_NEWLINE;
		}
		next_byte[i] = next_c;
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
void subtract(Machine *mz, int val) {
	mz->AX-=val;
}
void jump(Machine *mz, int addr) {
	mz->PC = addr;
}
void jump_if_zero(Machine *mz, int addr) {
	if (mz->AX == 0) {
		jump(mz, addr);
	}
}
void jump_if_not_zero(Machine *mz, int addr) {
	if (mz->AX != 0){
		jump(mz, addr);
	}
}
void output(Machine *mz) {
	printf("%d\n", mz->AX);
}

void load_instructions(Machine *mz, FILE *instructions) {
	int op_code;
	int i = 0;
	while (op_code !=-1){
		op_code = read_next_byte(instructions);
		if (op_code != -1 && op_code != ERROR_NEWLINE){
			mz->main_mem[i] = op_code;
			i++;
		}
	}
}
