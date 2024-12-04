import java.awt.*;
import javax.sound.sampled.*;
import java.io.File;

public class Task1 {
    private Button button1 = new Button("Red");
    private Button button2 = new Button("Yellow");
    private Button button3 = new Button("Green");
    private Button button4 = new Button("Sound");

    private boolean showRed = false;
    private boolean showYellow = false;
    private boolean showGreen = false;

    public Task1(){
        Frame frame = new Frame("Task1");
        frame.setSize(600, 400);
        frame.setLayout(null);

        button1.setBounds(350, 50, 100, 30);
        button2.setBounds(350, 100, 100, 30);
        button3.setBounds(350, 150, 100, 30);
        button4.setBounds(350, 200, 100, 30);

        frame.add(button1);
        frame.add(button2);
        frame.add(button3);
        frame.add(button4);

        Canvas canvas = new Canvas() {
            @Override
            public void paint(Graphics g) {
                if(showRed)
                    g.setColor(Color.RED);
                else g.setColor(Color.GRAY);
                g.fillRect(50, 50, 50, 50);

                if(showYellow)
                    g.setColor(Color.YELLOW);
                else g.setColor(Color.GRAY);
                g.fillRect(50, 110, 50, 50);

                if(showGreen)
                    g.setColor(Color.GREEN);
                else g.setColor(Color.GRAY);
                g.fillRect(50, 170, 50, 50);

                g.setColor(Color.GRAY);
                g.fillRect(75, 230, 10, 70);
            }
        };

        button1.addActionListener(e -> {
            showRed = !showRed;
            canvas.repaint();
        });
        button2.addActionListener(e -> {
            showYellow = !showYellow;
            canvas.repaint();
        });
        button3.addActionListener(e -> {
            showGreen = !showGreen;
            canvas.repaint();
        });
        button4.addActionListener(e -> playSound("D:\\GitHubRepo\\University\\3 year\\SSP\\ssp_4\\src\\sound.wav"));

        canvas.setSize(300, 300);
        canvas.setLocation(0, 0);
        frame.add(canvas);

        frame.setVisible(true);

        frame.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                System.exit(0);
            }
        });
    }

    private void playSound(String soundFile) {
        try {
            File sound = new File(soundFile);
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(sound);
            Clip clip = AudioSystem.getClip();
            clip.open(audioInputStream);
            clip.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
