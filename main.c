#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio_ext.h>

#define max_length 30
#define max_base 20

typedef struct sudents
{
	char *surname, *name, *patronymic;
	union
	{
		struct
		{
			char *father, *mother, *brother;
		} family1;
		struct
		{
			char *father, *mother, *brother, *sister;
		} family2;
		struct
		{
			char *mother, *brother, *sister;
		} family3;
	} choicefamily;
} student_t;

void check_help(int, char**);
int init_array(int, char **, student_t *);
void init_additional(int , char **, student_t *);
void stud_output(int,  student_t*, char **);

char* check_string(char*);
int atoi_change();

int main(int argc, char **argv)
{
	int array_size, arg1;
	student_t *stud;
	check_help(argc, argv);
	if(!strcmp(argv[1], "1") || !strcmp(argv[1], "2"))
	{
		stud = (student_t*)malloc(max_base*sizeof(student_t));
		if(!strcmp(argv[1], "1")) { arg1 = 0; }
		else
		{
			arg1 = 1;
			if(!(!strcmp(argv[2], "1") || !strcmp(argv[2], "2") || !strcmp(argv[2], "3")))
			{
				puts("Input command-line data is wrong. Re-run program according to next rules:\n \''-h\'' (means help), \''1\'' or \''2\'' - for first argument\n \''1\'', \''2\'' or \''3\'' - for second argument\n");
				return 0;
			}
		}
		array_size = init_array(arg1, argv, stud);
		stud_output(array_size, stud, argv);
		free(stud);
	}
	else puts("Input command-line data is wrong. Re-run program according to next rules:\n \''-h\'' (means help), \''1\'' or \''2\'' - for first argument\n \''1\'', \''2\'' or \''3\'' - for second argument\n");
	return 0;
}

int init_array(int arg1, char **argv, student_t* stud_array)
{
	int n=0, identifier;
	do
	{
		stud_array[n].surname = check_string("Enter a student's surname: ");
		stud_array[n].name = check_string("Enter a student's name: ");
		stud_array[n].patronymic = check_string("Enter a student's patronymic: ");
		if(arg1) { init_additional(n, argv, stud_array); }
		n++;
		identifier = 0;
		puts("Want to continue?");
		identifier = atoi_change();
		if(!identifier) return n;
	} while(n<max_base);
	return n;
}

void init_additional(int n, char **argv, student_t* stud_array)
{
	if(!strcmp(argv[2], "1"))
		{
			stud_array[n].choicefamily.family1.brother = check_string("Enter brother's name: ");
			stud_array[n].choicefamily.family1.father = check_string("Enter father's name: ");
			stud_array[n].choicefamily.family1.mother = check_string("Enter mother's name: ");
		}
		else if(!strcmp(argv[2], "2"))
		{
			stud_array[n].choicefamily.family2.brother = check_string("Enter brother's name: ");
			stud_array[n].choicefamily.family2.sister = check_string("Enter sister's name: ");
			stud_array[n].choicefamily.family2.father = check_string("Enter father's name: ");
			stud_array[n].choicefamily.family2.mother = check_string("Enter mother's name: ");
		}
		else
		{
			stud_array[n].choicefamily.family3.brother = check_string("Enter brother's name: ");
			stud_array[n].choicefamily.family3.sister = check_string("Enter sister's name: ");
			stud_array[n].choicefamily.family3.mother = check_string("Enter mother's name: ");
		}
}

void stud_output(int array_size, student_t* stud_array, char **argv)
{
	int n;
	puts("There is the list of students, according to input data:\n");
	do
	{
		if(!strcmp(argv[1], "2"))
		{
			if(!strcmp(argv[2], "1")) { printf("#%d - %s %s %s. Father - %s. Mother - %s. Brother - %s\n", n, stud_array[n].surname, stud_array[n].name, stud_array[n].patronymic, stud_array[n].choicefamily.family1.father, stud_array[n].choicefamily.family1.mother, stud_array[n].choicefamily.family1.brother); }
			else if(!strcmp(argv[2], "2")) { printf("#%d - %s %s %s. Father - %s. Mother - %s. Brother - %s. Sister - %s\n", n, stud_array[n].surname, stud_array[n].name, stud_array[n].patronymic, stud_array[n].choicefamily.family2.father, stud_array[n].choicefamily.family2.mother, stud_array[n].choicefamily.family2.brother, stud_array[n].choicefamily.family2.sister); }
			else { printf("#%d - %s %s %s. Mother - %s. Brother - %s. Sister - %s\n", n, stud_array[n].surname, stud_array[n].name, stud_array[n].patronymic, stud_array[n].choicefamily.family3.mother, stud_array[n].choicefamily.family3.brother, stud_array[n].choicefamily.family3.sister); }
		}
		else printf("#%d - %s %s %s\n", n, stud_array[n].surname, stud_array[n].name, stud_array[n].patronymic);
		n++;
	} while (n< array_size);
}

void check_help(int argc, char** argv)
{
	if(!strcmp(argv[1], "-h"))
    {
	puts("\n=============================================\n"
	"Manual\n\n"
	"1) Send the way of data output by command line\n"
	"2) A: Enter an information about students:\n"
	"- surname\n"
	"- name\n"
	"- patronymic\n"
	"B: Whether how it's asked to output the family members, the next data needs to be entered:\n"
	"- father\n"
	"- mother\n"
	"- brother\n"
	"- sister\n"
	"3) Output data in an interested way\n\n"
	"=================================================\n");
	exit(0);
    }
}

int atoi_change()
{
    int identifier;
    char string[128];
    while(1)
    {
	printf("(yes - 1/no - 0) ");
	fgets(string, 128, stdin);
	identifier = atoi(string);
	if(identifier == 1 || identifier == 0) { break; }
	puts("It's not correct. Please, input data again.");
    }
    return identifier;
}

char* check_string(char* comment)
{
    char *text;
    text = (char*)malloc(max_length*sizeof(char));
    do
    {
		printf("%s", comment);
		__fpurge(stdin);
        gets(text);
        if(text[0] == '\n') { continue; }
    } while (0);
    return text;
}
