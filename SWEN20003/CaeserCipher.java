import java.util.Scanner;

public class CaeserCipher {

  /* Constants used in program */
	public static final String ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	public static final String END = "Stop";
	public static final String ENCODE = "Encode";
	public static final String DECODE = "Decode";

	public static final int MAX_LETTERS = ALPHABET.length();

	public static void main(String[] args) {

        /* Created scanner object for reading input */
		Scanner scanner = new Scanner(System.in);

		System.out.print("Encoding/Decoding? ");

        /* Reads input until CTRL-D is entered */
		while (scanner.hasNextLine()) {

            /* Reads in direction */
			String direction = scanner.nextLine();
			if (direction.equals(END)) {
				break;
			}

            /* Reads in number of shifts needed for decoding/encoding */
			System.out.print("Enter n: ");
			int n = scanner.nextInt();
			scanner.nextLine();

            /* Reads in text to encode/decode */
			System.out.print("Enter text to convert: ");
			String text = scanner.nextLine();

            /* Converts text to all uppercase and whitespace is stripped */
			text = text.replace(" ", "");
			text = text.toUpperCase();
  			
            /* If encoding is needed */
  			if (direction.equals(ENCODE)) {

                /* Appends new encoded characters to a new buffer */
  				String encoding = "";
  				for (int i = 0; i < text.length(); i++) {
  					int charPosition = ALPHABET.indexOf(text.charAt(i));
  					int keyVal = (n + charPosition) % MAX_LETTERS;
  					char replaceVal = ALPHABET.charAt(keyVal);
  					encoding += replaceVal;
  				}

  				System.out.println(text);
  				System.out.println(encoding);

            /* If decoding is needed */
  			} else if (direction.equals(DECODE)) {

                /* Appends new decoded characters to a new buffer */
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