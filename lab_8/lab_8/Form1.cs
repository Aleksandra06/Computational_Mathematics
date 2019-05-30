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

        const int N = 4;
        double[] X = { 0, 1, 2, 3};
        double[] Y;
        double[,] C;
        double[] B;
        //double y, x;

        double[,] matrix;
        double[] otvet;
        double[] buff;
        double[,] f;
        int alfa;

        public Form1()
        {
            InitializeComponent();
            XX = pictureBox1.Width;
            YY = pictureBox1.Right;
            centerX = (int)XX / 2;
            centerY = (int)YY / 2;
            one = (int)centerX / 10;

            Y = new double[N];
            C = new double[N,N];
            B = new double[N];
            matrix = new double[N, N];
            otvet = new double[N];
            buff = new double[N];
            f = new double[1, 1];
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

        void PoiPeres(int i)
        {
            for (int j = i; j < N - 1; j++)
            {
                if (matrix[j,i] < 0)
                {
                    buff[j] = (-1) * matrix[j,i];
                }
                else
                {
                    buff[j] = matrix[j,i];
                }
            }
            double Maxbuff;
            int t;
            Maxbuff = buff[i];
            for (t = i; t < N - 1; t++)
            {
                if (buff[t] >= Maxbuff)
                {
                    Maxbuff = buff[t];
                    alfa = t;
                }
            }
            if (alfa != i)
            {
                int z = i, k;
                for (k = i; k < N; k++)
		        {
                    if (z < N) return;
                    f[i,i] = matrix[i,z];
                    matrix[i,z] = matrix[alfa,k];
                    matrix[alfa,k] = f[i,i];
                    z++;
                }
            }
        }

        void Gauss()
        {
            int i, j, k;
            double d;
            for (i = 0; i < N - 2; i++)
            {
                PoiPeres(i);
                for (j = i + 1; j < N - 1; j++)
                {
                    d = (matrix[j,i] / matrix[i,i]);
                    for (k = i; k < N; k++)
                        matrix[j,k] -= (matrix[i,k] * d);
                }
            }
            otvet[N - 2] = matrix[N - 2,N - 1] / matrix[N - 2,N - 2];
            for (i = N - 3; i >= 0; i--)
            {
                for (j = 0, d = 0; j < N - i - 2; j++)
                    d += (otvet[N - j - 2] * matrix[i,N - j - 2] * (-1));
                otvet[i] = (matrix[i,N - 1] + d) / matrix[i,i];
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

        double ChtoY(double i)
        {
            double S = otvet[0] + (otvet[1]) * i + (otvet[2]) * i * i;
            return S;
        }

        double g(double x, int l)
        {
            if (l == 0)
                return 1;
            if (l == 1)
                return x;
            if (l == 2)
                return x * x;
            return 0;
        }

        void apr(PaintEventArgs e)
        {
            int tmpx, tmpy;
            for (int i = 0; i < N; i++)
            {
                Y[i] = Math.Pow(X[i], 3);
                if ((0 < (int)(centerX + X[i] * one) || (int)(centerX + X[i] * one) < XX) && ((int)(centerY - (one * Math.Pow(X[i], 3))) > 0 || (int)(centerY - (one * Math.Pow(X[i], 3))) < YY))
                    e.Graphics.DrawRectangle(Pens.Black, (int)(centerX + X[i] * one), (int)(centerY - (one * Math.Pow(X[i], 3))), 1, 1);
            }
            for (int p = 0; p < N; ++p)
            {
                for (int j = 0; j < N; ++j)
                    C[p,j] = 0;
                B[p] = 0;
            }
            for (int p = 0; p < (N - 1); ++p)
                for (int j = 0; j < (N - 1); ++j)
                    for (int l = 0; l < N; ++l)
                        C[p,j] += g(X[l], p) * g(X[l], j);
            for (int p = 0; p < (N - 1); ++p)
                for (int j = 0; j < N; ++j)
                    B[p] += Y[j] * g(X[j], p);
            for (int i = 0; i < (N - 1); ++i)
            {
                matrix[i,N - 1] = B[i];
                for (int j = 0; j < (N - 1); ++j)
                    matrix[i,j] = C[i,j];
            }
            Gauss();
            /*for (double i = -10; i < 10.1; i++)
            {
                y = ChtoY(i);
            }*/
            Pen pens = new Pen(Color.Red);
            tmpx = 1;
            tmpy = Convert.ToInt32(centerY - one * ChtoY((double)(1 - centerX) / one));
            for (int i = 2; i < XX; i++)
            {
                if ((centerY - one * ChtoY((double)(i - centerX) / one) <= YY) && (centerY - one * ChtoY((double)(i - centerX) / one) >= 0))
                {
                    e.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * ChtoY((double)(i - centerX) / one))));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * ChtoY((double)(i - centerX) / one)));

            }
        }
    }
}
