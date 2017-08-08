public class Recipe {
    
    public static void main(String[] args) {
        /* test string */
        String recipe = "12 $12.72 Beef\n" +
                        "04 Carrots will cost $03.64\n" +
                        "99 I think $00.05 for Herbs";
        
        /* variable declarations */
        double total = 0.0, price;
        int quantity;
        final int start = 0;
        final int middle = 2;
        final int end = 7;
        
        /* only extracting important contents of string */
        recipe = recipe.replaceAll("[^0-9.]", "");
        
        /* calculating total recipe cost */
        for (int i = 0; i < 3; i++) {

            /* parsing text */
            quantity = Integer.parseInt(recipe.substring(start,middle));
            price = Double.parseDouble(recipe.substring(middle,end));
            total += quantity * price;

            /* cutting off parsed section of string */
            recipe = recipe.substring(end);
        }
       
        /* printing out result */
        System.out.println("Total recipe price: " + total);
        
    }
}