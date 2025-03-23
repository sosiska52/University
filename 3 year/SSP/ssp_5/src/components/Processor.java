package components;

public class Processor extends Component {
    private final double clockSpeed;

    public Processor(String name, String manufacturer, double price, double clockSpeed) {
        super(name, manufacturer, price);
        this.clockSpeed = clockSpeed;
    }

    public double getClockSpeed() { return clockSpeed; }
}