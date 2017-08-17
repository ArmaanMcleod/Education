import java.util.Scanner;

public class CaeserCipher {

	/* Some useful constants */
	public static final String ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	public static final String END = "Stop";
	public static final String ENCODE = "Encode";
	public static final String DECODE = "Decode";

	public static final int MAX_LETTERS = ALPHABET.length();

	public static void main(String[] args) {
		/* Create scanner object */
		Scanner scanner = new Scanner(System.in);
		        
		System.out.print("Encoding/Decoding? ");

		while (scanner.hasNextLine()) {
			/* Getting direction from user */
			String direction = scanner.nextLine();
			if (direction.equals(END)) {
				break;
			}

			/* Reading in shift from user*/
			System.out.print("Enter n: ");
			int n = scanner.nextInt();
			scanner.nextLine();

			/* Reading in text from user */
			System.out.print("Enter text to convert: ");
			String text = scanner.nextLine();

			/* Replace text with uppercase and no whitespace */
			text = text.replace(" ", "");
			text = text.toUpperCase();
  			
  			/* Performs encoding */
  			if (direction.equals(ENCODE)) {

  				String encoding = "";
  				for (int i = 0; i < text.length(); i++) {
  					int charPosition = ALPHABET.indexOf(text.charAt(i));
  					int keyVal = (n + charPosition) % MAX_LETTERS;
  					char replaceVal = ALPHABET.charAt(keyVal);
  					encoding += replaceVal;
  				}

  				System.out.println(text);
  				System.out.println(encoding);

  			/* Performs decoding */
  			} else if (direction.equals(DECODE)) {

  				String decoding = "";
  				for (int i = 0; i < text.length(); i++) {
  					int charPosition = ALPHABET.indexOf(text.charAt(i));
  					int keyVal = (charPosition - n) % MAX_LETTERS;
  					if (keyVal < 0) {
  						keyVal = ALPHABET.length() + keyVal;
  					}
  					char replaceVal = ALPHABET.charAt(keyVal);
  					decoding += replaceVal;
  				}

  				System.out.println(text);
  				System.out.println(decoding);
  			}

			System.out.print("Encoding/Decoding? ");
		}

	}
}