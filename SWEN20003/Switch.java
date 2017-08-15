import java.util.Scanner;

public class Switch {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        /* Prompt */
        System.out.print("Enter direction: ");
        
        /* Store direction in string */
        String direction = scanner.nextLine();

        /* Convert string letters to lower case for comparisons */
        direction = direction.toLowerCase();
        
        /* evaluating strings via switch */
        switch (direction) {
            case "north":
                System.out.println("0 degrees from North");
                break;
            case "east":
                System.out.println("90 degrees from North");
                break;
            case "south":
                System.out.println("180 degrees from North");
                break;
            case "west":
                System.out.println("270 degrees from North");
                break;
            default:
                System.out.println("Invalid");
        }
    }
}