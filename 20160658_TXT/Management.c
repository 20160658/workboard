#include "Management.h"

void ModeError()
{
	printf("Mode error.\nex) ./st Student\nMode : Student, Staff, Assets\n");
	return;
}

char * GetRemoveString(char *cMode) 
{
	if(!strcmp(cMode, "Student")) {
		return "./Student.txt";
	} else if(!strcmp(cMode, "Staff")) {
		return "./Staff.txt";
	} else if(!strcmp(cMode, "Assets")) {
		return "./Assets.txt";
	}
}

void GetTypeString(char *cMode) 
{
	printf("Select Type.\n0 : %s Register \n1 : %s List\n2 : %s Modify\n3 : %s Delete\n4 : Remove All Data\n5 : Quit\nInput : ", cMode, cMode, cMode, cMode);
}
	
void ExecuteFunction(char *cMode, char *cFunction)
{
	if(!strcmp(cMode, "Student") && !strcmp(cFunction, "Register")) { StudentRegister(); return; }
	else if(!strcmp(cMode, "Staff") && !strcmp(cFunction, "Register")) { StaffRegister(); return; }
	else if(!strcmp(cMode, "Assets") && !strcmp(cFunction, "Register")) { AssetsRegister(); return; }
	
	if(!strcmp(cMode, "Student") && !strcmp(cFunction, "List")) { StudentList(); return; }
	else if(!strcmp(cMode, "Staff") && !strcmp(cFunction, "List")) { StaffList(); return; }
	else if(!strcmp(cMode, "Assets") && !strcmp(cFunction, "List")) { AssetsList(); return; }
	
	if(!strcmp(cMode, "Student") && !strcmp(cFunction, "Modify")) { StudentModify(); return; }
	else if(!strcmp(cMode, "Staff") && !strcmp(cFunction, "Modify")) { StaffModify(); return; }
	else if(!strcmp(cMode, "Assets") && !strcmp(cFunction, "Modify")) { AssetsModify(); return; }

	if(!strcmp(cMode, "Student") && !strcmp(cFunction, "Delete")) { StudentDelete(); return; }
	else if(!strcmp(cMode, "Staff") && !strcmp(cFunction, "Delete")) { StaffDelete(); return; }
	else if(!strcmp(cMode, "Assets") && !strcmp(cFunction, "Delete")) { AssetsDelete(); return; }
}

void ChangeMode(char *cMode)
{
	int nMode;
	int nType;
	char cProgress='Y';
	char *cTemp;

	while(cProgress == 'Y' || cProgress == 'y') 
	{
		GetTypeString(cMode);
		scanf("%d", &nType);
		
		switch(nType) {
			case 0: ExecuteFunction(cMode, "Register");
				break;
			case 1: ExecuteFunction(cMode, "List");
				break; 
			case 2: ExecuteFunction(cMode, "Modify");
				break;
			case 3: ExecuteFunction(cMode, "Delete");
				break;
			case 4: remove(GetRemoveString(cMode));
				printf("Remove data complete.\n"); 
				break;
			case 5: return;
			default: printf("Wrong number.\n"); break;
		}
	
		printf("Continue? Y/N : ");
		ResetBuffer();
		scanf("%c", &cProgress); 
		if(cProgress != 'Y' && cProgress != 'N' && cProgress != 'y' && cProgress != 'n') {
			printf("Enter Y or N Please.\n");
			cProgress = 'Y';
			continue;
		}
	}
}

void main(int argc, char * argv[]) {
	if(argc != 2) 
	{
		ModeError();
		return;
	}

	if(!strcmp(argv[1], "Student")) {		
		ChangeMode("Student");
	} else if(!strcmp(argv[1], "Staff")) {
 		ChangeMode("Staff");
	} else if(!strcmp(argv[1], "Assets")) {
 		ChangeMode("Assets");
	} else {
		ModeError();
		return;
	}
}

void ResetBuffer() {
	getchar();
	fflush(stdin);
}
			
