import java.util.Scanner;

public class MeanAndScary {
	public static void main(String[] args) {
		/* Prompt */
		System.out.println("Enter inputs: ");

		/* Scanner object created */
		Scanner scanner = new Scanner(System.in);

		/* Reading in input */
		String text = scanner.nextLine();
		String leftChar = scanner.nextLine();
		String rightChar = scanner.nextLine();
		String charToRemove = scanner.nextLine();

		int width = scanner.nextInt();

		/* Replacing character in text */
		text = text.replace(charToRemove, "").toUpperCase();
		
		/* Calculating how many spaces available for each side */
		int numSymbol = width - text.length();

		/* determing the correct number of spaces for each side */
		int right = (numSymbol % 2 == 0) ? numSymbol / 2 : (numSymbol / 2) + 1;
		int left = numSymbol / 2;

		/* Formatting text */
		text = String.format("%s%s%s", generatePadding(leftChar, left), 
			                  text, generatePadding(rightChar, right));

		/* Outputting text */
	   	System.out.println(text);
	}

	/* Method used to generate padding */
	/* This method can be considered cheating */
	public static String generatePadding(String paddingCharacter, int num) {
		String padding = "";

		for (int i = 0; i < num; i++) {
			padding += paddingCharacter;
		}

		return padding;
	}
	
}