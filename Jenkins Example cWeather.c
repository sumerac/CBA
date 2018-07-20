#include "common.h"

#include "weather.h"

#include <stdio.h>

#include <stdbool.h>

#include <time.h>



static int wIndex=-1;



bool isFull()

{

  return wIndex >= max_number_of_cities;

}



extern int cityCount;



void addNewRecord(struct weather* wArray,const char* city,double tval, double hval, double pval)

{

  if(isFull())

    fprintf(stderr,"List is full\n");



  wIndex++;

  strcpy(wArray[wIndex].cityName,city);

  wArray[wIndex].temperature.reading=tval;

  wArray[wIndex].humidity.reading=hval;

  wArray[wIndex].pressure.reading=pval;

  wArray[wIndex].tstamp=time(NULL);

  cityCount=wIndex;

  //display(wArray+wIndex);

  //pLastEntry=wArray+index;	//&wArray[index];

}

void display(const struct weather* wEntry)

{

  printf("city=%s\n",wEntry->cityName);

  //printf("time=%s\n",ctime(&wEntry->tstamp));

  printf("temperature=%lf,humidity=%lf,pressure=%lf\n",

          wEntry->temperature.reading, wEntry->humidity.reading,wEntry->pressure.reading);

}

void displayAll(const struct weather* wArray)

{

  const struct weather* pCursor=wArray;

  for(int i=0;i<=wIndex;i++)

  {

    display(pCursor);

    pCursor++;

  }

}

void findByCityName(const struct weather* wArray, const char* city)  //come with alternative logic

{

  int i;

  const struct weather* pCursor=wArray;

  while(i <= cityCount && pCursor->cityName != city)   //importance of order	//pCursor!=pLastEntry

  {

    pCursor++;

    i++;

  }

  if(i <= cityCount)

    display(pCursor);

}

double findAverageTemperature(const struct weather* wArray)

{

  const struct weather* pCursor=wArray;

  double sum=0;

  for(int i=0;i<cityCount;i++)

    sum+=pCursor->temperature.reading;

  return sum/cityCount;



}

double findMinimumHumidity(const struct weather* wArray)

{

  double minValue=wArray[0].humidity.reading;	//wArray->humidity.reading

  const struct weather* pCursor=wArray+1;

  for(int i=1;i<cityCount;i++)

     if(pCursor->humidity.reading < minValue)

     {

	minValue=pCursor->humidity.reading;

        pCursor++;

     }

  return minValue;

}

double findMaximumPressure(const struct weather* wArray)

{

  double maxValue=wArray[0].pressure.reading;	//wArray->humidity.reading

  const struct weather* pCursor=wArray+1;

  for(int i=1;i<cityCount;i++)

     if(pCursor->pressure.reading > maxValue)

	maxValue=pCursor->pressure.reading;

  return maxValue;

}
