import java.awt.*;
import java.awt.event.*;

public class WinApp1 {
    private List list1, list2, list3;

    public WinApp1() {
        Frame frame = new Frame("Task 1");
        frame.setLayout(new BorderLayout());

        list1 = new List();
        list2 = new List();
        list3 = new List();

        Panel listPanel = new Panel();
        listPanel.setLayout(new GridLayout(1, 3));
        listPanel.add(list1);
        listPanel.add(list2);
        listPanel.add(list3);

        frame.add(listPanel, BorderLayout.CENTER);

        Panel buttonPanel = new Panel();
        buttonPanel.setLayout(new FlowLayout());

        Button moveToNext = new Button("Move");
        moveToNext.addActionListener(e -> moveSelectedItem());

        Button addItem = new Button("Add");
        addItem.addActionListener(e -> addItemToList());

        Button editItem = new Button("Edit");
        editItem.addActionListener(e -> editSelectedItem());

        Button deleteItem = new Button("Delete");
        deleteItem.addActionListener(e -> deleteSelectedItem());

        buttonPanel.add(moveToNext);
        buttonPanel.add(addItem);
        buttonPanel.add(editItem);
        buttonPanel.add(deleteItem);

        frame.add(buttonPanel, BorderLayout.SOUTH);

        frame.setExtendedState(Frame.MAXIMIZED_BOTH);
        frame.setVisible(true);

        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                frame.dispose();
            }
        });
    }

    private void moveSelectedItem() {
        String selectedValue1 = list1.getSelectedItem();
        String selectedValue2 = list2.getSelectedItem();
        String selectedValue3 = list3.getSelectedItem();

        if (selectedValue1 != null) {
            list1.remove(selectedValue1);
            list2.add(selectedValue1);
        } else if (selectedValue2 != null) {
            list2.remove(selectedValue2);
            list3.add(selectedValue2);
        } else if (selectedValue3 != null) {
            list3.remove(selectedValue3);
            list1.add(selectedValue3);
        }
    }

    private void addItemToList() {
        String newItem = DialogUtils.showInputDialog("Enter new element:");
        if (newItem != null && !newItem.trim().isEmpty()) {
            list2.add(newItem);
        }
    }

    private void editSelectedItem() {
        String selectedValue = list2.getSelectedItem();
        if (selectedValue != null) {
            String newValue = DialogUtils.showInputDialog("Edit element:", selectedValue);
            if (newValue != null && !newValue.trim().isEmpty()) {
                list2.replaceItem(newValue, list2.getSelectedIndex());
            }
        }
    }

    private void deleteSelectedItem() {
        int selectedIndex = list2.getSelectedIndex();
        if (selectedIndex != -1) {
            list2.remove(selectedIndex);
        }
    }
}

class DialogUtils {
    public static String showInputDialog(String message) {
        return showInputDialog(message, "");
    }

    public static String showInputDialog(String message, String initialValue) {
        Dialog dialog = new Dialog((Frame) null, "Enter:", true);
        dialog.setLayout(new FlowLayout());

        Label label = new Label(message);
        TextField textField = new TextField(initialValue, 20);
        Button okButton = new Button("OK");
        Button cancelButton = new Button("Cancel");

        okButton.addActionListener(e -> {
            dialog.setVisible(false);
        });

        cancelButton.addActionListener(e -> {
            textField.setText(null);
            dialog.setVisible(false);
        });

        dialog.add(label);
        dialog.add(textField);
        dialog.add(okButton);
        dialog.add(cancelButton);

        dialog.setSize(300, 150);
        dialog.setLayout(new FlowLayout());
        dialog.setVisible(true);

        return textField.getText();
    }
}