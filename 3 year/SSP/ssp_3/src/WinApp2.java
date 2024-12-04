import java.awt.*;
import java.awt.event.*;

public class WinApp2 {
    private List itemList;
    private Checkbox oddCheckbox;
    private Checkbox evenCheckbox;
    private Choice selectedItems;

    public WinApp2() {
        Frame frame = new Frame("Task 2");
        frame.setLayout(new BorderLayout());

        itemList = new List();
        for (int i = 0; i < 20; i++) {
            itemList.add("Element " + i);
        }

        oddCheckbox = new Checkbox("Choose odd lines");
        evenCheckbox = new Checkbox("Choose even lines");

        selectedItems = new Choice();

        ItemListener checkboxListener = e -> {
            if (e.getSource() == oddCheckbox && oddCheckbox.getState()) {
                evenCheckbox.setState(false);
            } else if (e.getSource() == evenCheckbox && evenCheckbox.getState()) {
                oddCheckbox.setState(false);
            }
            updateSelectedItems(); // Обновить выбранные элементы
        };
        oddCheckbox.addItemListener(checkboxListener);
        evenCheckbox.addItemListener(checkboxListener);

        Panel checkPanel = new Panel(new FlowLayout());
        checkPanel.add(oddCheckbox);
        checkPanel.add(evenCheckbox);

        Panel listPanel = new Panel(new GridLayout(1,2));
        listPanel.add(itemList);
        listPanel.add(selectedItems);

        frame.add(listPanel, BorderLayout.CENTER);
        frame.add(checkPanel, BorderLayout.SOUTH);

        frame.setExtendedState(Frame.MAXIMIZED_BOTH);
        frame.setVisible(true);

        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                frame.dispose();
            }
        });
    }

    private void updateSelectedItems() {
        selectedItems.removeAll();
        if (oddCheckbox.getState()) {
            for (int i = 0; i < itemList.getItemCount(); i++) {
                if (i % 2 != 0) {
                    selectedItems.add(itemList.getItem(i));
                }
            }
        }
        if (evenCheckbox.getState()) {
            for (int i = 0; i < itemList.getItemCount(); i++) {
                if (i % 2 == 0) {
                    selectedItems.add(itemList.getItem(i));
                }
            }
        }
    }
}