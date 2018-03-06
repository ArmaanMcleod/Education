import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;

public class FirstMax {

    public static void main(String[] args) {
        String text = "this is a test yes of a test a test";

        String[] textSplit = text.split(" ");

        List<String> words = getWordArray(textSplit);

        Map<String, Integer> freqs = wordFrequencyMap(words);

        for (Map.Entry<String, Integer> entry : freqs.entrySet()) {
            System.out.println(entry.getKey() + " " + entry.getValue());
        }

        Map.Entry<String, Integer> maxWord = getFirstMax(freqs);

        System.out.println("The word that occurs most often and its count are: " + 
                            maxWord.getKey() + " " + maxWord.getValue());

    }

    public static Map.Entry<String, Integer> getFirstMax(Map<String, Integer> freqs) {
        Map.Entry<String, Integer> maxWord = null;

        for (Map.Entry<String, Integer> entry : freqs.entrySet()) {
            if (maxWord == null || entry.getValue().compareTo(maxWord.getValue()) > 0) {
                maxWord = entry;
            }
        }

        return maxWord;
    }

    public static List<String> getWordArray(String[] text) {
        List<String> words = new ArrayList<String>();

        for (String word : text) {
            words.add(word);
        }

        return words;
    }

    public static Map<String, Integer> wordFrequencyMap(List<String> words) {
        Map<String, Integer> freqs = new HashMap<String, Integer>();

        for (String word : words) {
            if (freqs.keySet().contains(word)) {
                freqs.put(word, freqs.get(word) + 1);
            } else {
                freqs.put(word, 1);
            }
        }

        return freqs;
    }
}