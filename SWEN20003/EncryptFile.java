import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

import java.util.Scanner;
import java.util.Arrays;

public class EncryptFile {

    public static final int N_CHARS = 26;
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        /* Create an array */
        int[] shiftValues = new int[N_CHARS];

        /* Read in inputs */
        System.out.print("Input name of shift file: ");
        String shiftFile = scanner.nextLine();

        System.out.print("Input name of input file: ");
        String inputFile = scanner.nextLine();

        System.out.print("Input name of output file: ");
        String outputFile = scanner.nextLine();

        // Open the files
        try (BufferedReader shifts = 
                 new BufferedReader(new FileReader(shiftFile));
             BufferedReader input = 
                 new BufferedReader(new FileReader(inputFile));
            PrintWriter output = new PrintWriter(new FileWriter(outputFile))) {

            String text = null;
            char currentLetter = 0; 

            /* Read in shift values */
            System.out.println("Collecting shift values.");
            while ((text = shifts.readLine()) != null) {

                if (!isStringInt(text)) {
                    text = text.toUpperCase();
                    currentLetter = text.charAt(0);
                } else {
                    int index = currentLetter - 'A';
                    shiftValues[index] = Integer.parseInt(text);
                }
            }

            /* Build a new string */
            StringBuilder sb = new StringBuilder();
            while ((text = input.readLine()) != null) {
                sb.append(text).append("\n");
            }

            String fileAsString = sb.toString();

            /* Format String */
            fileAsString = fileAsString.trim();
            fileAsString = fileAsString.toUpperCase();

            for (int i = 0; i < fileAsString.length(); i++) {
                currentLetter = fileAsString.charAt(i);
                if (currentLetter == ' ') {
                    fileAsString = fileAsString.replace(Character.toString(currentLetter), "");
                } else if (currentLetter != '\n') {
                    if (!Character.isLetter(currentLetter)) {
                        fileAsString = fileAsString.replace(Character.toString(currentLetter), "");
                    }
                }
            }

            System.out.println("Shift values input.");

            String encodedText = "";
            for (int i = 0; i < fileAsString.length(); i++) {
                currentLetter = fileAsString.charAt(i);
                if (currentLetter == '\n') {
                    encodedText += "\n";
                } else {
                    int index = currentLetter - 'A';
                    encodedText += (char) ('A' + (currentLetter - 'A' + shiftValues[index])%N_CHARS);
                }
            }

            System.out.println("Encrypting document.");

            /* Write to file */
            output.println(encodedText);

            System.out.println("Encryption complete.");
                
        } catch (Exception e) {
            e.printStackTrace();
        }
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