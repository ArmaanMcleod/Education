import java.util.Scanner;

public class VigenereCipher {

    public static final int N_CHARS = 26;

    public static final String STOP = "stop";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] shifts = new int[N_CHARS];
        char[] alphabet = "abcdefghijklmnopqrstuvwxyz".toCharArray();

        // Keep looping while there is input to read
        while (scanner.hasNextLine()) {

            String input = scanner.nextLine();
            String checker = input;
            if (checker.equals(STOP)) {
                break;
            }

            char letter = input.charAt(0);

            int n = scanner.nextInt();
            scanner.nextLine();

            for (int i = 0; i < alphabet.length; i++) {
                if (alphabet[i] == letter) {
                    shifts[i] = n;
                }
            }
            
        }
        
        //System.out.println(Arrays.toString(shifts));

        System.out.print("Input text to convert: ");
        String text = scanner.nextLine();
            
        // Remove spaces, punctuation and numbers from the text
        text = text.replaceAll("[^a-zA-Z]", "");
            
        // Convert text to upper case for simplicity
        text = text.toUpperCase();
            
        // We're going to build a new String while converting
        String newText = "";
            
        // Now loop through all the characters and perform the shift
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);

            for (int j = 0; j < alphabet.length; j++) {
                char upperChar = Character.toUpperCase(alphabet[j]);
                if (upperChar == c) {
                    newText += (char) ('A' + (c - 'A' + shifts[j]) % N_CHARS);
                }
            }

        }
            
        // Output the original and converted text and start again
        System.out.println(text);
        System.out.println(newText);
            
    }

    public static boolean isStringInt(String s) {
        try {
            Integer.parseInt(s);
            return true;
        } catch (NumberFormatException ex) {
            return false;
        }
    }
}