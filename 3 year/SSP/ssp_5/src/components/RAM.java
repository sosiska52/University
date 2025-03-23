package components;

public class RAM extends Component {
    private final int capacity;
    private final String type;

    public RAM(String name, String manufacturer, double price, int capacity, String type) {
        super(name, manufacturer, price);
        this.capacity = capacity;
        this.type = type;
    }

    public int getCapacity() { return capacity; }
    public String getType() { return type; }
}