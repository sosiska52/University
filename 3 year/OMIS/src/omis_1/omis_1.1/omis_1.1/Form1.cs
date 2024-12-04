using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_1._1
{
    public partial class Form1 : Form
    {
        private Point[] points;

        public Form1()
        {
            InitializeComponent();
            // Инициализация массива точек
            points = new Point[]
            {
                new Point(50, 50),
                new Point(150, 50),
                new Point(200, 100),
                new Point(150, 150),
                new Point(50, 150),
                new Point(0, 100)
            };
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            DrawPolygon(e.Graphics);
        }

        private void DrawPolygon(Graphics g)
        {
            Pen pen = new Pen(Color.Black, 2);

            for (int i = 0; i < points.Length; i++)
            {
                int nextIndex = (i + 1) % points.Length; // для замыкания многоугольника
                g.DrawLine(pen, points[i].X, points[i].Y, points[nextIndex].X, points[nextIndex].Y);
            }

            pen.Dispose();
        }
    }
}

