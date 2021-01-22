#include "Management.h"

/*
	int nID
	char cName[20]
	char cDepartment[20]
	char cAdmin[20]
	char cLocation[20]
	char cDate[20]
	long lPrice
	char cComment[20]
*/

void AssetsList() {	
	FILE *fFile;
	struct sAssets Assets;
	char cProgress;

	if((fFile = fopen("./Assets.txt", "r+")) == NULL) 
	{
		fprintf(stderr, "Error while opening file.\n");
		return;
	}
	
	printf("Wait few seconds...\n");
	printf("-------------------------------------------------------------------------\n");
	printf("%s %s %s %s %s\n","ID","Name","Department","Location","Date");

	while(fread(&Assets, sizeof(Assets), 1, fFile) > 0) {
		if(Assets.nID != 0) {
			printf("%d %s %s %s %s\n", Assets.nID, Assets.cName, Assets.cDepartment, Assets.cLocation, Assets.cDate);
		}
	} 
	printf("-------------------------------------------------------------------------\n");

	printf("Write Y for more information or write N for exit : ");
	ResetBuffer();
	scanf("%c", &cProgress);
	if(cProgress == 'Y' || cProgress == 'y') {
		AssetsSearch();
	} else {
		return;
	}
}

void AssetsRegister() {
	FILE *fFile;
	struct sAssets Assets;
	
	fFile = fopen("./Assets.txt", "r");
	if(fFile == NULL) {
		fFile = fopen("./Assets.txt", "w+");
	} else {
		fFile = fopen("./Assets.txt", "r+");
	}


	printf("Please write your information.\nFor save and quit, write Alphabet and press Enter key.\nEnter ID over 100.\n");
	printf("%s %s %s %s %s %s %s %s\n","ID","Name","Department","Admin", "Location", "Date", "Price", "Comment");
	while(scanf("%d %s %s %s %s %s %ld %s", &Assets.nID, Assets.cName, Assets.cAdmin, Assets.cDepartment, Assets.cLocation, Assets.cDate, &Assets.lPrice, Assets.cComment) == 8) 
	{
		if(Assets.nID >= 0 && Assets.nID < 100)
		{
			printf("Please enter ID over 100.\n");
			return;
		}
		fseek(fFile, sizeof(Assets) * (Assets.nID - ASSETS_DIVISION), SEEK_SET);
		fwrite(&Assets, sizeof(Assets), 1, fFile);
		fflush(fFile);
	}
	printf("Saved.\n");
	ResetBuffer();
	fclose(fFile);
	return;
}

void AssetsSearch() {
	struct sAssets Assets;
	FILE *fFile;
	int nID;
	
	if((fFile = fopen("./Assets.txt", "r+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	printf("Write ID for search : ");
	if(scanf("%d", &nID) == 1) {
		fseek(fFile, sizeof(Assets) * (nID - ASSETS_DIVISION), SEEK_SET);
		if((fread(&Assets, sizeof(Assets), 1, fFile) > 0) && (Assets.nID != 0)) {
			printf("-------------------------------------------------------------------------\n");
			printf("%s %s %s %s %s %s %s %s\n","ID","Name","Admin", "Department","Location", "Date", "Price", "Comment");	
			printf("%d %s %s %s %s %s %ld %s\n", Assets.nID, Assets.cName, Assets.cAdmin, Assets.cDepartment, Assets.cLocation, Assets.cDate, Assets.lPrice, Assets.cComment);
			printf("-------------------------------------------------------------------------\n");
			fflush(fFile);
		} else printf("Record %d error.\n", nID);
	} else printf("Input error.\n");
	fclose(fFile);
	return;
}

void AssetsModify() {
	FILE *fFile;
	struct sAssets Assets;
	int nType;
	int nID;
	char cCheck = 'Y';
	
	if((fFile = fopen("./Assets.txt", "r+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}

	while(cCheck == 'Y' || cCheck == 'y') {
		printf("Write ID for modify : ");
		if(scanf("%d", &nID) == 1) { 
			fseek(fFile, sizeof(Assets) * (nID - ASSETS_DIVISION), SEEK_SET);
			if((fread(&Assets, sizeof(Assets), 1, fFile) > 0) && (Assets.nID != 0)) 
			{
				printf("Edit Option.\n1 : Name 2 : Admin 3 : Department\n4 : Location 5 : Date 6: Price 7 : Comment\nInput : ");
				scanf("%d", &nType);
				switch(nType) {
					case 1: ResetBuffer(); printf("Input Name for modify : "); scanf("%[^\n]", Assets.cName); break;	
					case 2: ResetBuffer(); printf("Input Admin for modify : "); scanf("%[^\n]", Assets.cAdmin); break;
					case 3: ResetBuffer(); printf("Input Department for modify : "); scanf("%[^\n]", Assets.cDepartment); break;
					case 4: ResetBuffer(); printf("Input Location for modify : "); scanf("%[^\n]", Assets.cLocation); break;
					case 5: ResetBuffer(); printf("Input Date for modify : "); scanf("%s", Assets.cDate); break;
					case 6: ResetBuffer(); printf("Input Price for modify : "); scanf("%ld", &Assets.lPrice); break;
					case 7: ResetBuffer(); printf("Input Comment for modify : "); scanf("%[^\n]", Assets.cComment); break;
					default: printf("Option error.\n"); break;
				}
			fseek(fFile, -sizeof(Assets), SEEK_CUR);
			fwrite(&Assets, sizeof(Assets), 1, fFile);
			fflush(fFile);
			} else printf("Record %d error.\n", nID);
		} else printf("Input error.\n");
		ResetBuffer();
		printf("Y(Modify Other Assets Record) N(Back to menu) : \n");
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

void AssetsDelete()
{
	FILE *fFile;
	struct sAssets Assets;
	int nID;
	char cCheck = 'Y';
	
	if((fFile = fopen("./Assets.txt", "r+")) == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return;
	}
	
	while(cCheck == 'Y' || cCheck == 'y') {
		printf("Write ID for delete : ");
		if(scanf("%d", &nID) == 1) {
			fseek(fFile, sizeof(Assets) * (nID - ASSETS_DIVISION), SEEK_SET);
			if((fread(&Assets, sizeof(Assets), 1, fFile) > 0) && (Assets.nID != 0)) 	
			{
				fseek(fFile, -sizeof(Assets), SEEK_CUR);
				Assets.nID = 0;
				fwrite(&Assets, sizeof(Assets), 1, fFile);
				printf("Record ID %d has been deleted.\n", nID);
				fflush(fFile);
			} else printf("Record %d error.\n", nID);
		} else printf("Input error.\n");
		ResetBuffer();
		printf("Y(Delete other Assets record) N(Back to menu) : ");
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

