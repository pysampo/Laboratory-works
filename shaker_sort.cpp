#include <stdio.h>
#define p printf
#define s scanf
void scanf_array(int a[], int size);
void printf_array(int a[], int  size);
void bubble(int a[], int size);
void bubble_version_2(int a[], int size);
void bubble_version_3(int a[], int size);
void rand_for_version_1_2(int a[], int size);

int const N = 25;
int main(void)
{
	int size;
	p("Enter your size: ");
	p("__\b\b");
	s("%d", &size);
	int version_1[N];
	rand_for_version_1_2(version_1, size);
	int version_2[N];
	rand_for_version_1_2(version_2, size);
	int list[N];
	p("Bubble Sort Level 1:\n");
	printf_array(version_1, size);
	bubble(version_1, size);
	printf_array(version_1, size);

	p("\n");
	p("Bubble Sort Level 2:\n");
	printf_array(version_2, size);
	bubble_version_2(version_2, size);
	printf_array(version_2, size);
	
	
	p("\nEnter Your Numbers for Last Sort (By Youself): \n");
	scanf_array(list, size);
	p("Your list:\n");
	printf_array(list, size);
	printf("Bubble Sort Level third:\n");
	bubble_version_3(list, size);
	printf_array(list, size);

}

void scanf_array(int a[], int size)
{	
	for(int i = 0; i < size; i++)
		s("%d", &a[i]);
}
void printf_array(int a[], int size)
{	
	p("[ ");
	for(int i = 0; i < size; i++)
		p("%d ", a[i]);
	p("]\n");
}
void rand_for_version_1_2(int a[], int size)

{
	for(int i = 0; i < size; i++)
		a[i] = rand() % 10;

}
void bubble(int a[], int size)
{
	int N = size - 1;
	int b;
	for(int i = N; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{
			if(a[j] > a[j+1]){
				b = a[j];
				a[j] = a[j+1];
				a[j+1] = b;
			}
		}
	}
}
void bubble_version_2(int a[], int size)
{	int R = 0;
	int Rt = size - 1;
	int b;
	while(R != Rt)
	{	
		R = Rt;
		for(int i = 0; i < R; i++)
		{
			if(a[i] > a[i+1])
			{	b = a[i];
				a[i] = a[i+1];
				a[i+1] = b;
				Rt = i;
			}
		}
	}	
}
void bubble_version_3(int a[], int size)
{
	int Lt = 0;
	int R = 0;
	int L  = size - 1;
	int Rt = size - 1;
	int b, c;
	while((R != Rt) && (L != Lt))
	{	
		R = Rt;
		for(int i = Lt; i < R; i++)
		{
			if(a[i] > a[i+1])
			{	b = a[i];
				a[i] = a[i+1];
				a[i+1] = b;
				Rt = i;
			}
		}
			if (R != Rt)
			{
				L = Lt;
				for(int i = Rt; i > L ; i--)
					if(a[i] < a[i - 1])
						{	c = a[i];
							a[i] = a[i-1];
							a[i-1] = c;
							Lt = i;
						}		
			}
		

	}
}
