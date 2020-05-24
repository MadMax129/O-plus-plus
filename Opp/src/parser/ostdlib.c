#include "ostdlib.h"

void opp_init_std()
{
	// NULL Value
	env_new_int(global_ns->inside, "NULL", 0);

	if (!env_new_cfn(global_ns->inside, "echo", echo))
		internal_error("STD Fail", 2);

	if (!env_new_cfn(global_ns->inside, "print", opp_print))
		internal_error("STD Fail", 2);

	if (!env_new_cfn(global_ns->inside, "input", opp_input))
		internal_error("STD Fail", 2);
}

struct Opp_Obj* echo(struct Opp_List* args)
{
	struct Opp_Obj* obj = obj_make(OBJ_NONE);
	for (int i=0; i<args->size; i++)
	{
		struct Opp_Obj* res = opp_eval_expr(args->list[i]);
		
		switch (res->obj_type)
		{
			case OBJ_INT:
				printf("%d ", res->oint);
				break;

			case OBJ_FLOAT:
				printf("%.1lf ", res->ofloat);
				break;

			case OBJ_STR:
				printf("%s ", res->ostr);
				break;

			case OBJ_BOOL:
				printf("%d ", res->obool);
				break;
		}
	}
	printf("\n");

	return obj;
}

struct Opp_Obj* opp_print(struct Opp_List* args)
{
	struct Opp_Obj* obj = obj_make(OBJ_NONE);
	for (int i=0; i<args->size; i++)
	{
		struct Opp_Obj* res = opp_eval_expr(args->list[i]);
		switch (res->obj_type)
		{
			case OBJ_INT:
				printf("%d\n", res->oint);
				break;

			case OBJ_FLOAT:
				printf("%.3lf\n", res->ofloat);
				break;

			case OBJ_STR:
				printf("%s\n", res->ostr);
				break;

			case OBJ_BOOL:
				printf("%d\n", res->obool);
				break;
		}
	}
	return obj;
}

struct Opp_Obj* opp_input(struct Opp_List* args)
{
	struct Opp_Obj* obj = NULL;

	expect_args(0);

	char input[255] = {0};
	scanf("%s", input);

	obj = obj_make(OBJ_STR);
	obj->ostr = (char*)malloc(sizeof(input)+1);
	strcpy(obj->ostr, input);

	return obj;
}





