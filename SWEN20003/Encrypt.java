import java.util.Scanner;

public class Encrypt {
	public static void main(String[] args) {
		String text = "True or False:\n" + 
            "1. Neville Longbottom was the true hero of Hogwarts\n" +
            "2. J.K. Rowling is a monster for killing Lupin and Tonks\n" +
            "3. Dumbledore was one screwed up dude";
        
        /* convert all letters to lower case */
        text = text.toLowerCase();

        /* copy text */
        String copyText = new String(text);

        /* replace everything other than letters with whitespace*/
        text = text.replaceAll("[^a-z]", "");

        /* get length of original string */
        int length = text.length();
        
        /* get first, middle and last characters */
        char first = text.charAt(0);
        char middle = text.charAt(length/2);
        char last = text.charAt(length-1);
        
        /* replace the relevant characters in the copied string */
        copyText = copyText.replace(first, (char)('z' - (first - 'a')));
        copyText = copyText.replace(middle, (char)('z' - (middle - 'a')));
        copyText = copyText.replace(last, (char)('z' - (last - 'a')));

        /* add quotation marks to string */
        copyText = String.format("\"%s\"", copyText);

        System.out.println(copyText);
    }
}					