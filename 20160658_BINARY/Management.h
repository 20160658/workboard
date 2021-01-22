#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define STUDENT_DIVISION 10000000
#define STAFF_DIVISION 10000
#define ASSETS_DIVISION 100

/*
typedef enum
{
	false = 0,
	true = 1
} bool;
*/

void ResetBuffer();

void StudentList();
void StudentRegister();
void StudentSearch();
void StudentModify();
void StudentDelete();

void StaffList();
void StaffRegister();
void StaffSearch();
void StaffModify();
void StaffDelete();

void AssetsList();
void AssetsRegister();
void AssetsSearch();
void AssetsModify();
void AssetsDelete();

struct sState {
	char cState[10];
	char cDate[20];
};

struct sSubject {
	char cSubject[20];
	int nScore;
	char cGrade;
};

struct sAward {
	char cAward[20];
	long lMoney;
};

struct sStudent {
	int nID;
	char cName[20];
	char cNumber[20];
	char cAddress[20];
	char cRRN[20];
	char cDepartment[20];
	char cMail[30];
	char cComment[30];
	struct sState State;
	struct sSubject Subject[10];
	struct sAward Award;
};

struct sStaff {
	int nID;
	char cName[20];
	char cNumber[20];
	char cAddress[20];
	char cRRN[20];
	char cDepartment[20];
	char cDate[20];
	char cComment[30];
};

struct sAssets {
	int nID;
	char cName[20];
	char cDepartment[20];
	char cAdmin[20];
	char cLocation[20];
	char cDate[20];
	long lPrice;
	char cComment[30];
};
