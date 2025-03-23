import components.Processor;
import components.RAM;
import components.Storage;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static final List<PC> pcs = new ArrayList<>();
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        boolean exit = false;
        while (!exit) {
            printMenu();
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1 -> createPC();
                case 2 -> displayAllPCs();
                case 3 -> findPCWithMaxProcessorSpeed();
                case 4 -> exit = true;
                default -> System.out.println("Неверный выбор.");
            }
        }
    }

    private static void printMenu() {
        System.out.println("1. Создать ПК");
        System.out.println("2. Показать все ПК");
        System.out.println("3. Найти ПК с максимальной частотой процессора");
        System.out.println("4. Выход");
        System.out.print("Выберите действие: ");
    }

    private static void createPC() {
        PC pc = new PC();
        System.out.println("Добавление процессора:");
        pc.addComponent(createProcessor());
        pc.addComponent(createRAM());
        pc.addComponent(createStorage());
        pcs.add(pc);
        System.out.println("ПК успешно создан.");
    }

    private static Processor createProcessor() {
        System.out.print("Название процессора: ");
        String name = scanner.nextLine();
        System.out.print("Производитель: ");
        String manufacturer = scanner.nextLine();
        System.out.print("Цена: ");
        double price = scanner.nextDouble();
        System.out.print("Частота (ГГц): ");
        double clockSpeed = scanner.nextDouble();
        scanner.nextLine();
        return new Processor(name, manufacturer, price, clockSpeed);
    }

    private static RAM createRAM() {
        System.out.println("Добавление оперативной памяти:");
        System.out.print("Название: ");
        String name = scanner.nextLine();
        System.out.print("Производитель: ");
        String manufacturer = scanner.nextLine();
        System.out.print("Цена: ");
        double price = scanner.nextDouble();
        System.out.print("Объем (ГБ): ");
        int capacity = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Тип (DDR3/DDR4): ");
        String type = scanner.nextLine();
        return new RAM(name, manufacturer, price, capacity, type);
    }

    private static Storage createStorage() {
        System.out.println("Добавление хранилища:");
        System.out.print("Название: ");
        String name = scanner.nextLine();
        System.out.print("Производитель: ");
        String manufacturer = scanner.nextLine();
        System.out.print("Цена: ");
        double price = scanner.nextDouble();
        System.out.print("Объем (ГБ): ");
        int capacity = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Тип (SSD/HDD): ");
        String type = scanner.nextLine();
        return new Storage(name, manufacturer, price, capacity, type);
    }

    private static void displayAllPCs() {
        if (pcs.isEmpty()) {
            System.out.println("Список ПК пуст.");
            return;
        }
        for (int i = 0; i < pcs.size(); i++) {
            System.out.println("ПК #" + (i + 1));
            pcs.get(i).getComponents().forEach(c ->
                    System.out.println(c.getClass().getSimpleName() + ": " + c.getName()));
        }
    }

    private static void findPCWithMaxProcessorSpeed() {
        if (pcs.isEmpty()) {
            System.out.println("Нет ПК для сравнения.");
            return;
        }
        PC maxPc = pcs.get(0);
        double maxSpeed = maxPc.getMaxProcessorSpeed();
        for (PC pc : pcs) {
            double currentSpeed = pc.getMaxProcessorSpeed();
            if (currentSpeed > maxSpeed) {
                maxSpeed = currentSpeed;
                maxPc = pc;
            }
        }
        System.out.printf("ПК с максимальной частотой процессора: %.2f ГГц%n", maxSpeed);
    }
}