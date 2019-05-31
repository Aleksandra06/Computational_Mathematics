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
        
        const int n = 4;
        //const int X = 5;

        public Form1()
        {
            InitializeComponent();
            XX = pictureBox1.Width;
            YY = pictureBox1.Right;
            centerX = (int)XX / 2;
            centerY = (int)YY / 2;
            one = (int)centerX / 10;
        }

        void GAUS(double[,] Matrix, int N, int M, double[] MassM, int G)
        {

            //Приведение матрицы к треугольному виду
            for (int i = 0; i < M - 2; i++)
            {
                //Вставка Максимального по модулю элемента на диагональ
                //SearchMaxElem(Matrix, N, M, i);

                for (int j = 1; j < N - i; j++)
                {
                    //Зануление столбца
                    Iter(Matrix, M, j, i);
                }
            }
            //Подсчёт корней на обратном ходу
            Result(Matrix, N, M, MassM, G);

            //return 0;
        }

        //Зануление выбранного элемента
        void Iter(double[,] Matrix, int M, int Row, int Coll)
        {
            double[] Str = new double[M];
            double mnoj;
            //Вычисление множителя для строки
            mnoj = -1 * (Matrix[Coll + Row,Coll] / Matrix[Coll,Coll]);

            for (int i = 0; i < M; i++)
            {
                //Умножение строки с ведущим элементом на множитель
                Str[i] = Matrix[Coll,i] * mnoj;

                //Сложение строки с ведущим элементом с текущей
                Matrix[Coll + Row,i] = Matrix[Coll + Row,i] + Str[i];
            }
        }

        //Вычисление корней
        void Result(double[,] Matrix, int N, int M, double[] MassM, int G)
        {
            //Кол-во решений
            int CountX = M - 1;
            //Кол-во рассматриваемых строк для случая когда строк больше чем корней
            N = N - (N - CountX);
            //Массив ответов
            double[] Answer = new double[CountX];
            for (int i = 0; i < CountX; i++)
            {
                Answer[i] = 0;
            }
            bool flag = false;
            double Summ = 0;

            //Проход по всем строкам
            for (int j = 0, z = 1; j < CountX; j++, z++)
            {
                int Error = 0;
                //Проход по текущей строке
                for (int i = 0; i < CountX; i++)
                {
                    //Сумма всех изветсных величин
                    Summ = Summ + (Matrix[N - z,i] * Answer[i] * -1);
                    if (Matrix[N - z,i] == 0) { Error++; }
                }
                if (Error == CountX)
                {
                    flag = true;
                    break;
                }
                //Прибавление правой части к сумме
                Summ = Summ + Matrix[N - z,M - 1];
                //Деление Суммы на коэффициент корня
                Answer[CountX - z] = Summ / Matrix[N - z,CountX - z];
                Summ = 0;
                Error = 0;
            }

            if (flag == true) ;//{ cout << "Ne imeet Resheniy ili imeet inf korney"; }
            else
            {
                //Вывод корней на экран
                for (int i = 0; i < M - 1; i++)
                {
                    if ((i != 0) || (i != (G - 1)))
                    {
                        MassM[i + 1] = Answer[i];
                    }
                }
            }
        }

        //Вставка Максимального по модулю элемента на диагональ
        void SearchMaxElem(double[][] Matrix, int N, int M, int D)
        {
            double MaxElem = 0;
            int MaxColl = 0;
            int MaxRow = 0;

            //Поиск максимального по модулю элемента
            for (int i = D; i < N; i++)
            {
                for (int j = D; j < M - 1; j++)
                {
                    if (Math.Abs(Matrix[i][j]) > Math.Abs(MaxElem))
                    {
                        MaxElem = Matrix[i][j];
                        MaxColl = j;
                        MaxRow = i;
                    }
                }
            }
            double temp;
            //Если элемент лежит не на диагонали
            if (Matrix[D][D] != MaxElem)
            {
                //Если не на том столбце
                if (MaxColl != D)
                {
                    for (int i = 0; i < N; i++)
                    {
                        temp = Matrix[i][D];
                        Matrix[i][D] = Matrix[i][MaxColl];
                        Matrix[i][MaxColl] = temp;
                    }
                }
                //Если не на той строке
                if (MaxRow != D)
                {
                    for (int i = 0; i < M; i++)
                    {
                        temp = Matrix[D][i];
                        Matrix[D][i] = Matrix[MaxRow][i];
                        Matrix[MaxRow][i] = temp;
                    }
                }
            }
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

        

        

        void apr(PaintEventArgs e)
        {
            int tmpx, tmpy;
            

            double[] MassX = new double[n];

            MassX[0] = 0;
            MassX[1] = 1;
            MassX[2] = 2;
            MassX[3] = 3;

            //Создание и заполнение массива Y-ов
            double[] MassY = new double[n];

            MassY[0] = 0;
            MassY[1] = 1;
            MassY[2] = 4;
            MassY[3] = 9;

            for (int i = 0; i < n; i++)
            {
                double tmp = Math.Pow(MassX[i], 2);
                if ((0 < (int)(centerX + MassX[i] * one) || (int)(centerX + MassX[i] * one) < XX) && ((int)(centerY - (one * Math.Pow(MassX[i], 2))) > 0 || (int)(centerY - (one * Math.Pow(MassX[i], 2))) < YY))
                    e.Graphics.DrawRectangle(Pens.Black, (int)(centerX + MassX[i] * one), (int)(centerY - (one * Math.Pow(MassX[i], 2))), 1, 1);
            }

            double[,] C = new double[3,4];

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    C[i,j] = 0;
                }
            }

            C[0,2] = 3;

            for (int i = 0; i < 4; i++)
            {
                C[0,1] += MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[0,0] += Math.Sqrt(MassX[i]);
            }

            for (int i = 0; i < 4; i++)
            {
                C[1,2] += MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[1,1] += MassX[i] * MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[1,0] += Math.Sqrt(MassX[i]) * MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[2,2] += Math.Sqrt(MassX[i]);
            }

            for (int i = 0; i < 4; i++)
            {
                C[2,1] += Math.Sqrt(MassX[i]) * MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[2,0] += MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[0,3] += MassY[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[1,3] += MassY[i] * MassX[i];
            }

            for (int i = 0; i < 4; i++)
            {
                C[2,3] += Math.Sqrt(MassX[i]) * MassY[i];
            }

            double[] MassM = new double[4];
            for (int i = 0; i < 4; i++)
            {
                MassM[i] = 0;
            }

            //Решение матрицы
            GAUS(C, 3, 4, MassM, 4);


            double y;
            Pen pens = new Pen(Color.Red);
            tmpx = 300; 
            y = MassM[1] * Math.Sqrt((double)(300 - centerX) / one) + MassM[2] * (double)(300 - centerX) / one + MassM[3];
            tmpy = Convert.ToInt32(centerY - one * y);
            for (int i = 301; i < XX; i++)
            {
                y = MassM[1] * Math.Sqrt((double)(i - centerX) / one) + MassM[2] * (double)(i - centerX) / one + MassM[3];
                if ((centerY - one * y <= YY) && (centerY - one * y >= 0))
                {
                    e.Graphics.DrawLine(pens, tmpx, tmpy, i, (int)(centerY - (one * y)));
                }
                tmpx = i;
                tmpy = (int)(centerY - (one * y));

            }
        }
    }
}
