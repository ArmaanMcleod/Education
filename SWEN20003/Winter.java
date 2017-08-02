/* class used to find middle word of Game of Thrones text */
/* compiled with javac Winter.java && java Winter */

public class Winter {

	/* main method, every method gets called here */
	public static void main(String args[]) {
		String text = "Winter is Coming!";
		String middle, upper;
		String[] words;

		/* splitting the text */
		words = splitString(text);

		/* calling first method */
		methodOne(words);
	}

	/* method used to split a string by whitespace */
	public static String[] splitString(String text) {
		String[] splitted;

		splitted = text.split(" ");

		return splitted;
	}

	/* method used to format string */
	public static String formattedUpper(String word) {
		String format;

		format = String.format("\"%s\"", word);
		format = format.toUpperCase();

		return format;
	}

	/* first attempted method */
	public static void methodOne(String[] words) {
		String middle, upper;

		middle = formattedUpper(words[(words.length - 1) / 2]);

		System.out.println(middle);
	}
}