import java.util.Scanner;

public class FamousLines {
    public static void main(String[] args) {
        /* Create scanner object */
        Scanner scanner = new Scanner(System.in);
    
        /* Take input from user */
        System.out.println("Enter name of TV show or movie:");

        /* store input in string */
        String input = scanner.nextLine();
        
        if (input.equals("Game of Thrones")) {
            System.out.println("Winter is coming");

        } else if (input.equals("Star Wars")) {
            System.out.println("I am your father");

        } else if (input.equals("Breaking Bad")) {
            System.out.println("I am the one who knocks");   

        } else if (input.equals("The Avengers")) {
            System.out.println("Hulk, smash");   

        } else if (input.equals("Frozen")) {
            System.out.println("Let it go!");   

        } else {
            System.out.println("Sorry, I don't know that one");
        }
    }
}