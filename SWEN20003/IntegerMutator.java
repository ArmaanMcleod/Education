public class IntegerMutator implements Mutator<Integer> {
    private int n;


    public IntegerMutator(int n) {
        this.n = n;
    }

    @Override
    public Integer mutate(Integer integer) {
        return integer % n;
    }
}