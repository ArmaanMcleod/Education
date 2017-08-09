import java.util.Scanner;

public class FormatStrings {
	public static void main(String[] args) {
		/* Prompt */
		System.out.println("Enter the currency values: ");

		/* Scanner object */
		Scanner scanner = new Scanner(System.in);

		/* Numeric values */
		int thousands = scanner.nextInt();
		int hundreds = scanner.nextInt();
		int cents = scanner.nextInt();
		int places = scanner.nextInt();

		/* Character values */
		String separator = scanner.nextLine();
		scanner.nextLine();
		String currency = scanner.nextLine();

		/* converting cents to a string */
		String strCents = String.format("%d", cents);

		/* formatting output */
		String output = String.format("%s%03d%s%03d.%s", currency, thousands,
                                      separator, hundreds, 
                                      rightPadZeroes(strCents, places));
        
        System.out.print(output);
	}

	/* helper method to add right padded zeroes */
	public static String rightPadZeroes(String str, int num) {
        return String.format("%1$-" + num + "s", str).replace(' ', '0');
    }
}