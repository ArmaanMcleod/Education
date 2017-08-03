import java.util.Scanner;

public class Command {
	public static void main(String args[]) {
		args = new String[]{"Hello", "10", "World"};

		/* Uppercase first arguement*/
		System.out.println(args[0].toUpperCase());

		/* middle character third arguement*/
		int length = args[2].length()/2;
		System.out.println(args[2].substring(length, length+1));
		// or args[2].charAt(length);

		/* double conversion of second arguement */
		double num = Double.parseDouble(args[1]);
		System.out.format("%-8.4f\n", num);
	}
}