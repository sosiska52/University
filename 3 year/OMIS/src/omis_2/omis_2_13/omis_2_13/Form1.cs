using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_2_13
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string input = textBox1.Text; 
            int number;
            if (int.TryParse(input, out number))
            {
                textBox2.Text = Math.Sqrt(number).ToString();
            }
            else
            {
                MessageBox.Show("Enter number");
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                textBox4.Text = listBox1.SelectedItem.ToString();
            }
            else
            {
                textBox4.Clear(); 
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox4 != null)
            {
                listBox1.Items.Remove(listBox1.SelectedItem);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox3 != null) { 
                listBox1.Items.Add(textBox3.Text);
            }
        }
    }
}
