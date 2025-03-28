import components.Component;
import components.Processor;
import java.util.ArrayList;
import java.util.List;

public class PC {
    private final List<Component> components;

    public PC() {
        components = new ArrayList<>();
    }

    public void addComponent(Component component) {
        components.add(component);
    }

    public double getMaxProcessorSpeed() {
        double maxSpeed = 0.0;

        for (Component component : components) {
            if (component instanceof Processor) {
                Processor processor = (Processor) component;
                if (processor.getClockSpeed() > maxSpeed) {
                    maxSpeed = processor.getClockSpeed();
                }
            }
        }

        return maxSpeed;
    }

    public List<Component> getComponents() {
        return new ArrayList<>(components);
    }
}