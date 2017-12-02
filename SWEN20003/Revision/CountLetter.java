import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class CountLetter {

    public static void main(String[] args) {
        String test = "June, July and August";

        HashMap<Character, Integer> counts = getCounts(test);

        System.out.println("All Letter-Frequency Pairs:");
        for (HashMap.Entry<Character, Integer> entry : counts.entrySet()) {
            System.out.println("Key = " + entry.getKey() + ", Value = " + entry.getValue());
        }

        List<HashMap.Entry<Character, Integer>> topThree = getTop(counts, 3);

        System.out.println("\nTop 3 Letter-Frequency Pairs:");
        for (HashMap.Entry<Character, Integer> entry : topThree) {
            System.out.println("Key = " + entry.getKey() + ", Value = " + entry.getValue());
        }
    }

    public static List<HashMap.Entry<Character, Integer>> getTop(HashMap<Character, Integer> map, int top) {
        List<HashMap.Entry<Character, Integer>> list = new ArrayList<HashMap.Entry<Character, Integer>>(map.entrySet());

        Collections.sort(list, new EntryComparator());

        return list.subList(0, top);
    }

    public static HashMap<Character, Integer> getCounts(String words) {
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();

        for (int i = 0; i < words.length(); i++) {
            char currentChar = words.charAt(i);
            Integer currentCount = map.get(currentChar);

            if (currentCount == null) {
                map.put(currentChar, 1);
            } else {
                map.put(currentChar, new Integer(currentCount + 1));
            }
        }

        return map;
    }
}