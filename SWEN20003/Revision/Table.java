import java.util.Scanner;

public class Table {
    private static final COL_SEPERATOR = "|";
    private static final ROW_SEPERATOR = "----";
    private static final INTERSECTION = "+";
    private static final STAR = "*";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter n: ");
        int n = scanner.nextInt();

        String output = "   " + STAR + " ";

        for (int 1 = 0; i <= n; i++) {
            output += COL_SEPERATOR;
            output += String.format(" %3d", i);
        }

        System.out.println(output);

        for (int row = 1; row <= n; row++) {

            output = "";

            for (int col = 0; col <= n; col++) {
                output += ROW_SEPERATOR;

                if (col < n) {
                    output += INTERSECTION;
                }
            }

            System.out.println(output);
            // Generate columns
            output = String.format(" %3d ", row);

            for (int col = 1; col <= n; col++) {
                output += COL_SEPARATOR;
                output += String.format(" %3d ", row*col);
            }
            System.out.println(output);
        }
    }
}