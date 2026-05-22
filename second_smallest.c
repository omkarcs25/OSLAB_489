#include <stdio.h>

int main() {
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int smallest, secondSmallest;

    // Assume first two elements
    if(arr[0] < arr[1]) {
        smallest = arr[0];
        secondSmallest = arr[1];
    } else {
        smallest = arr[1];
        secondSmallest = arr[0];
    }

    // Find second smallest
    for(i = 2; i < n; i++) {
        if(arr[i] < smallest) {
            secondSmallest = smallest;
            smallest = arr[i];
        } else if(arr[i] < secondSmallest && arr[i] != smallest) {
            secondSmallest = arr[i];
        }
    }

    printf("Second smallest element = %d\n", secondSmallest);

    return 0;
}
