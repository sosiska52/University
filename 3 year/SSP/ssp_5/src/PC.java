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
        return components.stream()
                .filter(Processor.class::isInstance)
                .map(Processor.class::cast)
                .mapToDouble(Processor::getClockSpeed)
                .max()
                .orElse(0.0);
    }

    public List<Component> getComponents() {
        return new ArrayList<>(components);
    }
}