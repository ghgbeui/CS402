#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readfile.h"

#define INITIAL_CAPACITY 20

int read_data(const char *filename, float** data, int* size, int* capacity)
// read the file, and store into dynamically array called data.
{
    if (open_file(filename) != 0)
    {
        printf("Error: Unable to open file '%s'\n", filename);
        return -1;
    }

    *data = (float *)malloc(INITIAL_CAPACITY * sizeof(float));

    if (*data == NULL) 
    {
        printf("Error: Memory allocation failed\n");
        close_file();
        return -1;
    }

    float value;
    while (read_float(&value) == 0) 
    {
        value = roundf(value * 10000.0) / 10000.0;
        // Check if the array is full, reallocate if necessary
        if (*size == *capacity) 
        {
            *capacity *= 2;
            float *temp = realloc(*data, *capacity * sizeof(float));
            if (temp == NULL) 
            {
                printf("Error: Memory reallocation failed\n");
                free(*data);
                close_file();
                return -1;
            }
            *data = temp;
        }
        // Store the value in the array
        (*data)[(*size)++] = value;
    }
    close_file();
    return 0;
}

void mean(float** data, int* size)
{
    float temp = 0.0;
    for(int i=0;i<*size;i++)
    {
        temp += *(*data + i);
    }
    temp = temp/(*size);
    printf("Mean: %.3f\n", temp);
}

void median(float** data, int* size)
{
    int even = 0;
    float temp=0.0;
    float mid_vale=0.0;

    for (int i = 0; i < *size-1; i++) 
    {
        for (int j = 0; j < *size-i-1; j++) 
        {
            if ((*data)[j] > (*data)[j+1]) 
            {
                float temp = (*data)[j];
                (*data)[j] = (*data)[j+1];
                (*data)[j+1] = temp;
            }
        }
    }

    if((*size%2)==0)
    {
        even = 1;
    }

    if(even)
    {
        int mid = (*size)/2;
        mid_vale = ((*data)[mid-1] + (*data)[mid])/2.0;
    }
    else
    {
        int mid = (*size)/2;
        mid_vale = (*data)[mid];
    }

    printf("The median is: %.3f\n", mid_vale);
}

void stddev(float** data, int* size)
{
    float temp = 0.0;
    for(int i=0;i<*size;i++)
    {
        temp += *(*data + i); 
    }
    temp = temp/(*size);

    float value = 0.0;

    for(int i=0; i<*size;i++)
    {
        float sub = (*data)[i] - temp;
        value += sub * sub;
    }

    float variance = value / *size;

    //Calculate the standard deviation
    float std = sqrt(variance);

    printf("The stddev is: %.3f\n", std);
}

void mode(float** data, int* size)
{
    float max = 0.0;
    int max_count=0;

    for(int i=0;i<*size;i++)
    {
        float current = (*data)[i];
        int current_count = 1; // Initialize count for the current value

        // Count occurrences of the current value in the remaining elements
        for (int j = i + 1; j < *size; j++)
        {
            if ((*data)[j] == current)
            {
                current_count++;
            }
        }
        if(current_count>max_count)
        {
            max_count = current_count;
            max = current;
        }
    }
    printf("Mode: %.3f\n", max);
}

// Helper function to calculate power (x^exp)
float power(float x, int exp) {
    float result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= x;
    }
    return result;
}

// Calculate the nth root using Newton's method
float nthRoot(float number, int n) {
    // Initial guess for the nth root
    float x = number / 2.0; // You can choose a better initial guess if needed

    // Iterate until convergence
    while (1) { // using true
        float prevX = x;
        // Newton's method iteration
        x = ((n - 1) * x + number / power(x, n - 1)) / n;
        // Check for convergence
        if (x == prevX) {
            break;
        }
    }

    return x;
}

// Calculate the geometric mean of an array
float GeometricMean(float* data, int size) {
    float product = 1.0;

    // Calculate the product of the nth powers of the data elements
    for (int i = 0; i < size; i++) {
        product *= data[i];
    }

    // If the product is 0, the geometric mean is also 0
    if (product == 0.0) {
        return 0.0;
    }

    // Calculate the nth root directly from the product of nth powers
    return nthRoot(product, size);
}

float HarmonicMean(float* data, int size)
{
    float reciprocal_sum = 0.0;
    for (int i = 0; i < size; i++) {
        reciprocal_sum += 1.0 / data[i];
    }
    return size / reciprocal_sum;
}

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    float* data = NULL;
    int size=0;
    int capacity=INITIAL_CAPACITY;

    const char *filename = argv[1];
    read_data(filename, &data, &size, &capacity);
    
    printf("Results:\n--------------\n");
    printf("Num values: %d\n", size); 
    mean(&data, &size);
    median(&data, &size);
    stddev(&data, &size);
    mode(&data, &size);
    float geo_mean = GeometricMean(data, size);
    printf("Geometric Mean: %.3f\n", geo_mean);
    float harm_mean = HarmonicMean(data, size);
    printf("Harmonic Mean: %.3f\n", harm_mean);

    int unuesd = 0;
    unuesd = capacity-size;
    printf("Unused array capacity: %d\n", unuesd);

    free(data);
    return 0;
}