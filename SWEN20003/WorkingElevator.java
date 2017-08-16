import java.util.Scanner;

public class WorkingElevator {
	public static void main(String[] args) {

		/* Important constants declared */
		final char FLOOR_LOWER = 'f';
		final char FLOOR_UPPER = 'F';

		final char DOOR_LOWER = 'd';
		final char DOOR_UPPER = 'D';

		final int MIN_FLOOR = 0;
        final int MAX_FLOOR = 9;

        final int MAX_PEOPLE = 12;
        final int MAX_WEIGHT = 1000;

        int currentFloor = MIN_FLOOR, nextFloor;
        boolean doorsOpen = true;
        boolean letPassengerOut = false;

        /* Created scanner object */
		Scanner scanner = new Scanner(System.in);

		while (scanner.hasNextLine()) {
			String input = scanner.nextLine();

			/* Get the first character from input */
			char command = input.charAt(0);

			// If the character is a digit, it's a floor command
			if (command == FLOOR_UPPER || command == FLOOR_LOWER) {

				if (letPassengerOut == false) {
					if (!doorsOpen) {
					    // Accept the rest of the command
					    nextFloor = scanner.nextInt();
					    scanner.nextLine();

					    // Validate the input
					    if (nextFloor < MIN_FLOOR || nextFloor > MAX_FLOOR) {
	                        System.out.println("Error: Invalid floor");
	                    } else if (currentFloor == nextFloor) {
	                        System.out.println("Error: Already on floor " + currentFloor);
	                    } else {
	                        System.out.format("Action: Moving from floor %d " +
                                              "to floor %d\n",
	                                           currentFloor, nextFloor);
	                    
	                        currentFloor = nextFloor;
	                        letPassengerOut = true;
	                    }
				    } else {
					    System.out.println("Error: Doors must " + 
                                           "be closed to move!");
				    }
				} else {
					System.out.println("Error: You should let the " +
                                       "passengers out first!");
				}

			} else if (command == DOOR_LOWER || command == DOOR_UPPER) {
            
	            // Accept the rest of the command
	            String doorCommand = scanner.nextLine();
	            
	            // Execute the commands if they're valid
	            if (doorCommand.equals("Open")) {
	            	doorsOpen = true;
	            	letPassengerOut = false;
	                System.out.println("Action: Opening doors");
	            } else if (doorCommand.equals("Close")) {
	            	if (letPassengerOut == false) {
	            		doorsOpen = false;
	                	System.out.println("Action: Closing doors");
	            	} else {
	            		System.out.println("Error: You should let the " +
	            		                    "passengers out first!");
	            	}
	            }
	            // If neither of these happen, the input was invalid
	            else {
	                System.out.println("Error: Invalid door command");
	            }

	        } else {
                System.out.println("Error: Invalid command");
            }
		}
	}
}