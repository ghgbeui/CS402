import java.util.Random;

public class doublematrix 
{

    // Function to generate a random double matrix
    public static double[][] generateRandomDoubleMatrix(int rows, int cols) 
    {
        double[][] matrix = new double[rows][cols];
        Random rand = new Random();
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                matrix[i][j] = rand.nextDouble() * 100.0; // Adjust range as needed
            }
        }
        return matrix;
    }
    //Print the matrix;
    public static void printMatrix(double[][] matrix) 
    {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) 
            {
                System.out.print(matrix[i][j] + "\t");
            }
            System.out.println();
        }
    }

    // Function to multiply two double matrices
    public static double[][] multiplyDoubleMatrices(double[][] matrix1, double[][] matrix2) 
    {
        int rows1 = matrix1.length;
        int cols1 = matrix1[0].length;
        int rows2 = matrix2.length;
        int cols2 = matrix2[0].length;

        if (cols1 != rows2) 
        {
            throw new IllegalArgumentException("Number of columns in the first matrix must equal the number of rows in the second matrix.");
        }

        double[][] result = new double[rows1][cols2];
        for (int i = 0; i < rows1; i++) 
        {
            for (int j = 0; j < cols2; j++) 
            {
                result[i][j] = 0.0;
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
        double[][] matrix1 = generateRandomDoubleMatrix(rows1, cols1);
        double[][] matrix2 = generateRandomDoubleMatrix(rows2, cols2);

        // Perform matrix multiplication with timing
        long startTime = System.currentTimeMillis();
        double[][] result = multiplyDoubleMatrices(matrix1, matrix2);
        long endTime = System.currentTimeMillis();

        // Calculate elapsed time
        double elapsedTimeInSeconds = (endTime - startTime) / 1000.0;

        // Print result or do other processing
        printMatrix(result);
        System.out.println("Time taken: " + elapsedTimeInSeconds + " seconds");
    }
}

