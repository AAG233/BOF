#include<unistd.h>
void main(){
	char *apuntador[2];
	apuntador[0] = "/bin/sh";
	apuntador[1] = NULL;
	execve(apuntador[0], apuntador, NULL);
}
