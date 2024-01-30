import java.util.Random;

public class Intmatrix 
{

    // Function to generate a random integer matrix
    public static int[][] generateRandomIntegerMatrix(int rows, int cols) 
    {
        int[][] matrix = new int[rows][cols];
        Random rand = new Random();
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                matrix[i][j] = rand.nextInt(100); // Adjust range as needed
            }
        }
        return matrix;
    }
    
    //print the matrix;
    public static void printMatrix(int[][] matrix) 
    {
        for (int i = 0; i < matrix.length; i++) 
        {
            for (int j = 0; j < matrix[0].length; j++) 
            {
                System.out.print(matrix[i][j] + "\t");
            }
            System.out.println();
        }
    }

    // Function to multiply two matrices
    public static int[][] multiplyMatrices(int[][] matrix1, int[][] matrix2) 
    {
        int rows1 = matrix1.length;
        int cols1 = matrix1[0].length;
        int rows2 = matrix2.length;
        int cols2 = matrix2[0].length;

        if (cols1 != rows2) 
        {
            throw new IllegalArgumentException("Number of columns in the first matrix must equal the number of rows in the second matrix.");
        }

        int[][] result = new int[rows1][cols2];
        for (int i = 0; i < rows1; i++) 
        {
            for (int j = 0; j < cols2; j++) 
            {
                result[i][j] = 0;
                for (int k = 0; k < cols1; k++) 
                {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return result;
    }

    public static void main(String[] args) 
    {
        // Define matrix dimensions
        int rows1 = 2000;
        int cols1 = 1000;
        int rows2 = 1000; // Adjusted dimensions to make non-square matrices
        int cols2 = 1500;

        // Generate random matrices
        int[][] matrix1 = generateRandomIntegerMatrix(rows1, cols1);
        int[][] matrix2 = generateRandomIntegerMatrix(rows2, cols2);

        // Perform matrix multiplication with timing
        long startTime = System.currentTimeMillis();
        int[][] result = multiplyMatrices(matrix1, matrix2);
        long endTime = System.currentTimeMillis();

        // Calculate elapsed time
        double elapsedTimeInSeconds = (endTime - startTime) / 1000.0;

        // Print result or do other processing
        System.out.println("Matrix multiplication successful!");
        printMatrix(result);
        System.out.println("Time taken: " + elapsedTimeInSeconds + " seconds");
    }
}
