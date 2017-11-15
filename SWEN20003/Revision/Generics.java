import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.HashMap;

public class Generics {

    private static final String COMMA = ",";
    private static final String SPACE = " ";

    public static void main(String[] args) {
        ArrayList<String> words = new ArrayList<String>();
        ArrayList<Customer> customers = new ArrayList<Customer>();

        words.add("Armaan");
        words.add("School is cool");
        words.add("You");
        words.add("Know nothing");

        String commaSep = processWords(words);

        System.out.println(commaSep);

        customers.add(new Customer(10));
        customers.add(new Customer(2));
        customers.add(new Customer(5));
        customers.add(new Customer(6));

        PriorityQueue<Customer> custOrders = processCustomers(customers);

        
    }

    public static HashMap<Ingredient, Integer> getQuantities(Recipe recipe) {
        HashMap<Ingredient, Integer> quantities = new HashMap<>();

        for (Ingredient ingredient : recipe.getIngredients()) {
            quantities.put(ingredient, ingredient.getCost());
        }

        return quantities;

    }

    public static PriorityQueue<Customer> processCustomers(ArrayList<Customer> customers) {
        PriorityQueue<Customer> queue = new PriorityQueue<Customer>(new CustomerComparator());

        for (Customer customer : customers) {
            queue.add(customer);
        }

        return queue;
    }



    public static String processWords(ArrayList<String> strings) {
        String output = "";

        for (String string : strings) {
            String[] words = string.split(SPACE);
            if (words.length == 1) {
                output += string;
                output += COMMA;
            }
        }

        output = output.substring(0, output.length()-1);

        return output;
    }
}