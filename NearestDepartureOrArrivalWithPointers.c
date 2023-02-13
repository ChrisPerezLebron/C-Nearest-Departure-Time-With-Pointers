#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void timeInMinToFormated(int timeInMin, char output[]);
void findClosestFlight(int desiredTime, int *departureTime, int *arrivalTime);


//global variables
//set of hard coded departure and arrival times

//times are expressed in minutes past midnight
int departures[] = {480, 583, 679, 767, 840, 945, 1140, 1305};

//times are expressed in minutes past midnight
int arrivals[] = {616, 712, 811, 900, 968, 1075, 1280, 1438};


int main( ){

	printf("Enter a 24-hour time: ");

	int hours, min;

	scanf("%d:%d", &hours, &min);

	//printf("%d\n%d\n", hours, min);

	int timeInMin = (hours * 60) + min;


	//find closest departure time & its arrival time
	int departureTime, arrivalTime;
	findClosestFlight(timeInMin, &departureTime, &arrivalTime);

	char departureTimeStr[30], arrivalTimeStr[30];

	timeInMinToFormated(departureTime, departureTimeStr);
	timeInMinToFormated(arrivalTime, arrivalTimeStr);


	printf("Closest departure time is %s, arriving at %s", departureTimeStr, arrivalTimeStr);


}

//takes the time in min since midnight and translates it into 12 hour time and prints the value
//info to console
void timeInMinToFormated(int timeInMin, char output[]) {

	int hours24 = timeInMin / 60;

	//update timeInMin
	timeInMin -= (hours24 * 60);

	int min = timeInMin;

	char timePeriod[20];

	if(hours24 >= 12) {
		strncpy(timePeriod, "P.M.", 19);

		//we want to leave hours24 unmodified if it is 12. Otherwise we want to subtract
		//12
		if(hours24 != 12)
			hours24 -=12;
	}
	else //if hours24 < 12
		strncpy(timePeriod, "A.M.", 19);
		//do not alter hour number


	snprintf(output, 29, "%d:%.2d %s", hours24, min, timePeriod);
}

void findClosestFlight(int desiredTime, int *departureTime, int *arrivalTime) {

	//initialization value
	int proximity = abs(desiredTime - departures[0]);
	int flightIndex = 0;

	for(int count = 1; count < sizeof(departures)/sizeof(departures[0]); count++) {

		if( abs(desiredTime - departures[count]) < proximity ) {
			proximity = abs(desiredTime - departures[count]);
			flightIndex = count;
		}
	}

	*departureTime = departures[flightIndex];
	*arrivalTime = arrivals[flightIndex];

}
