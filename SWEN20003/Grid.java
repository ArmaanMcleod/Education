import java.util.Scanner;

public class Grid {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		System.out.print("Enter n: ");
		int n = scanner.nextInt();

		System.out.format("%3c |", '*');
		for (int i = 1; i <= n; i++) {
			System.out.format("%3d |", i);
		}

		System.out.println();

		
	}
}