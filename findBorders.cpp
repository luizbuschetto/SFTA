#include "findBorders.h"

// Aqui estou retornando um par porque assim eu posso criar uma matriz do tamanho
// que eu preciso em sfta.c. Assim, eu não preciso rodar duas vezes o laço.
pair <Mat, int> findBorders(Mat I)
{
      Mat Im = Mat::zeros(I.rows, I.cols, I.type());
      copyMakeBorder(I, I, 1, 1, 1, 1, BORDER_CONSTANT, 255); // I = padarray(I, [1, 1], 1);
      int h = Im.rows;
      int w = Im.cols;

      bool bkgFound = false;
      int vals_size = 0;

      for(int row = 0; row < h; row++)
      {
          for(int col = 0; col < w; col++)
          {
              if (I.at<float>(row + 1, col + 1) == 255)
              {
                  bkgFound = false;

                  for (int i = 0; i <= 2; i++)
                  {
                      for (int j = 0; j <= 2; j++)
                      {
                          if (I.at<float>(row + i, col + j) == 0)
                          {
                              Im.at<float>(row, col) = 255;
                              vals_size++;
                              bkgFound = true;
                              break;
                          }
                      }

                      if (bkgFound)
                          break;
                  }
              }
          }
      }

      pair <Mat, int> values (Im, vals_size);
      return values;
}
