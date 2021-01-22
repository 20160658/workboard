Manage: Management.o StudentManagement.o StaffManagement.o AssetsManagement.o
	gcc -o Manage Management.o StudentManagement.o StaffManagement.o AssetsManagement.o
StudentManagement.o: StudentManagement.c Management.h
	gcc -c StudentManagement.c
StaffManagement.o: StaffManagement.c Management.h
	gcc -c StaffManagement.c
AssetsManagement.o: AssetsManagement.c Management.h
	gcc -c AssetsManagement.c
Management.o: Management.c Management.h
	gcc -c Management.c
clean:
	rm -f *.o
