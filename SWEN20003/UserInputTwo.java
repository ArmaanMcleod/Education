import java.util.Scanner;

public class UserInputTwo {
	public static void main(String[] args) {
		/* Delimeter needed to find first word */
		final String SEPARATOR = " ";

		/* Create prompt */
		System.out.print("Enter some text: ");

		/* Create scanner object */
		Scanner scanner = new Scanner(System.in);

		/* Extract line */
		String line = scanner.nextLine();

		/* Print out line length */
		System.out.println(line.length());

		/* Obtain index where first word ends */
		int index = line.indexOf(SEPARATOR);

		/* Extract first word */
		String firstWord = line.substring(0, index);

		/* Move down string */
		line = line.substring(index + 1);

		/* Output first word and rest of string */
		System.out.println(firstWord);
		System.out.println(line);
	}
}