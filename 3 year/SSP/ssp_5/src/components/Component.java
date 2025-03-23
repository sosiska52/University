package components;

public abstract class Component {
    private final String name;
    private final String manufacturer;
    private final double price;

    public Component(String name, String manufacturer, double price) {
        this.name = name;
        this.manufacturer = manufacturer;
        this.price = price;
    }

    public String getName() { return name; }
    public String getManufacturer() { return manufacturer; }
    public double getPrice() { return price; }
}