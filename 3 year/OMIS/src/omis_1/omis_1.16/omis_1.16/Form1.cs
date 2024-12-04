using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_1._16
{
    public partial class Form1 : Form
    {
        public Form1(){
            InitializeComponent();
        }
        private void openToolStripMenuItem_Click(object sender, EventArgs e){
            using (OpenFileDialog openFileDialog = new OpenFileDialog()){
                openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
                if (openFileDialog.ShowDialog() == DialogResult.OK){
                    string filePath = openFileDialog.FileName;
                    try{
                        string fileContent = System.IO.File.ReadAllText(filePath);
                        textBox1.Text = fileContent; 
                    }
                    catch (Exception ex){
                        MessageBox.Show($"Ошибка при чтении файла: {ex.Message}");
                    }

                    MessageBox.Show($"Файл открыт: {filePath}");
                }
            }
        }
        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e){
            using (SaveFileDialog saveFileDialog = new SaveFileDialog()) {
                saveFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
                if (saveFileDialog.ShowDialog() == DialogResult.OK){
                    string filePath = saveFileDialog.FileName;
                    try{
                        System.IO.File.WriteAllText(filePath, textBox1.Text);
                        MessageBox.Show($"Файл сохранен: {filePath}");
                    }
                    catch (Exception ex){
                        MessageBox.Show($"Ошибка при сохранении файла: {ex.Message}");
                    }
                    MessageBox.Show($"Файл сохранен: {filePath}");
                }
            }
        }
        private void exitToolStripMenuItem_Click(object sender, EventArgs e){
           this.Close();
        }
    }
}
