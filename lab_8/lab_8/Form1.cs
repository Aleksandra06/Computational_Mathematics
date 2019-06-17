using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab_8
{
    public partial class Form1 : Form
    {
        int XX, YY;
        int centerX, centerY, one;
        bool plus = true;

        const int N = 3;
        int n;

        double[,] matrix;
        double[] a;
        double[,] c;
        double[] b;

        double x0 = 0, xn;
        double[] xi, yi, gi;
        double h;

        public Form1()
        {
            InitializeComponent();
            XX = pictureBox1.Width;
            YY = pictureBox1.Right;
            centerX = (int)XX / 2;
            centerY = (int)YY / 2;
            one = (int)centerX / 10;



            input();
            init_value();
            fill_matrix();
            gaus(N, N + 1);
            print_a();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            osi(e);
            apr(e);
        }

        private void osi(PaintEventArgs g)
        {
            Pen BlackPen = new Pen(Color.Black);
            g.Graphics.DrawLine(BlackPen, 0, centerY, XX, centerY);//x
            g.Graphics.DrawLine(BlackPen, centerX, 0, centerX, YY);//y
            Font myfont = new Font("Arial", 14);
            g.Graphics.DrawString("X", myfont, Brushes.Black, new Point(XX - 20, centerY));
            g.Graphics.DrawString("Y", myfont, Brushes.Black, new Point(centerX, 20));
            Font myfont1 = new Font("Arial", 6);
            for (int i = centerX; i < XX; i = i + one)
            {
                g.Graphics.DrawRectangle(Pens.Black, i, centerY, 1, 2);
                g.Graphics.DrawString(((i - centerX) / one).ToString(), myfont1, Brushes.Black, new Point(i, centerY));
            }
            for (int i = centerX; i > 0; i = i - one)
            {
                g.Graphics.DrawRectangle(Pens.Black, i, centerY, 1, 2);
                g.Graphics.DrawString(((i - centerX) / one).ToString(), myfont1, Brushes.Black, new Point(i, centerY));
            }
            for (int i = centerY; i < YY; i = i + one)
            {
                g.Graphics.DrawRectangle(Pens.Black, centerX, i, 2, 1);
                g.Graphics.DrawString(((centerY - i) / one).ToString(), myfont1, Brushes.Black, new Point(centerX, i));
            }
            for (int i = centerY; i > 0; i = i - one)
            {
                g.Graphics.DrawRectangle(Pens.Black, centerX, i, 2, 1);
                g.Graphics.DrawString(((centerY - i) / one).ToString(), myfont1, Brushes.Black, new Point(centerX, i));
            }
        }     

        private void button1_Click(object sender, EventArgs e)
        {
            if (centerY > 10)
            {
                centerY = centerY - 10;
                pictureBox1.Invalidate();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (centerY < YY - 20)
            {
                centerY = centerY + 10;
                pictureBox1.Invalidate();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (centerX < XX - 20)
            {
                centerX = centerX + 10;
                pictureBox1.Invalidate();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (centerX > 20)
            {
                centerX = centerX - 10;
                pictureBox1.Invalidate();
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (one < centerX - 20)
            {
                one = one + 10;
                pictureBox1.Invalidate();
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (one > 20)
            {
                one = one - 10;
                pictureBox1.Invalidate();
            }
        }

        private double f(double x)
        {
            //return x * x;
            //return Math.Sqrt(x);
            //return x;
             return Math.Exp(x);
        }

        private double g(int r, double x)
        {
            gi[0] = 1;
            gi[1] = x;
            gi[2] = Math.Sqrt(x);
            //for (int i = 2; i < N; i++) { gi[i] = gi[i - 1] * x; }
           // gi[3] = Math.Exp(x);
            return gi[r];
        }

        private void input()
        {
            x0 = 0;
            xn = 3;
            h = 1;
            n = (int)((xn - x0) / h) + 1;
            //label2.Text = n.ToString();
        }

        private void init_value()
        {
            xi = new double[n];
            yi = new double[n];
            gi = new double[N];

            for (int i = 0; i < n; i++)
            {
                xi[i] = x0 + h * i;
                yi[i] = f(xi[i]);
            }
            //label2.Text = yi[n-1].ToString();
        }

        private double[,] fill_matrix()
        {
            matrix = new double[N, N + 1];

            init_c_b();
            fill_c();
            fill_b();
            fill_matrix_cb();

            return matrix;
        }

        private void init_c_b()
        {
            c = new double[N, N];
            b = new double[N];

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    c[i, j] = 0;
                }
                b[i] = 0;
            }
        }

        private double[,] fill_c()
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        c[i, j] += g(i, xi[k]) * g(j, xi[k]);
                    }
                }
            }
            return c;
        }

        private double[] fill_b()
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    b[i] += g(i, xi[j]) * f(xi[j]);
                }
            }
            return b;
        }

        private double[,] fill_matrix_cb()
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    matrix[i, j] = c[i, j];
                }
                matrix[i, N] = b[i];
            }
            return matrix;
        }

        private int gaus(int n, int m)
        {
            double coef;

            for (int j = 0; j < m - 1; j++)
            {
                swap(j, n, m);
                for (int i = j + 1; i < n; i++)
                {
                    coef = matrix[i, j] / matrix[j, j];
                    for (int k = 0; k < m; k++)
                    {
                        matrix[i, k] -= matrix[j, k] * coef;
                    }
                }
            }
            root(n, m);
            return 0;
        }

        private int swap(int number_swap, int n, int m)
        {
            int number_max = 0;
            double max = 0.0, tmp;

            for (int i = number_swap; i < n; i++)
            {
                if (Math.Abs(max) < Math.Abs(matrix[i, number_swap]))
                {
                    max = matrix[i, number_swap];
                    number_max = i;
                }
            }

            for (int k = 0; k < m; k++)
            {
                tmp = matrix[number_swap, k];
                matrix[number_swap, k] = matrix[number_max, k];
                matrix[number_max, k] = tmp;
            }
            return 0;
        }

        private int root(int n, int m)
        {
            a = new double[N];
            for (int i = 0; i < N; i++)
            {
                a[i] = 0;
            }

            int row = n - 1, column = m - 1;
            double sum = 0;

            for (int i = row, r = column - 1; r > -1; i--, r--)
            {
                sum = 0;
                for (int j = column - 1; j > i; j--)
                {
                    sum += matrix[i, j] * a[j];
                }
                a[r] = (matrix[i, column] - sum) / matrix[i, i];
            }
            return 0;
        }

        private double g_graphic(double x)
        {
            double y = 0;

            for (int i = 0; i < N; i++)
            {
                double q = a[i];
                y += a[i] * g(i, x);
            }
            return y;
        }

        void apr(PaintEventArgs e)
        {
            int tmpx, tmpy;
            for (int i = 0; i < n; i++)
            {
                if ((0 < (int)(centerX + xi[i] * one) || (int)(centerX + xi[i] * one) < XX) && ((int)(centerY - (one * f(xi[i]))) > 0 || (int)(centerY - (one * f(xi[i]))) < YY))
                    e.Graphics.DrawRectangle(Pens.Black, (int)(centerX + xi[i] * one)-1, (int)(centerY - (one * f(xi[i])))-1, 3, 3);
            }

            Pen pens = new Pen(Color.Green);
            double y;
            tmpx = 1;
            y = (double)(1 - centerX) / one;
            y = f((double)(1 - centerX) / one);
            tmpy = Convert.ToInt32(centerY - one * y);
            for (int i = 2; i < XX; i++)
            {
                y = f((double)(i - centerX) / one);
                if ((centerY - one * y <= YY) && (centerY - one * y >= 0))
                {
                    e.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * y)));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * y));

            }
            pens = new Pen(Color.Red);
            int start;
            if (plus == false) {
                start = 0;
                tmpx = 1;
            }
            else
            {
                start = centerX;
                tmpx = start;
            }
            y = (double)(start + 1 - centerX) / one;
            y = g_graphic((double)(start - centerX) / one);
            tmpy = Convert.ToInt32(centerY - one * y);
            for (int i = start + 2; i < XX; i++)
            {
                y = g_graphic((double)(i - centerX) / one);
                if ((centerY - one * y <= YY) && (centerY - one * y >= 0))
                {
                    e.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * y)));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * y));

            }
        }

        void print_a()
        {
            label1.Text = "";
            for (int i = 0; i < N; i++) {
                label1.Text += " " + String.Format("{0, 7:0.0000}", a[i]);
            }
        }
    }
}
