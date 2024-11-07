#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readfile.h"

#define INITIAL_CAPACITY 20

float custom_round(float value) 
{
    return (value >= 0) ? (int)(value + 0.5f) : (int)(value - 0.5f);
}

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
        value = custom_round(value * 10000.0) / 10000.0;
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

void min(float** data, int* size)
{
    float temp = (*data)[0];
    for(int i = 0; i< *size; i++)
    {
        if(temp > (*data)[i])
        {
            temp = (*data)[i];
        }
    }
    printf("Min: %.3f\n", temp);
}

void max(float** data, int* size)
{
    float temp = 0.0;
    for(int i = 0; i< *size; i++)
    {
        if(temp < (*data)[i])
        {
            temp = (*data)[i];
        }
    }
    printf("Max: %.3f\n", temp);
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

    printf("median: %.3f\n", mid_vale);
}

void stddev(float* data, int size)  
{
    float mean = 0.0;
    for(int i = 0; i < size; i++)
    {
        mean += data[i];
    }
    mean /= size;

    float value = 0.0;
    for(int i = 0; i < size; i++)
    {
        float sub = data[i] - mean;
        value += sub * sub;
    }

    float variance = value / size;

    // Calculate the standard deviation
    float std = sqrt(variance);

    printf("stddev: %.3f\n", std);
}


void sum(float** data, int* size)
{
    float temp = 0.0;

    for(int i = 0; i<*size;i++)
    {
        temp += (*data)[i];
    }

    printf("Sum: %.3f\n", temp);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    float* data = NULL;
    int size = 0;
    int capacity = INITIAL_CAPACITY;

    const char *filename = argv[1];
    read_data(filename, &data, &size, &capacity);

    // Calculate the size of the array after reading the data
    int n = size;

    printf("Results:\n--------------\n");
    printf("Num values: %d\n", size); 
    
    min(&data, &size);
    max(&data, &size);
    mean(&data, &size);
    median(&data, &size);
    stddev(data, size);
    sum(&data, &size);

    int unused = 0;
    unused = capacity - size;
    printf("Unused array capacity: %d\n", unused);

    free(data);
    return 0;
}
