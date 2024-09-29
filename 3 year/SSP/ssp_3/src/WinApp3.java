import java.awt.*;
import java.awt.event.*;

public class WinApp3 {
    private List list;
    private TextField textField;
    private Frame frame;

    public WinApp3(){
        frame = new Frame("Task 3");
        frame.setLayout(new BorderLayout());

        list = new List();
        textField = new TextField();

        list.setMultipleMode(true);
        textField.setEditable(false);

        for(int i = 0; i < 20; i++){
            list.add("Element " + i);
        }

        frame.add(list, BorderLayout.WEST);
        frame.add(textField, BorderLayout.CENTER);

        list.addItemListener(e -> updateText());

        textField.addTextListener(e -> {
            if(textField.getText().length() > 100)
                callDialog();
        });

        frame.setExtendedState(Frame.MAXIMIZED_BOTH);
        frame.setVisible(true);

        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                frame.dispose();
            }
        });
    }

    private void updateText(){
        textField.setText("");
        StringBuilder text = new StringBuilder();
        for(int i = 0; i < list.getItemCount(); i++)
            if(list.isIndexSelected(i))
                text.append(list.getItem(i));
        textField.setText(text.toString());
    }

    private void callDialog(){
        Dialog dialog = new Dialog(frame, "Dialog", true);
        dialog.setLayout(new FlowLayout());

        Label label = new Label();
        label.setText("Your text is over 100 characters!");

        dialog.add(label);

        Button okButton = new Button("OK");
        okButton.addActionListener(e -> dialog.dispose());
        dialog.add(okButton);

        dialog.setSize(200, 100);
        dialog.setVisible(true);
    }
}
