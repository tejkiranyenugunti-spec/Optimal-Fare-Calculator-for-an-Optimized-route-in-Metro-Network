#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

#define SNo 10 //Number of stations in the metro network, this can be changed according to the requirements


//search utility function to search for the metro stations entered by the user
int search(char source[], char *stations[])
{
int found = -1;

	for(int i = 0 ; i < SNo ; i++)
	{
		if(strcmp(source, stations[i]) ==0)
		{
			found = i;
			break;
		}
	}
	return found;
}


//function to calculate the optimal fare by calculating the least possible distance between the stations using shortest path algorithm
int optimalFareByShortestPath( int network[SNo][SNo], int startStation, int destinationStation)
{
  int distance[SNo]; //this is an array to hold the distance from the start station to all other possible destination stations
  bool Visited[SNo]; // this is an array to keep track of the vertices already visited and distance finalized from source station. Value will be true if already visited, else false
  //Initializing all distances to infinity from the source station
  int minDistance;
  int minStation;
  int currentStation;
  for(int i=0;i<SNo;i++)
  {
    distance[i] = INT_MAX;
  }
//Setting all Stations as unvisited initially
  for(int i =0 ;i <SNo;i++)
  {
    Visited[i] = false;
  }
  distance[startStation] = 0; //Initializing the ditance from Source Station to itself as Zero;

// in this for loop shortest path for all vertices is calculated
  for(int i =0;i< SNo -1; i++)
  {
      minDistance = INT_MAX;

			//this for loop is to determine the next minimum distance station from the set of stations not yet included in the visited set
      for(int j =0; j< SNo; j++)
      {
        if(Visited[j] == false && distance[j] <= minDistance)
        {
          minDistance = distance[j];
          minStation = j;
        }
      }
	// the current station is the minimum distance station not yet checked
  currentStation = minStation;
  Visited[currentStation] = true;  //marking the station as visited


// this for loop is to update the distance values of the neigbouring stations of the current station
  for(int k =0 ; k< SNo; k++)
    {
			//the neigbouring station's distance is updated only if  it is not yet in the visited set, and there is an edge between the two stations and total distance from source station is lesser than the current distance
      if(!Visited[k] && network[currentStation][k] && distance[currentStation]!= INT_MAX && distance[currentStation] + network[currentStation][k] < distance[k])
      {
        distance[k] = distance[currentStation] + network[currentStation][k];
      }
    }
}
 return distance[destinationStation];
}



int optimalFare(char source[], char destination[])
{
	// this function is the main part of the algorithm, where adjacency list and shortest path algorithm will be used to return fare
return 1;
}

int main(){
	char *stations[SNo] = {"Banashankari", "Halasuru", "Trinity", "Rajajinagar", "Vijayanagar", "Dasarahalli", "Giddenhalli", "Chickpete", "Jayanagar","Lalbagh"};

	//an undirected weighted graph to represt that the metros can travel in either direction from one station to another station
	//Zero in the matrix means there is no edge connecting the two Stations, any other number represents the distance in between the two stations which are connected
	int MetroNetwork[SNo][SNo] = {{0,30,10,0,0,0,0,64,0,0}, //Station 0 and its distance to other stations
		{30,0,0,20,0,0,0,64,0,40}, //Station 1 and its distance to other stations
		{10,0,0,0,0,0,0,0,15,0}, //Station 2 and its distance to other stations
		{0,20,0,0,10,0,0,0,0,15}, //Station 3 and its distance to other stations
		{0,0,0,10,0,80,0,64,0,20}, //Station 4 and its distance to other stations
		{0,0,0,0,80,0,6,8,0,0}, //Station 5 and its distance to other stations
		{0,0,0,0,0,6,0,7,25,0}, //Station 6 and its distance to other stations
		{64,0,10,0,0,8,7,0,6,5}, //Station 7 and its distance to other stations
		{0,0,15,0,0,0,25,6,0,0}, //Station 8 and its distance to other stations
		{0,40,0,15,20,0,0,5,0,0}}; //Station 9 and its distance to other stations

	int optimaldistance;
	char source[20]; //string to store source staiton
	char destination[20]; // string to store destination station
	int sourceStationNumber ;
	int destinationStationNumber;
	int found1 = -1;
	int found2 = -1;
	int discount = 10;
	float rate = 2.3 ;// per unit of distance
	float fare; // this is the final optimal fare
	int age; // age of user to determine eligibility of the user;
	bool disabled = false; //this is false by default, if user is disabled it will be set to true
	int disabilityDiscount = 30;
	char disabilityInput[5];
	printf("Welcome to Fare Calculator \n");

	printf("These are the available metro stations \n");
	for(int i=0;i<SNo;i++)
	{
		printf("%s \n", stations[i]);
	}

	do{
	printf("Please enter source station \n");
	scanf("%s", source);
	found1 = search(source,stations);
	if(found1==-1)
		printf("Source station not found \n");
}while(found1==-1);

do{
	printf("Please enter destination station \n");
	scanf("%s", source);
	found2 = search(source,stations);
	if(found2==-1)
		printf("Destination station not found \n");
}while(found2==-1);

sourceStationNumber = found1;
destinationStationNumber = found2;

optimaldistance = optimalFareByShortestPath(MetroNetwork,sourceStationNumber,destinationStationNumber);
printf("Optimal distance:%d \n", optimaldistance);
fare = optimaldistance*rate; // fare is calculated using distance multiplied by standard rate

printf("Are you disabled? Please enter 'Yes' or 'No' \n ");
scanf("%s", disabilityInput);
if(strcmp(disabilityInput,"Yes") ==0)
{
fare = fare - fare*(disabilityDiscount/100); //calculating disability discounted fee discounted fare
printf("You are eligible for a 30 percent discount and your discounted fare is %f \n", fare);
}
else{

	printf("please enter your age \n");
	scanf("%d", &age);
	if(age>60 || age < 10)
	{
		fare = fare - fare*(discount/100); //calculating discounted fare
		printf("You are eligible for a 10 percent discount and your discounted fare is %f \n", fare);
	}
	else
	{
		printf("Your fare is: %f \n", fare);
	}


}
return 0;
}
