using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace omis_2_17
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    string filePath = openFileDialog.FileName;
                    try
                    {
                        string fileContent = System.IO.File.ReadAllText(filePath);
                        richTextBox1.Text = fileContent;
                        richTextBox1.Modified = false;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show($"Ошибка при чтении файла: {ex.Message}");
                    }
                }
            }
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (richTextBox1.Modified)
            {
                DialogResult result = MessageBox.Show("Save text?", "Attention", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (result == DialogResult.Yes) {
                    using (SaveFileDialog saveFileDialog = new SaveFileDialog())
                    {
                        saveFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
                        if (saveFileDialog.ShowDialog() == DialogResult.OK)
                        {
                            string filePath = saveFileDialog.FileName;
                            try
                            {
                                System.IO.File.WriteAllText(filePath, richTextBox1.Text);
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show($"Ошибка при сохранении файла: {ex.Message}");
                            }
                        }
                    }
                }
                else
                {
                    richTextBox1.Clear();
                    richTextBox1.Modified = false;
                }
            }
            else
            {
                richTextBox1.Clear();
                richTextBox1.Modified = false;
            }
        }
    }
}
