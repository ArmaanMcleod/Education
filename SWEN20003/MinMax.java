import java.util.Scanner;

public class MinMax {
	public static void main(String[] args) {
		/* Created scanner object */
		Scanner scanner = new Scanner(System.in);

		int number = 0, count = 0;
        
        /* Initialised max and min values */
        int max = Integer.MIN_VALUE, min = Integer.MAX_VALUE;
        
        /* Flag to check if no numbers were entered */
		boolean noNumber = false;

		System.out.print("Input a number: ");

		/* Reads until ctrl-d is entered */
		while (scanner.hasNextLine()) {
			noNumber = false;
			String input = scanner.nextLine();

			/* Checks if input is a valid integer */
			if (!isInteger(input)) {
				noNumber = (count == 0) ? true : false;
				break;
			}

			/* If weve gotten this far, a valid integer has been read */
			number = Integer.parseInt(input);
			count++;

			/* updating max and min if necessary */
			if (number > max) {
				max = number;
			}

			if (number < min) {
				min = number;
			}

			System.out.print("Input a number: ");
		}

		/* deciding what to print at the end */
		if (noNumber || count == 0) {
			System.out.println("No numbers entered.");
		} else {
			System.out.println("Min number: " + min);
			System.out.println("Max number: " + max);
		}

	}

	/* helper function to determine if input is an integer */
	public static boolean isInteger(String input) {
        try {
            Integer.parseInt(input);
             return true;
        } catch(Exception e) {
             return false;
        }
    }
}