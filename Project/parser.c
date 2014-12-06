#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define maxIndex 100 //default 
#define baseHeight 5

int main(int argc, char *argv[]){
	double footage[maxIndex][3];
	int printIndex = 0;
	
	char line[128];
	char *token;
	int i = 0;
	int tokenSize;

	if (argv[1] == NULL)
		printf("usage: ./makerbot [gcode filename]\n");
	
	else{
		FILE *f = fopen(argv[1], "r");
		if(f != NULL){
			while (fgets (line, sizeof line, f) != NULL){
				token = strtok(line, " "); //get first command
	printf("token:%s.", token);
//				if (token.match(/\bG1\b/)){ //if that cmd includes G1
{				printf("reached here");
					token = strtok(NULL, " "); //took x
						//footage[printIndex][0];
						printf("%dth line 1st tok %s\n", printIndex, token);
					token = strtok(NULL, " "); //took y
						//footage[printIndex][2];
						printf("%dth line 2nd tok%s\n", printIndex, token);
					footage[printIndex][1] = baseHeight;
#if 0					
					token = strsep(&line, " ");
					if(token[0] = "Z")
						for(i=0; i<printIndex; i++){
							footage[i][1] -= .07; //moves down		
						}
#endif
						printIndex++;
					}
				}
			
		}
		fclose(f);
	}
	return 0;
}
