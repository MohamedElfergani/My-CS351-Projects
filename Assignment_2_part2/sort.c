#include <math.h>
#include <stdio.h>

int arr[] = {1, 17, 34, 51, 67};
int n = 5;
int i = 0, j = 0, key = 0;

void sort()
{
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void print()
{
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{
    sort();
    print();
    return 0;
}
