import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

import java.util.Scanner;
import java.util.Arrays;

public class LanguageEstimate {

    /* Key words in each langauge */
    public static final String[] C_PROGRAM = {"#include", "#define", "->", ".h"};
    public static final String[] JAVA_PROGRAM = {"public", "import", "new", "String"};
    public static final String[] PYTHON_PROGRAM = {"dict", "tuple", "#", "import"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String[] keyWordsC = C_PROGRAM;
        String[] keyWordsJava = JAVA_PROGRAM;
        String[] keyWordsPython = PYTHON_PROGRAM;

        /* Get filename from user */
        System.out.print("Input filename: ");
        String filename = scanner.nextLine();

        int programFreqC = 0;
        int programFreqJava = 0;
        int programFreqPython = 0;

        /* read in file */
        try (BufferedReader br =
            new BufferedReader(new FileReader(filename))) {

            String text;

            /* Go through each line in file */
            while ((text = br.readLine()) != null) {

                /* Split each line at each whitespace */
                String[] words = text.split(" ");

                /* Add frequences found */
                programFreqC += checkLanguage(words, keyWordsC);
                programFreqJava += checkLanguage(words, keyWordsJava);
                programFreqPython += checkLanguage(words, keyWordsPython);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        /* Print out results */
        printResults(programFreqC, programFreqJava, programFreqPython, filename);
    }

    /* Method that compares each word with each key */
    /* Returns count */
    public static int checkLanguage(String[] words, String[] keys) {
        int keyWordCount = 0;

        for (String word : words) {
            for (String key : keys) {
                if (word.equals(key)) {
                    keyWordCount++;
                }
            }
        }

        return keyWordCount;
    }

    /* Method that prints out results */
    public static void printResults(int freqC, int freqJava, int freqPython, String filename) {
        if (freqC > freqJava && freqC > freqPython) {
            System.out.format("%s was written in C.\n", filename);
        } else if (freqJava > freqC && freqJava > freqPython) {
            System.out.format("%s was written in Java.\n", filename);
        } else if (freqPython > freqC && freqPython > freqJava) {
            System.out.format("%s was written in Python.\n", filename);
        } else {
            System.out.format("Can't decide what language %s was written in...\n", filename);
        }
    }
}