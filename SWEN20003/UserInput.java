import java.util.Scanner;

public class UserInput {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);

		System.out.println("Enter name of character from a movie/TV/show/book:");
		String name = scanner.nextLine();

		System.out.println("Enter maximum rating for this character:");
		int maxRating = scanner.nextInt();
		scanner.nextLine();

		System.out.println("Enter rating for this character:");
		double rating = scanner.nextDouble();
		scanner.nextLine();

		System.out.println("Enter comment about this character:");
		String comment = scanner.nextLine();

		System.out.format("You gave %s a rating of %.2f/%d, or %2d%%\n",
						   name, rating, maxRating, (int) (rating/maxRating * 100));
		
		System.out.format("Your comment: %s\n", comment);
	}
}