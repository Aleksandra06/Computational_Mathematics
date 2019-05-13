using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace lab_5
{
    public partial class Form1 : Form
    {
        int XX, YY;
        int centerX, centerY, one;

        const int n = 3;
        const int N = 4;
        const double shag = 0.1;
        const double h = 0.2;
        double[] X;//xi=x0+i*h

        public Form1()
        {
            InitializeComponent();

            XX = pictureBox1.Width;
            YY = pictureBox1.Right;
            centerX = (int)XX / 2;
            centerY = (int)YY / 2;
            one = (int)centerX / 10;
            X = new double[n + 1];
            X[0] = 1;
            for (int i = 1; i <= n; i++)
            {
                X[i] = X[i - 1] + h;
            }
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

        private void graphics_origin(PaintEventArgs g)
        {
            Pen GreenPen = new Pen(Color.Green);
            int tmpx = 1;
            int tmpy = Convert.ToInt32(centerY - one * f((double)(1 - centerX) / one));
            for (int i = 2; i < XX; i++)
            {
                if ((centerY - one * f((double)(i - centerX) / one) <= YY) && (centerY - one * f((double)(i - centerX) / one) >= 0))
                {
                    g.Graphics.DrawLine(GreenPen, tmpx, tmpy, i, (int)(centerY - (one * f((double)(i - centerX) / one))));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * f((double)(i - centerX) / one)));

            }
            Font myfont = new Font("Arial", 7);
            g.Graphics.DrawLine(GreenPen, XX - 60, 10, XX - 40, 10);
            g.Graphics.DrawString("1/x", myfont, Brushes.Black, new Point(XX - 37, 5));
            for (int i = 0; i <= n; i++)
            {
                g.Graphics.DrawRectangle(Pens.Black, (int)(centerX + X[i] * one), (int)(centerY - (one * f(X[i]))), 1, 1);
            }
        }

        private void graphics_lagrang(PaintEventArgs g)
        {
            Pen pens = new Pen(Color.Coral);
            int tmpx = 1;
            int tmpy = Convert.ToInt32(centerY - one * lagrang((double)(1 - centerX) / one));
            for (int i = 2; i < XX; i++)
            {
                if ((centerY - one * lagrang((double)(i - centerX) / one) <= YY) && (centerY - one * lagrang((double)(i - centerX) / one) >= 0))
                {
                    g.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * lagrang((double)(i - centerX) / one))));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * lagrang((double)(i - centerX) / one)));

            }
            Font myfont = new Font("Arial", 7);
            g.Graphics.DrawLine(pens, XX - 60, 20, XX - 40, 20);
            g.Graphics.DrawString("Лагранж", myfont, Brushes.Black, new Point(XX - 37, 15));
        }

        public void graphics_aitken(PaintEventArgs g)
        {
            Pen pens = new Pen(Color.RosyBrown);
            int tmpx = 1;
            int tmpy = Convert.ToInt32(centerY - one * aitken((double)(1 - centerX) / one));
            for (int i = 2; i < XX; i++)
            {
                if ((centerY - one * aitken((double)(i - centerX) / one) <= YY) && (centerY - one * aitken((double)(i - centerX) / one) >= 0))
                {
                    g.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * aitken((double)(i - centerX) / one))));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * aitken((double)(i - centerX) / one)));

            }
            Font myfont = new Font("Arial", 7);
            g.Graphics.DrawLine(pens, XX - 60, 20, XX - 40, 20);
            g.Graphics.DrawString("Эйткин", myfont, Brushes.Black, new Point(XX - 37, 15));
        }

        public void graphics_newton(PaintEventArgs g)
        {
            Pen pens = new Pen(Color.Red);
            int tmpx = 1;
            int tmpy = Convert.ToInt32(centerY - one * newton((double)(1 - centerX) / one));
            for (int i = 2; i < XX; i++)
            {
                if ((centerY - one * newton((double)(i - centerX) / one) <= YY) && (centerY - one * newton((double)(i - centerX) / one) >= 0))
                {
                    g.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * newton((double)(i - centerX) / one))));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * newton((double)(i - centerX) / one)));

            }
            Font myfont = new Font("Arial", 7);
            g.Graphics.DrawLine(pens, XX - 60, 20, XX - 40, 20);
            g.Graphics.DrawString("Ньютон", myfont, Brushes.Black, new Point(XX - 37, 15));
        }
        
        public void graphics_spline(PaintEventArgs g)
        {
            int ch = 0;
            Pen pens = new Pen(Color.Blue);
            int tmpx = 1;
            int tmpy = Convert.ToInt32(centerY - one * spline((double)(1 - centerX) / one));
            for (int i = 2; i < XX; i++)
            {
                if (spline((double)(i - centerX) / one) != 0)
                {
                    if (ch == 0) ch++;
                    else

                if ((centerY - one * spline((double)(i - centerX) / one) <= YY) && (centerY - one * spline((double)(i - centerX) / one) >= 0))
                    {
                        g.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * spline((double)(i - centerX) / one))));
                    }
                    tmpx = i;
                    tmpy = (int)(centerY - (one * spline((double)(i - centerX) / one)));
                }
            }
            Font myfont = new Font("Arial", 7);
            g.Graphics.DrawLine(pens, XX - 60, 20, XX - 40, 20);
            g.Graphics.DrawString("Сплайн", myfont, Brushes.Black, new Point(XX - 37, 15));
        }
        
        private double f(double a)
        {
            return 1 / a;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            osi(e);
            if (radioButton1.Checked == true) { graphics_lagrang(e); graphics_origin(e); }
            if (radioButton2.Checked == true) { graphics_aitken(e); graphics_origin(e); }
            if (radioButton3.Checked == true) { graphics_newton(e); graphics_origin(e); }
            if (radioButton4.Checked == true) { graphics_spline(e); graphics_origin(e); }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (centerY > 10)
            {
                centerY = centerY - 10;
                pictureBox1.Invalidate();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (centerX < XX - 20)
            {
                centerX = centerX + 10;
                pictureBox1.Invalidate();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (centerY < YY - 20)
            {
                centerY = centerY + 10;
                pictureBox1.Invalidate();
            }
        }

        private void button2_Click(object sender, EventArgs e)
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

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        private double l_composition_ch(int i, double X0)
        {
            double otvet = 1;
            for (int j = 0; j < i; j++)
            {
                otvet = otvet * (X0 - X[j]);
            }
            for (int j = i + 1; j <= n; j++)
            {
                otvet = otvet * (X0 - X[j]);
            }
            return otvet;
        }

        private double l_composition_zn(int i)
        {
            double otvet = 1;
            for (int j = 0; j < i; j++)
            {
                otvet = otvet * (X[i] - X[j]);
            }
            for (int j = i + 1; j <= n; j++)
            {
                otvet = otvet * (X[i] - X[j]);
            }
            return otvet;
        }

        private double lagrang(double X0)
        {
            double P = 0;
            for (int i = 0; i <= n; i++)
            {
                P = P + f(X[i]) * l_composition_ch(i, X0) / l_composition_zn(i);
            }
            return P;
        }

        public double aitken(double X0)
        {
            double[] Px = new double[n + 1];
            for (int i = 0; i <= n; i++)
            {
                Px[i] = f(X[i]);
            }
            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j <= n - i; j++)
                {
                    Px[j] = (Px[j] * (X0 - X[j + i]) - Px[j + 1] * (X0 - X[j])) / (X[j] - X[j + i]);
                }
            }
            return Px[0];
        }

        public double newton(double X0)
        {
            double P = 0;

            double[,] y = new double[n + 1, n + 1];

            for (int i = 0; i <= n; i++)
                y[i, 0] = f(X[i]);

            for (int j = 1; j <= n; j++)
                for (int i = 0; i <= n - j; i++)
                    y[i, j] = y[i + 1, j - 1] - y[i, j - 1];

            double q = (X0 - X[0]) / h;
            double q_buf = q;
            double fact = 1;
            double y0 = y[0, 0];
            P = y0;
            for (int i = 1; i <= n; i++)
            {
                if (i > 1) q_buf *= (q - (i - 1));
                fact *= i;
                P += (y[0, i] * q_buf) / fact;
            }
            return P;
        }

        ///Сплайн///На графики это конечная кривая, почти перекрытая оригинальной ф-ей. Чтоб что-то увидеть, нужно приблизить
        public double[] mi = new double[N];
        public double[,] a = new double[N, N];
        public double[] x = new double[N];
        public double[] b = new double[N];
        
        public void gaus()
        {
            double t, s;
            double[] x = new double[N];
            int i, j, k;
            for (k = 0; k < N - 1; k++)
            {
                for (i = k + 1; i < N; i++)
                {
                    t = a[i,k] / a[k,k];
                    b[i] = b[i] - t * b[k];
                    for (j = 0; j < N; j++)
                        a[i,j] = a[i,j] - t * a[k,j];
                }
            }
            for (k = N - 1; k >= 0; k--)
            {
                s = 0;
                for (j = k + 1; j < N; j++)
                    s += a[k,j] * x[j];
                x[k] = (b[k] - s) / a[k,k];
            }
            for (i = 0; i< N; i++)
            {
                mi[i] = x[i];
            }
        }

        public double proiz(int i)
        {
            double res;
            if (i == 0)
                res = (f(x[1]) - f(x[0])) / (x[1] - x[0]);
            else if (i == N - 1)
                res = (f(x[N - 1]) - f(x[N - 2])) / (x[N - 1] - x[N - 2]);
            else
                res = (f(x[i + 1]) - f(x[i - 1])) / (x[i + 1] - x[i - 1]);
            return res;
        }

        public void mit()
        {
            int i, j;
            double h;
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N; j++)
                    a[i,j] = 0;
                if (i == 0 || i == N - 1) a[i,i] = 1;
                else
                {
                    a[i,i - 1] = 1;
                    a[i,i] = 4;
                    a[i,i + 1] = 1;
                    h = x[i] - x[i - 1];
                    if (i != 0 && i != N - 1)
                        b[i] = 3 * (f(x[i + 1]) - f(x[i - 1])) / h; //система из n+1 линейных уравнений относительно неизвестных m(i)
                }
                if (i == 0) b[i] = proiz(0);
                else if (i == N - 1) b[i] = proiz(N - 1);
            }
            gaus();
        }

        public double spline_it(double X0)
        {
            int i;
            double sp = 0, drob1, drob2, drob3, drob4, xstep;

            for (i = 1; i < N; i++)
            {
                if (x[i - 1] <= X0 && X0 <= x[i])
                {
                    xstep = x[i] - x[i - 1];// Интерполяционный кубический сплайн
                    drob1 = (X0 - x[i]) * (X0 - x[i]) * (2 * (X0 - x[i - 1]) + xstep) / Math.Pow(xstep, 3);
                    drob2 = (X0 - x[i - 1]) * (X0 - x[i - 1]) * (2 * (x[i] - X0) + xstep) / Math.Pow(xstep, 3);
                    drob3 = (X0 - x[i]) * (X0 - x[i]) * (X0 - x[i - 1]) / Math.Pow(xstep, 2);
                    drob4 = (X0 - x[i - 1]) * (X0 - x[i - 1]) * (X0 - x[i]) / Math.Pow(xstep, 2);
                    sp = f(x[i - 1]) * drob1 + f(x[i]) * drob2 + mi[i - 1] * drob3 + mi[i] * drob4;
                }
            }
            return sp;
        }
        
        public double spline(double X0)
        {
            x[0] = 1;
            for (int i = 1; i < N; i++)
            {
                x[i] = x[i - 1] + h;
            }
            double sp;
            mit();
            sp = spline_it(X0);
            return sp;
        }

    }
}
