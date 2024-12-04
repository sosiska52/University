import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.Timer;

public class Task4 {
    Canvas canvas;
    private Button button1 = new Button("Up");
    private Button button2 = new Button("Down");
    private Button button3 = new Button("Bigger");
    private Button button4 = new Button("Smaller");

    private int x = 50;
    private int y = 50;
    private int diameter = 100;

    private Timer moveTimer;
    private Timer deformTimer;
    private boolean isMovingUp = false;
    private boolean isMovingDown = false;
    private boolean isExpanding = false;
    private boolean isShrinking = false;

    public Task4(){
        Frame frame = new Frame("Task 4");
        frame.setSize(600, 800);
        frame.setLayout(null);

        button1.setBounds(450, 50, 100, 30);
        button2.setBounds(450, 100, 100, 30);
        button3.setBounds(450, 150, 100, 30);
        button4.setBounds(450, 200, 100, 30);

        frame.add(button1);
        frame.add(button2);
        frame.add(button3);
        frame.add(button4);

        canvas = new Canvas() {
            @Override
            public void paint(Graphics g) {
                g.setColor(Color.RED);
                g.fillOval(x, y, diameter, diameter);
            }
        };
        canvas.setSize(500, 800);
        canvas.setLocation(0, 0);
        frame.add(canvas);

        button1.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                isMovingUp = true;
                startMoving();
            }
            @Override
            public void mouseReleased(MouseEvent e) {
                isMovingUp = false;
            }
        });

        button2.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                isMovingDown = true;
                startMoving();
            }
            @Override
            public void mouseReleased(MouseEvent e) {
                isMovingDown = false;
            }
        });

        button3.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                isExpanding = true;
                startDeforming();
            }
            @Override
            public void mouseReleased(MouseEvent e) {
                isExpanding = false;
            }
        });

        button4.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                isShrinking = true;
                startDeforming();
            }
            @Override
            public void mouseReleased(MouseEvent e) {
                isShrinking = false;
            }
        });

        frame.setVisible(true);

        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent) {
                System.exit(0);
            }
        });
    }

    private void startMoving() {
        if (moveTimer == null) {
            moveTimer = new Timer(100, e -> {
                if (isMovingUp) {
                    y-=5;
                    canvas.repaint();
                }
                if (isMovingDown){
                    y+=5;
                    canvas.repaint();
                }
            });
            moveTimer.start();
        }
    }

    private void startDeforming() {
        if (deformTimer == null) {
            deformTimer = new Timer(100, e -> {
                if (isExpanding) {
                    diameter+=5;
                    canvas.repaint();
                }
                if (isShrinking){
                    diameter-=5;
                    canvas.repaint();
                }
            });
            deformTimer.start();
        }
    }
}
