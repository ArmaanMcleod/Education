import java.util.Comparator;
import java.util.HashMap;

public class EntryComparator implements Comparator<HashMap.Entry<Character, Integer>> {

    @Override
    public int compare(HashMap.Entry<Character, Integer> o1, HashMap.Entry<Character, Integer> o2) {
        if (o1.getValue() < o2.getValue()) {
            return 1;
        } else if (o1.getValue() > o2.getValue()) {
            return -1;
        }
        return 0;
    }
}