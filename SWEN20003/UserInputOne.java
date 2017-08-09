import java.util.Scanner;

public class UserInputOne {
	public static void main(String[] args) {
		/* Prompt */
		System.out.println("Enter two numbers: ");

		/* Create Scanner object */
		Scanner scanner = new Scanner(System.in);

		/* Read int integers */
		int firstNumber = scanner.nextInt();
		int secondNumber = scanner.nextInt();

		/* Perform calculations on integers */
		int sum = firstNumber + secondNumber;
		int difference = firstNumber - secondNumber;
		int product = firstNumber * secondNumber;
		int quotient = firstNumber / secondNumber;
		int remainder = firstNumber % secondNumber;

		/* Print out calculations */
		System.out.println(sum);
		System.out.println(difference);
		System.out.println(product);
		System.out.println(quotient);
		System.out.println(remainder);
	}
}