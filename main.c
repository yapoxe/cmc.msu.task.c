/*  
	Файл: main.c
	Студент Никитин Владимир Вадимович, группа 102, преподаватель Смирнов А.В.
	Задание
		Реализовать два метода сортировки массива чисел и провести их экспериментальное сравнение.
	Вариант: 2-2-1-5
	Данные:  64-разрядные целые числа (long long int)
	Вид сортировки: Числа упорядочиваются по невозрастанию (убыванию)
	Методы сортировки: Метод "пузырька", пирамидальная сортировка
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variables
long long int x=0;
int condition=0, movement=0, i=0;					// Переменные, в которые будем записывать кол-во сравнений и перестановок
void CreateArray(int param, int n); 				// Объявление функции, которая создает массив
void BubbleSort(long long int a[], int n); 			// Объявление функции, которая сортирует массив "пузырьком"
void PyramidSort(long long int a[], int n); 		// Объявление функции, которая сортирует массив с помощью пирамидальной сортировки
void RightPyramid(long long int a[], int k, int m); // Объявление функции, которая строит пирамиду из данной

// Main
int main(void) {
	srand(time(NULL)); 								// Будем генерировать случайные числа, в качестве базы установим время
	printf("Parameters:\n");
	printf("1 - Elements are sorted\n");
	printf("2 - Elements are sorted at worst\n");
	printf("3-4 - Elements are sorted randomly\n");
	printf("Example of input: 2 10 \n(2 - sorted at worst, 10 - number of elements)\n");
	printf("Enter parameter and number of elements:\n");
	scanf("%d %d", &condition, &movement);			// Condition и movement используются для оптимизации, потом обнуляются
	printf("\n");
	CreateArray(condition, movement);
	return 0;
}

// Functions
void CreateArray(int param, int n){ 				// Создание массива
	if(n<1){
		printf("ERROR 1: WRONG NUMBER OF ELEMENTS");
		exit(1);		
	}
	long long int *a;
	a=(long long int*)malloc(n*sizeof(long long int));
	switch(param){
		case 1:
			for(i=0; i<n; i++){
				a[i]=10000-i;
			}
			break;
		case 2:
			for(i=0; i<n; i++){
				a[i]=i;
			}
			break;
		case 3: case 4:
			for(i=0; i<n; i++){
				a[i]=rand()*rand()*rand()*rand()*rand();
			}
			break;
		default:
			printf("ERROR 2: PARAM != {1,2,3,4}");
			exit(1);
	}
	PyramidSort(a, n);								// Выбираем нужную сортировку (BubbleSort или PyramidSort)
}

void BubbleSort(long long int a[], int n){ 			// Обычная сортировка "пузырьком", алгоритм понятен интуитивно
	condition=0;
	movement=0;
	printf("---------------------------------------------------------\n");
	printf("Massive A before sort:\n\n");
	for(i=0; i<n; i++){
		printf("%d ", a[i]);
	}
	printf("\n---------------------------------------------------------\n");

	// Сортировка
	int j=0;
	for(i=0; i<n; i++){
		for(j=n-1; j>i; j--){
			++condition;
			if(a[j-1]<a[j]){
				++movement;
				x=a[j-1];
				a[j-1]=a[j];
				a[j]=x;
			}
		}
	}
	x=0;

	printf("\nBubble sort is over");
	printf("\n\n---------------------------------------------------------\n");
	printf("Massive A after sort:\n\n");
	for(i=0; i<n; i++){
		printf("%d ", a[i]);
	}
	printf("\n---------------------------------------------------------\n\n");
	printf("Number of conditions: %d\n", condition);
	printf("Number of movements: %d\n", movement);
	free(a);
	exit(0);
}

void PyramidSort(long long int a[], int n){ 		// Пирамидальная сортировка
	condition=0;
	movement=0;
	printf("---------------------------------------------------------\n");
	printf("Massive A before sort:\n\n");
	for(i=0; i<n; i++){
		printf("%d ", a[i]);
	}
	printf("\n---------------------------------------------------------\n");

	// Сортировка
	for(i=n/2-1; i>=0; i--){
		RightPyramid(a,i,n-1); 						// Построение пирамиды из данного массива
	}
	for(i=n-1; i>0; i--){
		++movement;
		x=a[i]; 
		a[i]=a[0]; 
		a[0]=x; 									// Меняем местами наименьший элемент (высоту пирамиды) и последний, сортируем пирамиду заново
		x=0;
		RightPyramid(a, 0, i-1); 
	}

	printf("\nPyramid sort is over");
	printf("\n\n---------------------------------------------------------\n");
	printf("Massive A after sort:\n\n");
	for(i=0; i<n; i++){
		printf("%d ", a[i]);
	}
	printf("\n---------------------------------------------------------\n\n");
	printf("Number of conditions: %d\n", condition);
	printf("Number of movements: %d\n", movement);
	free(a);
	exit(0);
}

void RightPyramid(long long int a[], int k, int m){ // Построение пирамиды, высота пирамиды - наименьшее значение
	long long int elem;
	elem=a[k];
	while(k<=m/2){
		x=2*k;
		++condition;
		if(x<m && a[x]>a[x+1]){ 
			x++;
		}
		++condition;
		if(elem<=a[x]) break;
		++movement;
		a[k]=a[x];
		k=x;
	}
	a[k]=elem;
	x=0;
}