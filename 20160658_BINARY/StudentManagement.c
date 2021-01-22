#include "Management.h"

char GetGrade(int nScore) {
	if(nScore >= 90) {
		return 'A';
	} else if(nScore >= 80) {
		return 'B';
	} else if(nScore >= 70) {
		return 'C';
	} else if(nScore >= 60) {
		return 'D';
	} else {
		return 'F';
	}	
}

void StudentList() {	
	FILE *fFile;
	struct sStudent Student;
	char cProgress;

	if((fFile = fopen("./Student.bin", "rb+")) == NULL) 
	{
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	printf("Wait few seconds...\n");
	printf("-------------------------------------------------------------------------\n");
	printf("%s %s %s %s %s %s %s %s\n","ID","Name","Number","Address", "RRN", "Department", "E-mail", "Comment");
	while(fread(&Student, sizeof(Student), 1, fFile) > 0) {
		if(Student.nID != 0) {
			printf("%d %s %s %s %s %s %s %s\n", Student.nID, Student.cName, Student.cNumber, Student.cAddress, Student.cRRN, Student.cDepartment, Student.cMail, Student.cComment);
		}
	}
	printf("-------------------------------------------------------------------------\n");

	printf("Write Y for more information or write N for exit : ");
	ResetBuffer();
	scanf("%c", &cProgress);
	if(cProgress == 'Y' || cProgress == 'y') {
		StudentSearch();
	} else {
		return;
	}
}

void StudentRegister() {
	FILE *fFile;
	struct sStudent Student;
	
	fFile = fopen("./Student.bin", "rb");
	if(fFile == NULL) {
		fFile = fopen("./Student.bin", "wb");
	} else {
		fFile = fopen("./Student.bin", "rb+");
	}


	printf("Please write your information.\nFor save and quit, write Alphabet and press Enter key.\nEnter ID over 10000000.\n");
	printf("%s %s %s %s %s %s %s %s\n","ID","Name","Number","Address", "RRN", "Department", "E-mail", "Comment");
	while(scanf("%d %s %s %s %s %s %s %s", &Student.nID, Student.cName, Student.cNumber, Student.cAddress, Student.cRRN, Student.cDepartment, Student.cMail, Student.cComment) == 8) 
	{
		if(Student.nID >= 0 && Student.nID < 10000000)
		{
			printf("Please enter ID over 10000000.\n");
			return;
		}
		strcpy(Student.State.cState, "Admission");
		strcpy(Student.State.cDate, "2000-01-01");
		strcpy(Student.Award.cAward, "None");
		Student.Award.lMoney = 0l;
		memset(Student.Subject, 0, sizeof(Student.Subject));
		fseek(fFile, sizeof(Student) * (Student.nID - STUDENT_DIVISION), SEEK_SET);
		fwrite(&Student, sizeof(Student), 1, fFile);
		fflush(fFile);
	}
	printf("Saved.\n");
	ResetBuffer();
	fclose(fFile);
	return;
}

void StudentSearch() {
	struct sStudent Student;
	FILE *fFile;
	int nID;
	
	if((fFile = fopen("./Student.bin", "rb+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	printf("Write ID for search : ");
	if(scanf("%d", &nID) == 1) {
		fseek(fFile, sizeof(Student) * (nID - STUDENT_DIVISION), SEEK_SET);
		if((fread(&Student, sizeof(Student), 1, fFile) > 0) && (Student.nID != 0)) {
			printf("-------------------------------------------------------------------------\n");
			printf("%s %s %s %s %s %s %s %s\n","ID","Name","Number","Address", "RRN", "Department", "E-mail", "Comment");	
			printf("%d %s %s %s %s %s %s %s\n", Student.nID, Student.cName, Student.cNumber, Student.cAddress, Student.cRRN, Student.cDepartment, Student.cMail, Student.cComment);
							printf("-------------------------------------------------------------------------\n");
			printf("%s %s %s %s\n", "State", "Date", "Award", "Money");
			printf("%s %s %s %ld\n", Student.State.cState, Student.State.cDate, Student.Award.cAward, Student.Award.lMoney);
printf("-------------------------------------------------------------------------\n");
			printf("Subject Number Name Score Grade\n");
			for(int i=0; i<10; i++) {
				if(Student.Subject[i].cSubject[0] == 0) {
					strcpy(Student.Subject[i].cSubject, "-");
				}
				if(Student.Subject[i].cGrade == 0)
					Student.Subject[i].cGrade = '-';
				printf("%d %s %d %c\n",i+1, Student.Subject[i].cSubject, Student.Subject[i].nScore, Student.Subject[i].cGrade);
			}
			printf("-------------------------------------------------------------------------\n");
			fflush(fFile);
		} else printf("Record %d error.\n", nID);
	} else printf("Input error.\n");
	fclose(fFile);
	return;
}

void StudentModify() {
	FILE *fFile;
	struct sStudent Student;
	int nType;
	int nID;
	int nOption;
	int nSubject;
	char cCheck = 'Y';
	
	if((fFile = fopen("./Student.bin", "rb+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	while(cCheck == 'Y' || cCheck == 'y') {
		printf("Write ID for modify : ");
		if(scanf("%d", &nID) == 1) { 
			fseek(fFile, sizeof(Student) * (nID - STUDENT_DIVISION), SEEK_SET);
			if((fread(&Student, sizeof(Student), 1, fFile) > 0) && (Student.nID != 0)) 
			{
				printf("Edit Option.\n1 : Name 2 : Number 3 : Address\n4 : Department 5 : E-mail 6 : Comment\n7 : State 8 : Award 9 : Subject\nInput : ");
				scanf("%d", &nType);
				switch(nType) {
					case 1: ResetBuffer(); printf("Input Name for modify : "); scanf("%[^\n]", Student.cName); break;	
					case 2: ResetBuffer(); printf("Input Number for modify : "); scanf("%s", Student.cNumber); break;
					case 3: ResetBuffer(); printf("Input Address for modify : "); scanf("%[^\n]", Student.cAddress); break;
					case 4: ResetBuffer(); printf("Input Department for modify : "); scanf("%[^\n]", Student.cDepartment); break;
					case 5: ResetBuffer(); printf("Input E-Mail for modify : "); scanf("%s", Student.cMail); break;
					case 6: ResetBuffer(); printf("Input Comment for modify : "); scanf("%[^\n]", Student.cComment); break;
					case 7: ResetBuffer(); 
						printf("Input Status Option\n0 : State\n1 : Date\n: "); 
						scanf("%d", &nOption); 
						switch(nOption) { 
							case 0: 
								ResetBuffer();
								printf("Value : "); 
								scanf("%s", Student.State.cState); 
								break; 
							case 1: 
								ResetBuffer();
								printf("Value : "); 
								scanf("%s", Student.State.cDate); 
								break;
							default:
								printf("Option error.\n");
								break; 
						}
						break;
					case 8: ResetBuffer();
						printf("Input Award Option\n0 : Award\n1 : Money\n: "); 
						scanf("%d", &nOption); 
						switch(nOption) { 
							case 0: 
								ResetBuffer();		
								printf("Value : "); 
								scanf("%[^\n]", Student.Award.cAward); 
								break; 
							case 1: 
								ResetBuffer();
								printf("Value : "); 
								scanf("%ld", &Student.Award.lMoney); 
								break;
							default:
								printf("Option error\n");
								break; 
						}
						break;
					case 9: 
						ResetBuffer();
						printf("Input Subject Number 1~10 : \n"); 
						scanf("%d", &nSubject); 
						nSubject--;
						if(nSubject > 9 && nSubject < 0) {
							printf("Value error.\n"); 
							break;
						}
						printf("input Subject Option\n0 : Subject 1 : Score\n: "); 
						scanf("%d", &nOption); 
						switch(nOption) { 
							case 0: 
								ResetBuffer();
								printf("Value : "); 
								scanf("%[^\n]", Student.Subject[nSubject].cSubject); 
								break; 
							case 1: 
								ResetBuffer();
								printf("Value : "); 
								scanf("%d", &Student.Subject[nSubject].nScore); 
								Student.Subject[nSubject].cGrade = GetGrade(Student.Subject[nSubject].nScore);
								break;
							default:
								printf("Option error.\n");
								break; 
						}
						break;
					default: printf("Option error.\n"); break;
				}
			fseek(fFile, -sizeof(Student), SEEK_CUR);
			fwrite(&Student, sizeof(Student), 1, fFile);
			fflush(fFile);
			} else printf("Record %d error.\n", nID);
		} else printf("Input error.\n");
		ResetBuffer();
		printf("Y(Modify Other Student Record) N(Back to menu) : ");
		scanf("%c", &cCheck);
		if(cCheck == 'N' || cCheck == 'n')
			return;
		if(cCheck != 'Y' && cCheck != 'N' && cCheck != 'y' && cCheck != 'n') {
			printf("Input error.\n");
			cCheck = 'Y';		
		}
	}
	fclose(fFile);	
}

void StudentDelete()
{
	FILE *fFile;
	struct sStudent Student;
	int nID;
	char cCheck = 'Y';
	
	if((fFile = fopen("./Student.bin", "rb+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}
	
	while(cCheck == 'Y' || cCheck == 'y') {
		printf("Write ID for delete : ");
		if(scanf("%d", &nID) == 1) {
			fseek(fFile, sizeof(Student) * (nID - STUDENT_DIVISION), SEEK_SET);
			if((fread(&Student, sizeof(Student), 1, fFile) > 0) && (Student.nID != 0)) 	
			{
				fseek(fFile, -sizeof(Student), SEEK_CUR);
				Student.nID = 0;
				fwrite(&Student, sizeof(Student), 1, fFile);
				printf("Record ID %d has been deleted.\n", nID);
				fflush(fFile);
			} else printf("Record %d error.\n", nID);
		} else printf("Input error.\n");
		ResetBuffer();
		printf("Y(Delete other Student record) N(Back to menu) : \n");
		scanf("%c", &cCheck);
		if(cCheck == 'N')
			return;
		if(cCheck != 'Y' && cCheck != 'N' && cCheck != 'y' && cCheck != 'n') {
			printf("Input error.\n");
			cCheck = 'Y';		
		}
	}
	fclose(fFile);
	return;
}

