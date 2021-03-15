#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Meal{
	int point;
	char name[50];
};

int is_in_list(char* name, struct Meal array[], int size){
	for(int i=0; i<size; i++){
		if(array[i].point == 0)
			break;
		if(strcmp(array[i].name, name) == 0)
			return i;
	}
	return -1;
}

int find_final_meal_index(struct Meal array[], int size){
	int biggestPoint = 0;
	int index = 0;
	
	for(int i=0; i<size; i++){
		if(array[i].point == 0)
			break;
		if(array[i].point > biggestPoint){
			biggestPoint = array[i].point;
			index = i;
		}
	}
	return index;
}

int locationTracker = 0;
void init_meals(struct Meal m, struct Meal array[], int numberOfGuests){
	if(is_in_list(m.name, array, numberOfGuests*5) != -1)
		array[is_in_list(m.name, array, numberOfGuests*5)].point += m.point;
	else if(is_in_list(m.name, array, numberOfGuests*5) == -1){
		array[locationTracker].point = m.point;
		strcpy(array[locationTracker].name, m.name);
		locationTracker += 1;
	}	
}

int main() {
	const int numberOfMeals = 5;
	const int threshHold = 8;
	int numberOfGuests = 0;
	int foundBiggerThanTrashHold = 0;

	printf("Welcome to What2Eat program!\nHow many guests do I have? \n");
	scanf("%d", &numberOfGuests);
	
	struct Meal pointsOfMeals[numberOfGuests*5];
	struct Meal pointsOfMealsAboveThresh[numberOfGuests*5];
	struct Meal finalList[numberOfGuests*5];
	
	printf("First step: \n");
	for(int i=0; i<numberOfGuests; i++){
		printf("Could %d. user enter their five choices in order of their preferences (most preferred to least preferred) \n", i+1);
		
		struct Meal m1;
		struct Meal m2;
		struct Meal m3;
		struct Meal m4;
		struct Meal m5;
		
		scanf("%s %s %s %s %s", m1.name, m2.name, m3.name, m4.name, m5.name);

		m1.point = 5;
		m2.point = 4;
		m3.point = 3;
		m4.point = 2;
		m5.point = 1;	
		
		init_meals(m1, pointsOfMeals, numberOfGuests*5);
		init_meals(m2, pointsOfMeals, numberOfGuests*5);
		init_meals(m3, pointsOfMeals, numberOfGuests*5);
		init_meals(m4, pointsOfMeals, numberOfGuests*5);
		init_meals(m5, pointsOfMeals, numberOfGuests*5);
	}
	
	for(int i=locationTracker; i<numberOfGuests*5; i++){
		pointsOfMeals[i].point = 0;
	}
	
	locationTracker = 0;
	printf("List of the meals with a point bigger than %d: \n", threshHold);	
	for(int i=0; i<numberOfGuests*5; i++){
		if(pointsOfMeals[i].point >= threshHold){
			foundBiggerThanTrashHold = 1;
			printf("%s : %d \n", pointsOfMeals[i].name, pointsOfMeals[i].point);
			pointsOfMealsAboveThresh[locationTracker] = pointsOfMeals[i];
			locationTracker += 1;
		}	
	}
	
	for(int i=locationTracker; i<numberOfGuests*5; i++){
		pointsOfMealsAboveThresh[i].point = 0;
	}
	
	locationTracker = 0;
	if(foundBiggerThanTrashHold == 0)
		printf("You are eating at home/dorm today! \n");
	else{
		printf("Second step: \n");
		if(sizeof(pointsOfMealsAboveThresh) == 1)
			printf("%s is the only meal in the list and will be ordered.", pointsOfMealsAboveThresh[0].name);
		
		for(int i=0; i<numberOfGuests; i++){
			printf("Could %d. user enter their choice from the final list \n", i+1);
			
			struct Meal m6;
			scanf("%s", m6.name);
			m6.point = pointsOfMealsAboveThresh[is_in_list(m6.name, pointsOfMealsAboveThresh, numberOfGuests*5)].point;
			init_meals(m6, finalList, numberOfGuests*5);	
		}
		
		for(int i=locationTracker; i<numberOfGuests*5; i++)
			finalList[i].point = 0;
		
		char* finalMeal = finalList[find_final_meal_index(finalList, numberOfGuests*5)].name;
		printf("Winner meal is %s \n", finalMeal);
	}
	return 0;
}






























