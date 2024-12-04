using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_1._22
{
    public partial class Dialog : Form{
        public string text;
        public Dialog(){
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e){
            text = richTextBox1.Text; 
            this.DialogResult = DialogResult.OK; 
            this.Close();
        }
    }
}
