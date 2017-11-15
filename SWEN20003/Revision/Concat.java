import java.util.HashMap;

public class Concat {

    public static void main(String[] args) {
        System.out.println(filterAndConcat("Hello", "Hell", 2));
        System.out.println(filterAndConcat("Hello", "World", 2));
        System.out.println(filterAndConcat("Android good", "Apple bad", 3));
    }

    public static String filterAndConcat(String s1, String s2, int minFreq) {
        HashMap<Character, Integer> map1 = getMap(s1);
        HashMap<Character, Integer> map2 = getMap(s2);

        String first = getStrings(s1, map1, map2, minFreq);
        String second = getStrings(s2, map2, map1, minFreq);
        
        return first + second;
    }

    public static String getStrings(String string, 
                                    HashMap<Character, Integer> map1, 
                                    HashMap<Character, Integer> map2, 
                                    int minFreq) {
        String output = "";

        for (int i = 0; i < string.length(); i++) {
            char character = string.charAt(i);
            
            if (map2.get(character) != null) {
                if ((map1.get(character) + map2.get(character)) >= minFreq) {
                    output += character;
                }
            } else {
                if (map1.get(character) >= minFreq) {
                    output += character;
                }
            }

        }

        return output;
    }

    public static HashMap<Character, Integer> getMap(String string) {
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();

        for (int i = 0; i < string.length(); i++) {
            char character = string.charAt(i);
            Integer val = map.get(new Character(character));

            if (val != null) {
                map.put(character, new Integer(val+1));
            } else {
                map.put(character, 1);
            }
        }

        return map;
    }

}