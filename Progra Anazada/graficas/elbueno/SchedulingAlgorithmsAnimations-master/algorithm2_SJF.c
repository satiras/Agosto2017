// algorithm2_SJF.c
// to compile, do this: gcc -lncurses algorithm2_SJF.c
// To compile this, you need to have ncurses installed

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DELAY 30000
#define TOT_PROCESSES 4

void drawLine(int loIndex, int hiIndex, int verticalIsConstant, int constantIndex, char* string){

	for(int i = loIndex; i <= hiIndex; i++){

		if(verticalIsConstant == 1)
			mvprintw(constantIndex, i, string);

		else
			mvprintw(i, constantIndex, string);
	}
}

void draw(int loY, int loX, int hiY, int hiX, char* charToDraw, int counter, char* processName, char* processBurstTime, char* processAriival){

	drawBox(loY, loX, hiY, hiX, charToDraw);
	drawInsideBox(loY - 1 +  (hiY - loY)/2, loX + (hiX - loX)/2, processName);
	drawInsideBox(loY + (hiY - loY)/2, loX + (hiX - loX)/2, processBurstTime);
    drawInsideBox(loY + 1 + (hiY - loY)/2, loX + (hiX - loX)/2, processAriival);
	addColor(counter, 10);
}

void drawInsideBox(int y, int x, char* numberToDraw){

	mvprintw(y, x, numberToDraw);
}

void addColor(int counter, int mod){

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	attron(COLOR_PAIR((counter%mod)/(mod/2) +  1));
	attron(COLOR_PAIR(1));
}

void draw(int loY, int loX, int hiY, int hiX, char* charToDraw, int counter, char* processName, char* processBurstTime){

	drawBox(loY, loX, hiY, hiX, charToDraw);
	drawInsideBox(loY + (hiY - loY)/2, loX + (hiX - loX)/2, processName);
	drawInsideBox(loY + 1 + (hiY - loY)/2, loX + (hiX - loX)/2, processBurstTime);
	addColor(counter, 10);
}

void drawCPU(int cpuLoY, int cpuLoX, int cpuHiY, int cpuHiX){

	drawBox(cpuLoY, cpuLoX, cpuHiY, cpuHiX, "*");
	drawInsideBox(cpuLoY + 2, cpuLoX - 1 + (cpuHiX - cpuLoX)/2, "CPU");
	addColor(10, 10);
}

void drawTotalWaitingTime(int y, int x, int time){

	char strTime[10];
	sprintf(strTime, "%d", time);
	mvprintw(y, x - 12, "Total CPU time: ");
	mvprintw(y, x + 4, strTime);
}

void drawRemainingProcessesCounter(int y, int x, int remainingProcessesCounter){

	char strRemainingProcessesCounter[10];
	sprintf(strRemainingProcessesCounter, "%d", remainingProcessesCounter);
	mvprintw(y, x - 20, "Remaining Processes: ");
	mvprintw(y, x + 1, strRemainingProcessesCounter);
}

void advanceCoordinates(int* ptrNext_x, int* ptrLoX, int* ptrHiX, int* ptrDirection, int max_x){

 	*ptrNext_x = *ptrHiX + *ptrDirection;

 	if(*ptrNext_x >= max_x || *ptrNext_x < 0){

 		*ptrDirection *= -1;
 	}

 	else{

 		*ptrLoX += *ptrDirection;
 		*ptrHiX += *ptrDirection;
 	}
}

int isItsTurn(int processIndex, int processIsFinished[]){

	return processIsFinished[processIndex - 1] == 1;
}

int *array;

int cmp(const void *a, const void *b){
    
    int ia = *(int *)a;
    int ib = *(int *)b;
    
    return (array[ia] < array[ib]) ? -1 : array[ia] > array[ib];
}

