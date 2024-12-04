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
    public partial class Dialog2 : Form
    {
        private Form1 mainForm; 

        public Dialog2(Form1 form)
        {
            InitializeComponent();
            mainForm = form;
            label1.Text = mainForm.counter.ToString();
        }
    }
}
