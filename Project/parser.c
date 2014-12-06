#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define maxIndex 100 //default 

double footage[maxIndex][3];
double baseHeight = 5;


int main(int argc, char *argv[]){
	int printIndex = 0;
	
	char line[128];
	char *token;
	char tmp[128];
	int i = 0;
	int tokenSize;

	if (argv[1] == NULL)
		printf("usage: ./makerbot [gcode filename]\n");
	
	else{
		FILE *f = fopen(argv[1], "r");
		if(f != NULL){
			while (fgets (line, sizeof line, f) != NULL){
				token = strtok(line, " "); //get first command
				if(strspn(token, "G1") == 2){ //it starts with "G1"
					token = strtok(NULL, " ");
					//parsing X or Z
					if(strspn(token, "X") == 1){ //moving x
						strcpy(tmp, token);
						for(i=0; i<strlen(tmp); i++)
							tmp[i] = tmp[i+1]; //take charater "x" off
						footage[printIndex][0] = atof(tmp);
//printf("x: %f ",footage[printIndex][0]);
						token = strtok(NULL, " "); //took y
						if(strspn(token, "Y") == 1){ //moving y
							strcpy(tmp, token);
							for(i=0; i<strlen(tmp); i++)
								tmp[i] = tmp[i+1]; //take charater "y" off
							footage[printIndex][2] = atof(tmp); //z-axe in OpenGL
//printf("y: %f ",footage[printIndex][2]);
						}
						footage[printIndex][1] = baseHeight;
//printf("z: %f\n",footage[printIndex][1]);
						printIndex++;
					} else if(strspn(token, "Z") == 1) //moving z(height)i
						baseHeight -= 0.7; //only when Z-cmd occur 
				}
			}
			fclose(f);
			for (i=0; i<printIndex; i++)
				printf("x:%f, y:%f, z:%f\n", 
					footage[i][0], footage[i][1], footage[i][2]);
		}
	}
	return 0;
}
