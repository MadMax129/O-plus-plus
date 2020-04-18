#include <stdio.h>
#include "opp.h"
#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include "./env/enviroment.h"
#include "./interpreter/interpreter.h"
#include "./parser/ostdlib.h"

static void help_menu()
{
	#ifdef UNX
		system("clear");
	#else
		system("cls");
	#endif
	printf("\n\x1b[32mO++ Programming Language\x1b[0m\n");
	printf("Written by Maks S\n");
	printf("\n\x1b[31mFormat: o++ [flag] [file]\x1b[0m\n");
	printf("-dump | For dumping file tokens\n\n\n");
}

void init_file(const char* fname, struct Opp_Scan *s)
{
	long size;

	s->file = fopen(fname, "r");
	if (!s->file)
		printf("[%s] Is not a file...\n", fname), exit(1);
	fseek(s->file, 0, SEEK_END);
	size = ftell(s->file);
	rewind(s->file);
	char *content = calloc(1, size + 2); 

	fread(content, size, 1, s->file);
	fclose(s->file);

	opp_init_lex(s, content);
}

void init_opp(const char* fname)
{
	struct Opp_Scan data = {0};
	struct Opp_Parser* parser;

	init_file(fname, &data);
	parser = opp_parse_init(&data);
	opp_init_environment();
	opp_init_std();

	opp_eval_init(parser);
}

static char* get_repl_line() 
{
	char* input = (char*)malloc(100);
	char* s = input;
	char c = 0;
	int maxlen = 100;
	int i = 0;

	printf(">> ");
	for (;;) {
		c = fgetc(stdin);

		if (c == EOF || c == '\n')
			break;
		if (i >= maxlen)
			printf("Overflow of stdin\n"), exit(1);

		input[i] = c;
		i++;
	}
	return input;
}

static void opp_init_repl()
{
	opp_init_environment();
	opp_init_std();

	for (;;) {
		struct Opp_Scan data = {0};
		struct Opp_Parser* parser = NULL;
		opp_init_lex(&data, get_repl_line());
		parser = opp_parse_init(&data);
		opp_eval_init(parser);
	}

}

int main(int argc, char** argv)
{
	if (argc == 2)
		init_opp(argv[1]);
	else {
		help_menu();
		opp_init_repl();
	}

	return 0;
} 