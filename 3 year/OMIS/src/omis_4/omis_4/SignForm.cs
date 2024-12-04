using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_4
{
    public partial class SignForm : Form
    {
        public SignForm()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
        }
        private const string loginPath = "D:\\GitHubRepo\\University\\3 year\\OMIS\\src\\omis_4\\omis_4\\logins.txt";
        public string[] pair;
        private int findLogin(string newLogin)
        {
            int ind = 0;
            foreach (string line in File.ReadLines(loginPath))
            {
                string[] pair = line.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                if (pair[0] == newLogin)
                {
                    this.pair = pair;
                    return ind;
                }
                ind++;
            }
            return -1;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int ind = findLogin(textBox1.Text);
            if (ind >= 0)
            {
                MessageBox.Show("Welcome back, " + pair[1]);
                this.Close();
            }
            else
                MessageBox.Show("Wrong login");
        }

        private void label2_Click(object sender, EventArgs e)
        {
            SignIn signIn = new SignIn();
            signIn.ShowDialog();
        }
    }
}
