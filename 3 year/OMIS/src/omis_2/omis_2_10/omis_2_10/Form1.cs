using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_2_10
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            countA = 0;
            countB = 0;
            countPaint = 0;
            InitializeComponent();
        }

        private int countA;
        private int countB;
        private int countPaint;
        private void Form1_Activated(object sender, EventArgs e)
        {
            countA++;
            string text = "A = ";
            this.label1.Text =text + countA.ToString();
        }

        private void Form1_Deactivate(object sender, EventArgs e)
        {
            countB++;
            string text = "DA = ";
            this.label2.Text = text + countB.ToString();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            countPaint++;
            string text = "ReDrawNumber = ";
            this.label3.Text = text + countPaint.ToString();
        }
    }
}
