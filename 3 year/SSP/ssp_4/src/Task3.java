import javax.swing.*;
import java.awt.*;

public class Task3 {
    private Button button1 = new Button("Square");
    private Button button2 = new Button("Circle");
    private Button button3 = new Button("Triangle");

    private boolean isSquare = false;
    private boolean isCircle = false;
    private boolean isTriangle = false;

    public Task3(){
        Frame frame = new Frame("Task 3");
        frame.setSize(600, 400);
        frame.setLayout(null);

        button1.setBounds(350, 50, 100, 30);
        button2.setBounds(350, 100, 100, 30);
        button3.setBounds(350, 150, 100, 30);

        frame.add(button1);
        frame.add(button2);
        frame.add(button3);

        Canvas canvas = new Canvas() {
            @Override
            public void paint(Graphics g) {
                g.setColor(Color.GREEN);
                if(isCircle)
                    g.fillOval(50, 50, 50, 50);
                if(isSquare)
                    g.fillRect(50,50,50,50);
                if(isTriangle)
                    g.fillPolygon(new int[]{50,50,25}, new int[]{75,50,75}, 3);
            }
        };
        canvas.setSize(300, 300);
        canvas.setLocation(0, 0);

        button1.addActionListener(e -> {
            isSquare = true;
            isCircle = isTriangle = false;
            canvas.repaint();
        });
        button2.addActionListener(e -> {
            isCircle = true;
            isSquare = isTriangle = false;
            canvas.repaint();
        });
        button3.addActionListener(e -> {
            isTriangle = true;
            isSquare = isCircle = false;
            canvas.repaint();
        });

        frame.add(canvas);
        frame.setVisible(true);

        frame.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                System.exit(0);
            }
        });
    }
}
