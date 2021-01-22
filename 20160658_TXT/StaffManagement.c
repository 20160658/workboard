#include "Management.h"

/*
	int nID;
	char cName[20];
	char cNumber[13];
	char cAddress[20];
	char cRRN[14];
	char cDepartment[20];
	char cDate[20];
*/

void StaffList() {	
	FILE *fFile;
	struct sStaff Staff;
	char cProgress;

	if((fFile = fopen("./Staff.txt", "r+")) == NULL) 
	{
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	printf("Wait few seconds...\n");	
	printf("-------------------------------------------------------------------------\n");
	printf("%s %s %s %s\n","ID","Name","Number", "RRN");
	while(fread(&Staff, sizeof(Staff), 1, fFile) > 0) {
		if(Staff.nID != 0) {
			printf("%d %s %s %s\n", Staff.nID, Staff.cName, Staff.cNumber, Staff.cRRN);
		}
	}
	printf("-------------------------------------------------------------------------\n");

	printf("Write Y for more information or write N for exit : ");
	ResetBuffer();
	scanf("%c", &cProgress);
	if(cProgress == 'Y' || cProgress == 'y') {
		StaffSearch();
	} else {
		return;
	}
}


void StaffRegister() {
	FILE *fFile;
	struct sStaff Staff;
	
	fFile = fopen("./Staff.txt", "r");
	if(fFile == NULL) {
		fFile = fopen("./Staff.txt", "w+");
	} else {
		fFile = fopen("./Staff.txt", "r+");
	}


	printf("Please write your information.\nFor save and quit, write Alphabet and press Enter key.\nEnter ID over 10000.\n");
	printf("%s %s %s %s %s %s %s %s\n","ID","Name","Number","Address", "RRN", "Department", "Date", "Comment");
	while(scanf("%d %s %s %s %s %s %s %s", &Staff.nID, Staff.cName, Staff.cNumber, Staff.cAddress, Staff.cRRN, Staff.cDepartment, Staff.cDate, Staff.cComment) == 8) 
	{
		if(Staff.nID >= 0 && Staff.nID < 10000)
		{
			printf("Please enter ID over 10000.\n");
			return;
		}
		fseek(fFile, sizeof(Staff) * (Staff.nID - STAFF_DIVISION), SEEK_SET);
		fwrite(&Staff, sizeof(Staff), 1, fFile);
		fflush(fFile);
	}
	printf("Saved.\n");
	ResetBuffer();
	fclose(fFile);
	return;
}

void StaffSearch() {
	struct sStaff Staff;
	FILE *fFile;
	int nID;
	
	if((fFile = fopen("./Staff.txt", "r+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	printf("Write ID for search : ");
	if(scanf("%d", &nID) == 1) {
		fseek(fFile, sizeof(Staff) * (nID - STAFF_DIVISION), SEEK_SET);
		if((fread(&Staff, sizeof(Staff), 1, fFile) > 0) && (Staff.nID != 0)) {
			printf("-------------------------------------------------------------------------\n");
			printf("%s %s %s %s %s %s %s %s\n","ID","Name","Number","Address", "RRN", "Department", "Date", "Comment");	
			printf("%d %s %s %s %s %s %s %s\n", Staff.nID, Staff.cName, Staff.cNumber, Staff.cAddress, Staff.cRRN, Staff.cDepartment, Staff.cDate, Staff.cComment);
			printf("-------------------------------------------------------------------------\n");
			fflush(fFile);
		} else printf("Record %d error.\n", nID);
	} else printf("Input error.\n");
	fclose(fFile);
	return;
}

void StaffModify() {
	FILE *fFile;
	struct sStaff Staff;
	int nType;
	int nID;
	char cCheck = 'Y';
	
	if((fFile = fopen("./Staff.txt", "r+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	while(cCheck == 'Y' || cCheck == 'y') {
		printf("Write ID for modify : ");
		if(scanf("%d", &nID) == 1) { 
			fseek(fFile, sizeof(Staff) * (nID - STAFF_DIVISION), SEEK_SET);
			if((fread(&Staff, sizeof(Staff), 1, fFile) > 0) && (Staff.nID != 0)) 
			{
				printf("Edit Option.\n1 : Name 2 : Number 3 : Address\n4 : Department 5 : Date 6 : Comment\nInput : ");
				scanf("%d", &nType);
				switch(nType) {
					case 1: ResetBuffer(); printf("Input Name for modify : "); scanf("%[^\n]", Staff.cName); break;	
					case 2: ResetBuffer(); printf("Input Number for modify : "); scanf("%s", Staff.cNumber); break;
					case 3: ResetBuffer(); printf("Input Address for modify : "); scanf("%[^\n]", Staff.cAddress); break;
					case 4: ResetBuffer(); printf("Input Department for modify : "); scanf("%[^\n]", Staff.cDepartment); break;
					case 5: ResetBuffer(); printf("Input Date for modify : "); scanf("%s", Staff.cDate); break;
					case 6: ResetBuffer(); printf("Input Department for modify : "); scanf("%[^\n]", Staff.cComment); break;
					default: printf("Option error.\n"); break;
				}
			fseek(fFile, -sizeof(Staff), SEEK_CUR);
			fwrite(&Staff, sizeof(Staff), 1, fFile);
			fflush(fFile);
			} else printf("Record %d error.\n", nID);
		} else printf("Input error.\n");
		ResetBuffer();
		printf("Y(Modify Other Staff Record) N(Back to menu) : ");
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

void StaffDelete()
{
	FILE *fFile;
	struct sStaff Staff;
	int nID;
	char cCheck = 'Y';
	
	if((fFile = fopen("./Staff.txt", "r+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}
	
	while(cCheck == 'Y' || cCheck == 'y') {
		printf("Write ID for delete : ");
		if(scanf("%d", &nID) == 1) {
			fseek(fFile, sizeof(Staff) * (nID - STAFF_DIVISION), SEEK_SET);
			if((fread(&Staff, sizeof(Staff), 1, fFile) > 0) && (Staff.nID != 0)) 	
			{
				fseek(fFile, -sizeof(Staff), SEEK_CUR);
				Staff.nID = 0;
				fwrite(&Staff, sizeof(Staff), 1, fFile);
				printf("Record ID %d has been deleted.\n", nID);
				fflush(fFile);
			} else printf("Record %d error.\n", nID);
		} else printf("Input error.\n");
		ResetBuffer();
		printf("Y(Delete other Staff record) N(Back to menu) : \n");
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

