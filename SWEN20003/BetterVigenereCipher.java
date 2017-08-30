import grok.Input;

public class Program {
        
    public static final int N_CHARS = 26;
    
    public static final String STOP_COMMAND = "STOP";

    public static void main(String[] args) {
        
        int[] shiftValues = getShiftValues();
            
        System.out.print("Input text to convert: ");
        String text = Input.readLine();

        // Remove spaces, punctuation and numbers from the text
        text = text.replaceAll("[^a-zA-Z]", "");

        // Convert text to upper case for simplicity
        text = text.toUpperCase();

        // We're going to build a new String while converting
        String newText = encodeText(text, shiftValues);

        // Output the original and converted text and start again
        System.out.println(text);
        System.out.println(newText);
            
    }
    
    public static int charToIndex(char c) {
        return c - 'A';
    }
    
    public static int[] getShiftValues() {
        
        int[] shiftValues = new int[N_CHARS];
        
        // Assume there is always input at this stage
        while (true) {
            
            String input = Input.readLine().toUpperCase();
            
            // Break the iteration if the stop command was entered
            if (input.equals(STOP_COMMAND)) {
                break;
            }
            
            // Otherwise, the input was a character, so compute its index
            int index = charToIndex(input.charAt(0));
            
            // Then get the shift value for that character
            shiftValues[index] = Integer.parseInt(Input.readLine());
            
        }
        
        return shiftValues;
        
    }
    
    public static char encodeCharacter(char c, int[] shiftValues) {
        int index = charToIndex(c);
        return (char) ('A' + (c - 'A' + shiftValues[index])%N_CHARS);
    }
    
    public static String encodeText(String text, int[] shiftValues) {
        String newText = "";
        
        // Loop through all the characters and perform the shift
        for (int i = 0; i < text.length(); i++) {
            // Compute the new character
            newText += encodeCharacter(text.charAt(i), shiftValues);
        }
        
        return newText;
    }
}