import java.util.Scanner;

public class Reverse {
	public static void main(String[] args) {

		/* Create scanner object */
		Scanner scanner = new Scanner(System.in);

        /* Read in input */
		String input = scanner.nextLine();
        
        /* Get length of input */
		int length = input.length();

        /* reverse string */
		String reversed = "";
		for (int i = length-1; i >= 0; i--) {
			reversed += input.charAt(i);
		}

		System.out.println(reversed);
	}
}