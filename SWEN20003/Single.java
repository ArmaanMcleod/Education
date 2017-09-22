import java.util.ArrayList;
import java.util.Arrays;
import java.util.*;

public class Single {

    public static final String SPACE = " ";
    public static final String CSV = ",";

    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<String>();

        list.add("Hello");
        list.add("October 19");
        list.add("Bilal Sheheta");
        list.add("SWEN20003");

        String singleWords = processList(list);

        System.out.println(singleWords);
    }

    public static String processList(ArrayList <String> list) {
        String output = "";

        for (String string : list) {
            String[] splits = string.split(SPACE);
            if (splits.length == 1) {
                output += string + CSV;
            }
        }

        output = output.substring(0, output.length() - 1);

        return output;
    }
}