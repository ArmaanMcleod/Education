import java.util.Scanner;

public class Elevator {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        final char FLOOR_CHAR = 'f';
        final char DOOR_CHAR = 'd';
        final char EMERGENCY_CHAR = 'e';

        final char FLOOR_CHAR_UPPER = 'F';
        final char DOOR_CHAR_UPPER = 'D';
        final char EMERGENCY_CHAR_UPPER = 'E';
        
        final int MIN_FLOOR = 0;
        final int MAX_FLOOR = 9;
        
        final int MAX_PEOPLE = 12;
        final int MAX_WEIGHT = 1000;
        
        // Get the elevator's command
        String input = scanner.nextLine();
        
        char command = input.charAt(0);
        
        // If the character is a digit, it's a floor command
        if (command == FLOOR_CHAR || command == FLOOR_CHAR_UPPER) {
            
            // Accept the rest of the command
            int currentFloor = scanner.nextInt();
            int nextFloor = scanner.nextInt();
            
            // Validate the input
            if ((currentFloor < MIN_FLOOR || currentFloor > MAX_FLOOR) ||
               (nextFloor < MIN_FLOOR || nextFloor > MAX_FLOOR)) {
                System.out.println("Error: Invalid floor");
            } 
            // Print an error if the next floor is the same as current
            else if (currentFloor == nextFloor) {
                System.out.println("Error: Already on floor " + currentFloor);
            }
            // Otherwise, be an elevator
            else {
                System.out.format("Action: Moving from floor %d to floor %d\n",
                                  currentFloor, nextFloor);
            }
        }
        // If the character is 'D' then it's a door command
        else if (command == DOOR_CHAR || command == DOOR_CHAR_UPPER) {
            
            // Accept the rest of the command
            String doorCommand = scanner.nextLine();
            
            // Execute the commands if they're valid
            if (doorCommand.equals("Open")) {
                System.out.println("Action: Opening doors");
            } else if (doorCommand.equals("Close")) {
                System.out.println("Action: Closing doors");
            }
            // If neither of these happen, the input was invalid
            else {
                System.out.println("Error: Invalid door command");
            }
        }
        // If the character is 'E' then it's an emergency command
        else if (command == EMERGENCY_CHAR || command == EMERGENCY_CHAR_UPPER) {
            
            // Accept the rest of the command
            String emergencyCommand = scanner.nextLine();
            
            if (emergencyCommand.equals("Weight")) {
                System.out.format("Emergency: Can hold at most %d people " +
                                  "or %dkg in the elevator\n", MAX_PEOPLE,
                                  MAX_WEIGHT);
            } else if (emergencyCommand.equals("Stop")) {
                System.out.println("Emergency: Elevator has stopped");
            } else if (emergencyCommand.equals("Inoperable")) {
                System.out.println("Emergency: Elevator has stopped working");
            }
            // If none of these happen, the input was invalid
            else {
                System.out.println("Error: Invalid emergency command");
            }
        }

        else {
            System.out.println("Error: Invalid command");
        }
    }
}