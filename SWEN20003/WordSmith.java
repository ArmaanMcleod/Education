import java.util.Scanner;
import java.util.Arrays;

public class WordSmith {
    /* Useful constant defined */
    public static final int MAXCOL = 3;

    public static void main(String[] args) {
        /* Create scanner object */
        Scanner scanner = new Scanner(System.in);

        /* Enter n words */
        System.out.print("Enter n: ");
        int n = scanner.nextInt();
        scanner.nextLine();

        /* Allocate 2D array of strings */
        String[][] data = new String [n][MAXCOL];

        /* Get n inputs from user and perform some computation */
        System.out.println("Enter n lines: ");
        for (int i = 0; i < n; i++) {

            /* Store input */
            String line = scanner.nextLine();

            /* Split words at whitespace */
            String[] words = line.split(" ");

            /* Perform computation */
            String alphaWord = greatestWord(words);

            String longWord = longestWord(words);

            String mostVowels = mostVowelsWord(words);

            /* store words in data structure */
            data[i][0] = alphaWord;
            data[i][1] = mostVowels;
            data[i][2] = longWord;

        }

        /* print the words */
        printWords(data, n, MAXCOL);
    }

    /* Gets the largest word */
    public static String longestWord(String[] words) {
        int maxLength = words[0].length();
        int maxLengthIndex = 0;

        for (int j = 1; j < words.length; j++) {
            if (words[j].length() > maxLength) {
                maxLength = words[j].length();
                maxLengthIndex = j;
            }
        }

        return words[maxLengthIndex];
    }

    /* Gets the alphabetically biggest word */
    public static String greatestWord(String[] words) {
        String maxWord = words[0];
        int greatestIndex = 0, compare;

        for (int j = 1; j < words.length; j++) {
            compare = maxWord.compareTo(words[j]);

            if (compare < 0) {
                maxWord = words[j];
                greatestIndex = j;
            }
        }

        return words[greatestIndex];
    }

    /* Gets the word with most vowels */
    public static String mostVowelsWord(String[] words) {
        int maxVowelCount = 0;
        String mostVowels = null;

        for (String word : words) {
            int vowelCount = 0;
            String temp = word.toLowerCase();

            for (int v = 0; v < word.length(); v++) {
                char x = word.charAt(v);

                if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u') {
                    vowelCount++;
                }
            }

            if (vowelCount > maxVowelCount) {
                maxVowelCount = vowelCount;
                mostVowels = word;
            }
        }

        return mostVowels;
    }

    /* Prints words out */
    public static void printWords(String[][] words, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols-1; j++) {
                System.out.print(words[i][j] + ",");
            }
            System.out.println(words[i][cols-1]);
        }
    }
}