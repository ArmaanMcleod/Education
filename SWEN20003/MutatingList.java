import java.util.ArrayList;

public class MutatingList<T, M extends Mutator<T>> {
    private ArrayList<T> list;
    private ArrayList<T> mutatedList;
    private M mutator;

    public MutatingList(M mutator) {
        this.mutator = mutator;
        this.list = new ArrayList<T>();
    }

    public ArrayList<T> mutateList() {
        ArrayList<T> mutatedList = new ArrayList<T>();

        for (T integer : list) {
            mutatedList.add(mutator.mutate(integer));
        }

        return mutatedList;
    }

    public T mutateIndex(int index) {
        T indexedElement = list.get(index);
        return mutator.mutate(indexedElement);
    }

    public void add(T element) {
        list.add(element);
    }

    @Override
    public String toString() {
        String output = "";

        mutatedList = mutateList();

        for (int i = 0; i < list.size(); i++) {
            output += String.format("%s -> %s\n", list.get(i), mutatedList.get(i));
        }

        return output;
    }

    public static void main(String[] args) {
        IntegerMutator mutators = new IntegerMutator(30);
        MutatingList<Integer, IntegerMutator> list = new MutatingList<>(mutators);

        list.add(100);
        list.add(72);
        list.add(500);

        System.out.println(list.mutateIndex(2));
        System.out.println(list);
    }

}