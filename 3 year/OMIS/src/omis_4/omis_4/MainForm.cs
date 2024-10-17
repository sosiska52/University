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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace omis_4
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }
        private string[] pair;
        private string dataPath = "D:\\GitHubRepo\\University\\3 year\\OMIS\\src\\omis_4\\omis_4\\UsersData\\";

        private void MainForm_Load(object sender, EventArgs e)
        {
            SignForm reg = new SignForm();
            reg.FormClosed += reg_FormClosed;
            reg.ShowDialog();
        }

        private void reg_FormClosed(object sender, FormClosedEventArgs e)
        {
            SignForm signForm = sender as SignForm;
            if (signForm != null)
                this.pair = signForm.pair;
            this.Text = pair[1];
            this.dataPath = this.dataPath + pair[0] + ".txt";
        }

        private void dataGridView1_RowValidating(object sender, DataGridViewCellCancelEventArgs e)
        {
            if (e.RowIndex == dataGridView1.NewRowIndex)
                return;

            foreach (DataGridViewCell cell in dataGridView1.Rows[e.RowIndex].Cells)
                for(int i = 0; i < 3; i++)
                    if (cell.ColumnIndex == i && string.IsNullOrWhiteSpace(cell.Value?.ToString()))
                    {
                        dataGridView1.Rows[e.RowIndex].ErrorText = "Пожалуйста, заполните все поля.";
                        e.Cancel = true;
                        return;
                    }

            dataGridView1.Rows[e.RowIndex].ErrorText = string.Empty; 
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            File.WriteAllText(dataPath, "");
            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                if (!row.IsNewRow) 
                {
                    string year = row.Cells[0].Value.ToString();
                    string expenses = row.Cells[1].Value.ToString();
                    string income = row.Cells[2].Value.ToString();

                    string line = $"{year}\t{expenses}\t{income}\n";
                    File.AppendAllText(dataPath, line);
                }
            }
        }

        private void cleanToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            foreach (string line in File.ReadLines(dataPath))
            {
                string[] pair = line.Split(new char[] { '\t' }, StringSplitOptions.RemoveEmptyEntries);
                dataGridView1.Rows.Add(pair[0], pair[1], pair[2]);
            }
        }

        private void findToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SearchTask searchTask = new SearchTask(dataGridView1);
            searchTask.Show();
        }
    }
}