int main() {

	int max_y = 0, max_x = 0;
	char* toDraw = "*";
	int totalWaitingTime = 0;
	int remainingProcessesCounter = TOT_PROCESSES;

	int arrLoY[TOT_PROCESSES], arrLoX[TOT_PROCESSES], arrHiY[TOT_PROCESSES], arrHiX[TOT_PROCESSES];
	int arrNext_x[TOT_PROCESSES];
	int arrDirection[TOT_PROCESSES];

	int cpuLoY, cpuLoX, cpuHiY, cpuHiX;
	cpuLoY = 0;
	cpuLoX = 70;
	cpuHiY = 20;
	cpuHiX = 90;

	char arrProcessesNames[TOT_PROCESSES][10];
	strcpy(arrProcessesNames[0], "A");
	strcpy(arrProcessesNames[1], "B");
	strcpy(arrProcessesNames[2], "C");
	strcpy(arrProcessesNames[3], "D");


	int arrProcessTotalTime[TOT_PROCESSES] = {9,5,7,1};
	int arrProcessCurrentTime[TOT_PROCESSES] = {0, 0, 0, 0};
    int arrProcessArriva[TOT_PROCESSES] = {0,2,3,5};

	char intToStr[10];
	char arrProcessesBurstTimes[TOT_PROCESSES][10];
	char arrArrival[TOT_PROCESSES][10];
	
	sprintf(intToStr, "%d", arrProcessTotalTime[0]);
	strcpy(arrProcessesBurstTimes[0], intToStr);
	
	sprintf(intToStr, "%d", arrProcessTotalTime[1]);
	strcpy(arrProcessesBurstTimes[1], intToStr);
		
	sprintf(intToStr, "%d", arrProcessTotalTime[2]);
	strcpy(arrProcessesBurstTimes[2], intToStr);
		
	sprintf(intToStr, "%d", arrProcessTotalTime[3]);
	strcpy(arrProcessesBurstTimes[3], intToStr);
//
	sprintf(intToStr, "%d", arrProcessArriva[0]);
	strcpy(arrArrival[0], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[1]);
	strcpy(arrArrival[1], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[2]);
	strcpy(arrArrival[2], intToStr);

	sprintf(intToStr, "%d", arrProcessArriva[3]);
	strcpy(arrArrival[3], intToStr);


	int processIsFinished[TOT_PROCESSES] = {0, 0, 0, 0};

	arrLoY[3] = 8;
	arrLoX[3] = 0;
	arrHiY[3] = 12;
	arrHiX[3] = 8;
	arrNext_x[3] = 0;
	arrDirection[3] = 1;

	arrLoY[2] = 8;
	arrLoX[2] = 12;
	arrHiY[2] = 12;
	arrHiX[2] = 20;
	arrNext_x[2] = 0;
	arrDirection[2] = 1;

	arrLoY[1] = 8;
	arrLoX[1] = 24;
	arrHiY[1] = 12;
	arrHiX[1] = 32;
	arrNext_x[1] = 0;
	arrDirection[1] = 1;

	arrLoY[0] = 8;
	arrLoX[0] = 36;
	arrHiY[0] = 12;
	arrHiX[0] = 44;
	arrNext_x[0] = 0;
	arrDirection[0] = 1;

	initscr();
	noecho();
	curs_set(FALSE);

	/////////////////////////////////////

	int orderedProcessesIndices[TOT_PROCESSES];//use malloc to large size array
    int i;

    for(i = 0; i < TOT_PROCESSES; i++)
        orderedProcessesIndices[i] = i;
   
    array = arrProcessTotalTime;
    qsort(orderedProcessesIndices, TOT_PROCESSES, sizeof(*orderedProcessesIndices), cmp);

	////////////////////////////////////

	// Global var `stdscr` is created by the call to `initscr()`
	getmaxyx(stdscr, max_y, max_x);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	int counter = 0;

	int processCounter = 0;

	while(remainingProcessesCounter > 0) {

		clear();
		drawCPU(cpuLoY, cpuLoX, cpuHiY, cpuHiX);
		mvprintw(0, 0, "Shortest-job-first algorithm");
		drawRemainingProcessesCounter(2, 20, remainingProcessesCounter);
		drawTotalWaitingTime(3, 12, totalWaitingTime);

		char intToStr[10];
		int currProcessIndex = orderedProcessesIndices[processCounter];

		for(int i = 0; i < TOT_PROCESSES; i++){

			if(processIsFinished[i] == 1)
				continue;

			draw(arrLoY[i], arrLoX[i], arrHiY[i], arrHiX[i], toDraw, counter, arrProcessesNames[i], arrProcessesBurstTimes[i],arrArrival[i]);
			if(i > 0 && !isItsTurn(i, processIsFinished))
				continue;
	 			
			if(arrLoX[currProcessIndex] < cpuLoX + (cpuHiX - cpuLoX)/2 - 4)
	 			advanceCoordinates(&arrNext_x[currProcessIndex], &arrLoX[currProcessIndex], &arrHiX[currProcessIndex], &arrDirection[currProcessIndex], max_x);

	 		if(!processIsFinished[currProcessIndex] && arrLoX[currProcessIndex] == cpuLoX + (cpuHiX - cpuLoX)/2 - 4){

	 			if(arrProcessCurrentTime[currProcessIndex] == arrProcessTotalTime[currProcessIndex]){

	 				remainingProcessesCounter--;
	 				processIsFinished[currProcessIndex] = 1;
	 				processCounter++;
	 			}

	 			else{

	 				totalWaitingTime++;
	 				arrProcessCurrentTime[currProcessIndex]++;
	 			}
	 		}
	 	}

	 	refresh();
	 	usleep(10*DELAY);
	 	counter++;
	}

	usleep(10*DELAY);
	endwin();

	return 0;
}