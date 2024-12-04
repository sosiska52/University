using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_2_20
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        public int counter = 0;
        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                using (Dialog1 dialog1 = new Dialog1())
                {
                    dialog1.ShowDialog(this);
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                counter++;
                Dialog2 dialog2 = new Dialog2(this);
                dialog2.ShowDialog(this);
            }
        }
    }
}
