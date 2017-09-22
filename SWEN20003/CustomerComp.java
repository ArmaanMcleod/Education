import java.util.Comparator;

public class CustomerComp implements Comparator <Customer> {
    public int compare(Customer arg0, Customer arg1) {
        return arg0.getWaitTime -  arg1.getWaitTime();
    }
}