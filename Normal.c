#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <math.h>
int main()
{
	int retry;

	if ((checkfiles()) == 1)
	{
		printf("Error!\n");
		system("pause");
	}
	do
	{
		system("cls");
		printf("Good day, Boss!\nDo you want to start working?\n1 - Yes\n2 - No\nChoose, Sir: ");
		retry = getchar() - '0';
		scanf("%*[^\n]%*c%");
		getchar();
		switch (retry)
		{
		case 1:
		{
			choosemode();
			break;
		}
		case 2:
		{
			printf("Goodbye, i'll miss you...\n");
			deltrash();
			return 0;
		}
		default:
		{
			printf("Wrong format. Press button to retry\n");
			getchar();
			break;
		}
		}
	} while (retry != 2);
	deltrash();
	return 0;
}
int choosemode()
{
	char mode;
	char s[100];

	do
	{
		system("cls");
		printf("Choose Mode: \n1 - Add to base\n2 - Read from base\n3 - Recreate Base\n4 - Delete Base\n5 - Exit\nEnter mode code: ");
		mode = getchar() - '0';
		scanf("%*[^\n]%*c");
		getchar();
		switch (mode)
		{
		case 1:
		{
			entinbase();
			break;
		}
		case 2:
		{
			readmode();
			break;
		}
		case 3:
		{
			SysMenu();
			break;
		}
		case 4:
		{
			DelBase();
			break;
		}
		case 5:
		{
			system("cls");
			return 0;
		}
		default:
		{
			printf("Wrong format. Press button to retry\n");
			getchar();
			break;
		}
		}
	} while (mode != 5);
	return 0;
}
int entinbase ()
{
	char s1[100];
	int res, Limit;
	long int N;
	FILE *f1, *f2, *cfg;
	struct date
	{
		int month;
		int day;
		int code;
	} date;

	system("cls");
	f1 = fopen("file.txt", "r+");
	f2 = fopen("file1.txt", "w+");
	cfg = fopen("cfg.txt", "r+");
	res = 0;
	fscanf(cfg, "Limit: %d\n", &Limit);

	while (res == 0)
	{
		printf("Enter the month or exit. For exit enter 13: ");
		scanf("%d", &date.month);
		getchar();
		while ((date.month < 1) || (date.month > 13))
		{
			system("cls");
			printf("Invalid Format. Please, retry. \nEnter the month or exit. For exit enter 13: ");
			scanf("%d", &date.month);
			getchar();
		}
		system("cls");
		if (date.month == 13)
		{
			fclose(f1);
			fclose(f2);
			fclose(cfg);
			return 0;
		}
		printf("Enter the day or exit. For exit enter 32: ");
		scanf("%d", &date.day);
		getchar();
		while ((date.day < 1) || (date.day > 32))
		{
			system("cls");
			printf("Invalid Format. Please, retry. \nEnter the day or exit. For exit enter 32: ");
			scanf("%d", &date.day);
			getchar();
		}
		system("cls");
		if (date.day == 32)
		{
			fclose(f1);
			fclose(f2);
			fclose(cfg);
			return 0;
		}
		printf("Choose the type or exit:\n1 - Birthday\n2 - Hollyday\n3 - Important Day\nEnter the code or exit. For exit enter 4: ");
		scanf("%d", &date.code);
		getchar();
		while ((date.code < 1) || (date.code > 4))
		{
			system("cls");
			printf("Invalid Format. Please, retry. \nChoose the type or exit:\n1 - Birthday\n2 - Hollyday\n3 - Important Day\nEnter the code or exit. For exit enter 4: ");
			scanf("%d", &date.code);
			getchar();
		}
		system("cls");
		if (date.code == 4)
		{
			fclose(f1);
			fclose(f2);
			fclose(cfg);
			return 0;
		}
		printf("Enter the name or exit. For exit enter 1: ");
		fgets(s1, 100, stdin);
		if (s1[0] == '1')
		{
			fclose(f1);
			fclose(f2);
			fclose(cfg);
			return 0;
		}
		N = (date.month * 1000) + (date.day * 10) + date.code;
		res = testnalimit(0, 0, N, Limit);
	}
	if (N > Limit)
		changecfg(cfg, N);
	
	fscanf(cfg, "Limit: %d\n", &Limit);

	vvodid(f1, f2, 0, Limit, 0, N, s1);

	fclose(f1);
	fclose(f2);
	fclose(cfg);
	remove("file.txt");
	rename("file1.txt", "file.txt");
	system("cls");

	return 0;
}
int vvodid(FILE *f1, FILE *f2, int i, int Limit, int previousI, long int N, char s1[1000])
{
	char s[100];
	int chislo[5];
	int krat;
	char type[100];
	int j;
	struct date
	{
		int month;
		int day;
		int code;
	} date;

	do
	{
		fscanf(f1, "%d ", &i);
		fgets(s, 100, f1);
		if ((previousI <= N) && (N < i))
		{
			fprintf(f2, "%d %s", N, s1);
		}
		fprintf(f2, "%d %s", i, s);
		previousI = i;
	} while (i < Limit);
	if (N > Limit)
	{
		fseek(f1, 0, SEEK_END);
		fprintf(f2, "%d %s", N, s1);
	}

	krat = 10000;
	i = 0;
	for (j = 0; j != 5; j++)
	{
		chislo[i] = N / krat;
		N = N - chislo[i] * krat;
		krat = krat / 10;
		i++;
	}

	date.month = chislo[0] * 10 + chislo[1];
	date.day = chislo[2] * 10 + chislo[3];
	date.code = chislo[4];

	switch (date.code)
	{
	case 1:
	{
		strcpy(type, "Birthday");
		break;
	}
	case 2:
	{
		strcpy(type, "Hollyday");
		break;
	}
	case 3:
	{
		strcpy(type, "Important Day");
		break;
	}
	}
	system("cls");
	printf("New Event added: %d.%d - %s - %s\n", date.day, date.month, type, s1);
	system("pause");
	return 0;

}
int testnalimit(int PreviousI, int i, long int N, int Limit)
{

	FILE *list, *list1;
	int number;
	list = fopen("listofnumbers.txt", "r+");
	list1 = fopen("listofnumbers1.txt", "w+");
	do
	{
		fscanf(list, "%d\n", &number);
		if (N == number)
		{
			printf("Sorry, this id is already in use, try again\n");
			return 0;
		}

	} while (number < Limit);
	fseek(list, 0, SEEK_SET);
	do
	{
		fscanf(list, "%d", &i);
		if ((PreviousI < N) && (N < i))
		{
			fprintf(list1, "%d\n", N);
		}
		fprintf(list1, "%d \n", i);
		PreviousI = i;
	} while (i < Limit);
	if (N > Limit)
		fprintf(list1, "%d\n", N);
	fclose(list);
	fclose(list1);
	remove("listofnumbers.txt");
	rename("listofnumbers1.txt", "listofnumbers.txt");
	return 1;
}
int changecfg(FILE *cfg, int num)
{
	FILE *cfg1;
	cfg1 = fopen("cfg1.txt", "w+");
	fprintf(cfg1, "Limit: %d\n", num);
	fclose(cfg);
	fclose(cfg1);
	remove("cfg.txt");
	rename("cfg1.txt", "cfg.txt");
	return 0;
}
int readmode ()
{
	char mode;
	do
	{
		system("cls");
		printf("Choose mode:\n1 - One Event\n2 - Whole month\n3 - One category\n4 - Exit\nEnter mode code: ");
		mode = getchar() - '0';
		scanf("%*[^\n]%*c");
		getchar();
		switch (mode)
		{
		case 1:
		{
			readonedate();
			return 0;
		}
		case 2:
		{
			readmonth();
			return 0;
		}
		case 3:
		{
			readcat();
			return 0;
		}
		case 4:
		{
			return 0;
		}
		default:
		{
			printf("Wrong format. Press button to retry\n");
			getchar();
			break;
		}
		}
	} while (mode != 3);
	
}
int readmonth()
{
	FILE *f1;
	struct dates
	{
		int month;
		int day;
		int code;
		char type[100];
	};
	struct founded
	{
		int trig;
		long int number;
		char string[100];
	};

	struct dates date[33];
	struct founded found[33];
	int N, resN, i, j, k,q, cont, month;
	long int g;
	int chislo[5];
	int krat;
	char str[100];

	q = 0;
	f1 = fopen("file.txt", "r+");
	system("cls");
	printf("Enter the month or exit. For exit enter 13: ");
	scanf("%d", &month);
	while ((month < 1) || (month > 13))
	{
		system("cls");
		printf("Invalid Format. Please, retry. \nEnter the month or exit. For exit enter 13: ");
		scanf("%d", &month);
		getchar();
	}
	system("cls");
	getchar();
	if (month == 13)
		return 0;

	
	N = (month * 1000);
	resN = N + 1000;
	i = N;
	j = 0;
	while ((i < resN) && (feof(f1) == 0))
	{
		fscanf(f1, "%d ", &g);
		fgets(str, 100, f1);
		found[j].trig = 0;
		if ((g > i) && (g <= resN))
		{
			found[j].number = g;
			strcpy(found[j].string, str);
			found[j].trig = 1;
			j++;
			i = g;
			q++;
		}
		
	}
	fclose(f1);
	if (q == 0)
	{
		printf("Information not found. Please touch any key to exit and retry\n ");
		system("pause");
		return 0;
	}

	k = 0;

	while (found[k].trig != 0)
	{
		krat = 10000;
		i = 0;
		for (cont = 0; cont != 5; cont++)
		{
			chislo[i] = found[k].number / krat;
			found[k].number = found[k].number - chislo[i] * krat;
			krat = krat / 10;
			i++;
		}
		date[k].month = chislo[0] * 10 + chislo[1];
		date[k].day = chislo[2] * 10 + chislo[3];
		date[k].code = chislo[4];
		switch (date[k].code)
		{
		case 1:
		{
			strcpy(date[k].type, "Birthday");
			break;
		}
		case 2:
		{
			strcpy(date[k].type, "Hollyday");
			break;
		}
		case 3:
		{
			strcpy(date[k].type, "Important Day");
			break;
		}
		}
		printf("%d.%d - %s - %s\n", date[k].day, date[k].month, date[k].type, found[k].string);
		k++;
	}	 
	system("pause");
	return 0;
}
int readonedate()
{
	FILE *cfg, *f1;
	struct date
	{
		int month;
		int day;
		int code;
	} date;

	int reply, N, resN, i, j, Limit;
	int chislo[5];
	int krat;
	char str[100];
	char type[100];

	f1 = fopen("file.txt", "r+");
	cfg = fopen("cfg.txt", "r+");
	fscanf(cfg, "Limit: %d\n", &Limit);
	system("cls");
	printf("Enter the month or exit. For exit enter 13: ");
	scanf("%d", &date.month);
	getchar();
	while ((date.month < 1) || (date.month > 13))
	{
		system("cls");
		printf("Invalid Format. Please, retry. \nEnter the month or exit. For exit enter 13: ");
		scanf("%d", &date.month);
		getchar();
	}
	system("cls");
	if (date.month == 13)
		return 0;
	printf("Enter the day or exit. For exit enter 32: ");
	scanf("%d", &date.day);
	getchar();
	while ((date.day < 1) || (date.day > 32))
	{
		system("cls");
		printf("Invalid Format. Please, retry. \nEnter the day or exit. For exit enter 32: ");
		scanf("%d", &date.day);
		getchar();
	}
	system("cls");
	if (date.day == 32)
		return 0;
	printf("Choose the type or exit:\n1 - Birthday\n2 - Hollyday\n3 - Important Day\nEnter the code or exit. For exit enter 4: ");
	scanf("%d", &date.code);
	getchar();
	while ((date.code < 1) || (date.code > 4))
	{
		system("cls");
		printf("Invalid Format. Please, retry. \nChoose the type or exit:\n1 - Birthday\n2 - Hollyday\n3 - Important Day\nEnter the code or exit. For exit enter 4: ");
		scanf("%d", &date.code);
		getchar();
	}
	system("cls");
	if (date.code == 4)
		return 0;
	N = (date.month * 1000) + (date.day * 10) + date.code;
	i = 0;
	resN = N;
	while ((N != i) && (i != Limit))
	{
		fscanf(f1, "%d ", &i);
		fgets(str, 100, f1);
	}
	if (i != N)
	{
		printf("Information not found. Please touch any key to exit and retry\n ");
		system("pause");
		getchar();
		return 0;
	}
	krat = 10000;
	i = 0;
	for (j = 0; j != 5; j++)
	{
		chislo[i] = N / krat;
		N = N - chislo[i] * krat;
		krat = krat / 10;
		i++;
	}

	date.month = chislo[0] * 10 + chislo[1];
	date.day = chislo[2] * 10 + chislo[3];
	date.code = chislo[4];
	fclose(f1);
	fclose(cfg);
	switch (date.code)
	{
	case 1:
	{
		strcpy(type, "Birthday");
		break;
	}
	case 2:
	{
		strcpy(type, "Hollyday");
		break;
	}
	case 3:
	{
		strcpy(type, "Important Day");
		break;
	}
	}

	system("cls");
	printf("Information was found\n");
	printf("%d.%d - %s - %s\n", date.day, date.month, type, str);
	delored(resN, date.day, date.month, type, str);
	return 0;
}
int readcat()
{
	FILE *f1;
	FILE *cfg;
	struct dates
	{
		int month;
		int day;
		int code;
		char type[100];
	};
	struct founded
	{
		int trig;
		long int number;
		char string[100];
	};

	struct dates date[33];
	struct founded found[33];
	int N, resN, i, j, k, q, cont, code, Limit;
	long int g;
	int chislo[5];
	int krat;
	char str[100];

	q = 0;
	f1 = fopen("file.txt", "r+");
	cfg = fopen("cfg.txt", "r+");
	cfg = fopen("cfg.txt", "r+");
	fscanf(cfg, "Limit: %d\n", &Limit);
	fclose(cfg);
	system("cls");
	printf("Enter the category or exit. \n1 - Birhtday\n2 - Hollyday\n3 - Important day\nFor exit enter 4: ");
	scanf("%d", &code);
	while ((code < 1) || (code > 4))
	{
		system("cls");
		printf("Invalid Format. Please, retry. \nEnter the category or exit. \n1 - Birhtday\n2 - Hollyday\n3 - Important day\nFor exit enter 4: ");
		scanf("%d", &code);
		getchar();
	}
	system("cls");
	getchar();
	if (code == 4)
		return 0;

	resN = Limit;
	i = code;
	j = 0;
	do
	{
		fscanf(f1, "%d ", &g);
		fgets(str, 100, f1);
		found[j].trig = 0;
		if ((g%10 == code) && (g <= resN))
		{
			found[j].number = g;
			strcpy(found[j].string, str);
			found[j].trig = 1;
			j++;
			i = g;
			q++;
		}

	} while ((i < resN) && (feof(f1) == 0));
	fclose(f1);
	if (q == 0)
	{
		printf("Information not found. Please touch any key to exit and retry\n ");
		system("pause");
		return 0;
	}

	k = 0;

	while (found[k].trig > 0)
	{
		krat = 10000;
		i = 0;
		for (cont = 0; cont != 5; cont++)
		{
			chislo[i] = found[k].number / krat;
			found[k].number = found[k].number - chislo[i] * krat;
			krat = krat / 10;
			i++;
		}
		date[k].month = chislo[0] * 10 + chislo[1];
		date[k].day = chislo[2] * 10 + chislo[3];
		date[k].code = chislo[4];
		switch (date[k].code)
		{
		case 1:
		{
			strcpy(date[k].type, "Birthday");
			break;
		}
		case 2:
		{
			strcpy(date[k].type, "Hollyday");
			break;
		}
		case 3:
		{
			strcpy(date[k].type, "Important Day");
			break;
		}
		}
		printf("%d.%d - %s - %s\n", date[k].day, date[k].month, date[k].type, found[k].string);
		k++;
	}
	system("pause");
	return 0;
}
int delored(long int resN, int day, int month, char type[100], char str[100])
{
	int mode, N;
	mode = 0;
	N = resN;	
	printf("What do you want to do?\n1 - Delete this event\n2 - Edit this event\n3 - Exit\nChoose action: ");
	scanf("%d", &mode);
	while ((mode < 1) || (mode > 3))
	{
		system("cls");
		printf("Invalid Format. Please, retry. \n What do you want to do?\n1 - Delete this event\n2 - Edit this event\n3 - Exit\nChoose action: ");
		scanf("%d", &mode);
		getchar();
	}
	getchar();
	switch (mode)
	{
	case 1:
	{
		delstroke(N);
		return 0;
	}
	case 2:
	{
		editstroke(N, day, month, type, str);
		return 0;
	}
	case 3:
		return 0;
	}
	return 0;
}
int delstroke(long int resN)
{
	FILE *f1, *f2, *cfg, *list1, *list2;
	int Limit, i, lastI;
	char s[100];
	system("cls");
	f1 = fopen("file.txt", "r+");
	f2 = fopen("file1.txt", "w+");
	list1 = fopen("listofnumbers.txt", "r+");
	list2 = fopen("listofnumbers1.txt", "w+");
	cfg = fopen("cfg.txt", "r+");
	fscanf(cfg, "Limit: %d\n", &Limit);
	fscanf(f1, "%d ", &i);
	fgets(s, 100, f1);

	while (i != resN)
	{
		fprintf(f2, "%d %s", i, s);
		fprintf(list2, "%d\n", i);
		lastI = i;
		fscanf(f1, "%d ", &i);
		fgets(s, 100, f1);
	}
	fscanf(f1, "%d ", &i);
	fgets(s, 100, f1);

	if (resN == Limit)
	{
		fclose(cfg);
		cfg = fopen("cfg.txt", "w+");
		fprintf(cfg, "Limit: %d", lastI);
		printf("Delete was sucsesful");
		fclose(f1);
		fclose(f2);
		fclose(cfg);
		fclose(list1);
		fclose(list2);
		remove("listofnumbers.txt");
		rename("listofnumbers1.txt", "listofnumbers.txt");
		remove("file.txt");
		rename("file1.txt", "file.txt");
		return 0;
	}
	fprintf(f2, "%d %s", i, s);
	fprintf(list2, "%d\n", i);
	do
	{
		fscanf(f1, "%d ", &i);
		fgets(s, 100, f1);
		fprintf(f2, "%d %s", i, s);
		fprintf(list2, "%d\n", i);
	} while (i < Limit);
;
	fclose(f1);
	fclose(f2);
	fclose(cfg);
	fclose(list1);
	fclose(list2);
	remove("listofnumbers.txt");
	rename("listofnumbers1.txt", "listofnumbers.txt");
	remove("file.txt");
	rename("file1.txt", "file.txt");
	return 0;
}
int editstroke(long int resN, int day, int month, char type[100], char str[100])
{
	int mode;
	system("cls");
	printf("Remember date and Event: %d.%d - %s - %s\n", day, month, type, str);
	delstroke(resN);
	printf("What do you want to edit?\n1 - Date\n2 - Name of date\nChoose action: ");
	scanf("%d", &mode);
	getchar();
	switch (mode)
	{
	case 1:
	{
		newstroke(str, 0);
		break;
	}
	case 2:
	{
		newstroke(0, resN);
		break;
	}
	}
	return 0;
}
int newstroke(char s1[100], long int dateN)
{
	struct date
	{
		int month;
		int day;
		int code;
	} date;
	char str[100];
	int N, code;
	int Limit;
	long int N1;
	FILE *f1, *f2, *cfg;
	f1 = fopen("file.txt", "r+");
	f2 = fopen("file1.txt", "w+");
	cfg = fopen("cfg.txt", "r+");
	fscanf(cfg, "Limit: %d\n", &Limit);
	if (s1 != NULL)
		strcpy(str, s1);
	if (dateN == 0)
	{
		printf("Enter the month or exit. For exit enter 13: ");
		scanf("%d", &date.month);
		getchar();
		while ((date.month < 1) || (date.month > 13))
		{
			system("cls");
			printf("Invalid Format. Please, retry. \nEnter the month or exit. For exit enter 13: ");
			scanf("%d", &date.month);
			getchar();
		}
		system("cls");
		if (date.month == 13)
			return 0;
		printf("Enter the day or exit. For exit enter 32: ");
		scanf("%d", &date.day);
		getchar();
		while ((date.day < 1) || (date.day > 32))
		{
			system("cls");
			printf("Invalid Format. Please, retry. \nEnter the day or exit. For exit enter 32: ");
			scanf("%d", &date.day);
			getchar();
		}
		system("cls");
		if (date.day == 32)
			return 0;
		printf("Choose the type or exit:\n1 - Birthday\n2 - Hollyday\n3 - Important Day\nEnter the code or exit. For exit enter 4: ");
		scanf("%d", &date.code);
		getchar();
		while ((date.code < 1) || (date.code > 4))
		{
			system("cls");
			printf("Invalid Format. Please, retry. \nChoose the type or exit:\n1 - Birthday\n2 - Hollyday\n3 - Important Day\nEnter the code or exit. For exit enter 4: ");
			scanf("%d", &date.code);
			getchar();
		}
		system("cls");
		if (date.code == 4)
			return 0;
		N1 = (date.month * 1000) + (date.day * 10) + date.code;
	}
	if (s1 == NULL)
	{
		printf("Enter new name: ");
		fgets(str, 100, stdin);
		N1 = dateN;

	}
	rednumb(0, 0, N1, Limit);
	vvodid(f1, f2, 0, Limit, 0, N1, str);
	if (N1 > Limit)
		changecfg(cfg, N1);
	fclose(f1);
	fclose(f2);
	remove("file.txt");
	rename("file1.txt", "file.txt");
	return 0;
}
int rednumb(int PreviousI, int i, long int N, int Limit)
{

	FILE *list, *list1;
	int number;
	list = fopen("listofnumbers.txt", "r+");
	list1 = fopen("listofnumbers1.txt", "w+");
	do
	{
		fscanf(list, "%d\n", &number);
		if (N == number)
		{
			printf("Sorry, this id is already in use, try again\n");
			return 0;
		}

	} while (number < Limit);
	fseek(list, 0, SEEK_SET);
	do
	{
		fscanf(list, "%d", &i);
		if ((PreviousI < N) && (N < i))
		{
			fprintf(list1, "%d\n", N);
		}
		fprintf(list1, "%d \n", i);
		PreviousI = i;
	} while (i < Limit);
	if (N > Limit)
		fprintf(list1, "%d\n", N);
	fclose(list);
	fclose(list1);
	remove("listofnumbers.txt");
	rename("listofnumbers1.txt", "listofnumbers.txt");
	return 1;
} 
int checkfiles()
{
	FILE *base, *numb, *cfg;
	int ans;
	
	ans = 0;

	if ((base = fopen("file.txt", "r")) == NULL)
	{
		printf("Base file of Main Base was broken. PLS, call admin and don't touch anything\n");
		ans++;
	}

	if ((numb = fopen("listofnumbers.txt", "r")) == NULL)
	{
		printf("Base file of Numbers was broken. PLS, call admin and don't touch anything\n");
		ans++;
	}

	if ((cfg = fopen("cfg.txt", "r")) == NULL)
	{
		printf("Base file of Config was broken. PLS, call admin and don't touch anything\n");
		ans++;
	}


	switch (ans)
	{
	case 0: 
	{
		fclose(cfg);
		fclose(base);
		fclose(numb);
		return 0;
	}
	default: return 1;
	}

	return 1;
}
int SysMenu()
{
	int retry;
	retry = 0;

	do
	{
		system("cls");
		printf("Do you want to recreate base?\n1 - Yes\n2 - No\nEnter action code: ");
		retry = getchar() - '0';
		scanf("%*[^\n]%*c%");
		getchar();
		switch (retry)
		{
		case 1:
		{
			CreateSys();
			return 0;
		}
		case 2:
		{
			printf("Okey, Boss\n");
			return 1;
		}
		default:
		{
			printf("Wrong format. Press button to retry\n");
			getchar();
			break;
		}
		}
	} while (retry != 2);

}
int CreateSys()
{
	FILE *base, *numb, *cfg;
	int ans1;

	ans1 = 0;

	if ((base = fopen("file.txt", "w+")) == NULL)
	{
		printf("Base file of Main Base was broken. PLS, call admin and don't touch anything\n");
		ans1++;
	}

	if ((numb = fopen("listofnumbers.txt", "w+")) == NULL)
	{
		printf("Base file of Numbers was broken. PLS, call admin and don't touch anything\n");
		ans1++;
	}

	if ((cfg = fopen("cfg.txt", "w+")) == NULL)
	{
		printf("Base file of Config was broken. PLS, call admin and don't touch anything\n");
		ans1++;
	}
	system("cls");
	switch (ans1)
	{
	case 0: 
	{ 
		printf("Recreation of files was sucsessfull\n");
		break;
	}
	default: 
	{
		printf("Recreation was broken. PLS, call admin and don't touch anything \n");
		return 1;
	}
	}


	fprintf(base,"0000 debug\n");
	fprintf(numb, "0000\n");
	fprintf(cfg, "Limit: 0\n");
	fclose(cfg);
	fclose(base);
	fclose(numb);
	

	printf("Continue working with base\n");
	system("pause");
	return 0;
}
int DelBase()
{
	int retry;
	retry = 0;

	do
	{
		system("cls");
		printf("Do you want to delete base?\n1 - Yes\n2 - No\nEnter action code: ");
		retry = getchar() - '0';
		scanf("%*[^\n]%*c%");
		getchar();
		switch (retry)
		{
		case 1:
		{
			Delete();
			return 0;
		}
		case 2:
		{
			printf("Okey, Boss\n");
			return 1;
		}
		default:
		{
			printf("Wrong format. Press button to retry\n");
			getchar();
			break;
		}
		}
	} while (retry != 2);
	return 0;
}
int Delete()
{
	int ans1;
	ans1 = 0;
	if((remove("file.txt"))!=NULL)
	{
		printf("Deletement of base file of Main Base was broken. PLS, call admin and don't touch anything\n");
		ans1++;
	}
	if ((remove("cfg.txt")) != NULL)
	{
		printf("Deletement of config file of Main Base was broken. PLS, call admin and don't touch anything\n");
		ans1++;
	}
	if ((remove("listofnumbers.txt")) != NULL)
	{
		printf("Deletement of numbers file of Main Base was broken. PLS, call admin and don't touch anything\n");
		ans1++;
	}
	system("cls");
	switch (ans1)
	{
	case 0:
	{
		printf("Deletement of files was sucsessfull\n");
		break;
	}
	default:
	{
		printf("Deletement was broken. PLS, call admin and don't touch anything \n");
		system("pause");
		return 1;
	}
	}

	printf("TO continue working with base recreate base \n");
	system("pause");
	return 0;
}
int deltrash()
{
	remove("cfg1.txt");
	remove("file1.txt");
	remove("listofnumbers1.txt");
	return 0;
}
