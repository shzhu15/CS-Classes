#include <stdio.h>
#include <stdlib.h>

/**
 * Compares two numbers and returns a positive integer, 0 or
 * a negative integer if the first number is greater than, equal to
 * or less than the second number.
 * Assumes the numbers are of the type int.
 * Used when invoking the quicksort function.
 */
int compare (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}


/**
 * Takes in an array of integers and the number of elements in the array
 * as arguments.
 * Then it will sort and return the median of the sorted array.
 * To keep things simple, it always returns
 * the element at index arr_size/2 even though the
 * array size is even.
 */
int return_median(int *arr, int size)
{
   qsort(arr, size, sizeof(int), compare);
   return arr[size/2];
}


/**
 * Takes in a random number and maps it to the
 * range [100000 - 120000)
 */
int get_iteration_count(int rand)
{
    return (rand % 20000) + 100000;
}

/**
 * Takes in a random number and maps it to the
 * range [1000 - 1500)
 */
int get_arr_size(int rand)
{
    return (rand % 500) + 1000;
}


/**
 * This is the method that you need to implement.
 * Implement the following steps in the given order.
 *
 *  1. Generate the number of iterations
 *      - Generate a random number. Map it to the range [100000 - 120000) using the
 *      utility function 'get_iteration_count'.
 *
 * 2. For each iteration:
 *      2.a Generate an array size - Generate a random number and map it to the range [1000 - 1500) using
 *          the utility function 'get_arr_size'.
 *
 *      2.b Allocate memory for the array in the heap.
 *
 *      2.c Populate the array with random numbers.
 *
 *      2.d Get the median of the array using the function 'return_median'.
 *
 *      2.e Check if the median is divisible by 13.
 *
 *      2.f Return the number of medians that were divisible by 13.
 *
 */
int get_running_count()
{
    // TODO: Implement this method.
    //getting the number of iterations
    int iterations = get_iteration_count(rand());
    int count = 0;                                          //count is the variable to keep track of divisble
    //For loop for the iterations
    for(int n = 0; n < iterations; n++) {
      int arraysize = get_arr_size(rand());                 //getting array size
      int *generator = malloc(arraysize * sizeof(int));     //allocation of the array
      for(int i = 0; i< arraysize; i++) {                   //for loop to put numbers in the array
        generator[i] = rand();
      }
      int median = return_median(generator, arraysize);     //getting the median so it can test for divisble
      free(generator);                                      //deallocation of the array or freeing the array
      //Checking if divisible by 13 with two tests of the same method
      int lastDigit = median % 10;
      int firstTest = 0;
      int secondTest = 0;
      lastDigit = lastDigit * 4;
      median = median / 10;
      firstTest = median + lastDigit;
      lastDigit = firstTest % 10;
      lastDigit = lastDigit * 4;
      secondTest = firstTest / 10;
      secondTest = secondTest + lastDigit;
      if(firstTest % 13 == 0 && secondTest % 13 == 0) {
        count++;
      }
    }

    printf("[MemoryManager] Number of Iterations: %d\n", iterations);
    return count;
}
