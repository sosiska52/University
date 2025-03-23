package components;

public class Storage extends Component {
    private final int capacity;
    private final String type;

    public Storage(String name, String manufacturer, double price, int capacity, String type) {
        super(name, manufacturer, price);
        this.capacity = capacity;
        this.type = type;
    }

    public int getCapacity() { return capacity; }
    public String getType() { return type; }
}