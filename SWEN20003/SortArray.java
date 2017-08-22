import java.util.Scanner;
import java.util.Arrays;

public class SortArray {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        /* Reading in n */
        System.out.print("Enter n: ");
        int n = scanner.nextInt();
        
        /* Allocate array */
        int[] numbers = new int[n];
        
        /* Assign numbers to array */
        System.out.println("Enter n more numbers: ");
        for (int i = 0; i < n; i++) {
            int number = scanner.nextInt();
            numbers[i] = number;
        }
        
        /* Print unsorted array */
        System.out.println(Arrays.toString(numbers));
        
        /* Print sorted array */
        Arrays.sort(numbers);
        
        /* Print sorted array */
        System.out.println(Arrays.toString(numbers));
        
    }
}