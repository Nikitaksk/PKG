#include <iostream>
#include "filter_kernel.h"

filter_kernel::filter_kernel()
{
    rows = 0;
    cols = 0;
    divider = 1;
    matrix = nullptr;
}
filter_kernel::filter_kernel(int rows, int cols, float divider, float *matrix)
{
    this->rows    = rows;
    this->cols    = cols;
    this->divider = divider;
    this->matrix  = matrix;
}
filter_kernel::filter_kernel(const filter_kernel &other)
{
    rows = other.rows;
    cols = other.cols;
    divider = other.divider;

    int matrix_size = rows * cols;
    matrix = new float[matrix_size];
    memcpy(matrix, other.matrix, matrix_size * sizeof(float));
}

void filter_kernel::recreate_matrix(int old_rows, int old_cols, int new_rows, int new_cols)
{
    if (new_rows == 0 || new_cols == 0)
    {
        delete matrix;
        matrix = nullptr;
        return;
    }

    // copying info from old matrix to new
    float *new_matrix = new float[new_rows * new_cols];
    for (int i = 0; i < old_rows && i < new_rows; i++)
    {
        for (int j = 0; j < old_cols && j < new_cols; j++)
        {
            new_matrix[i * new_cols + j] = matrix[i * old_cols + j];
        }
    }
    delete matrix;
    matrix = new_matrix;

    // filling empty spaces with ones
    while (old_rows < new_rows)
    {
        for (int j = 0; j < new_cols; j++)
        {
            new_matrix[old_rows * new_cols + j] = 1;
        }
        ++old_rows;
    }
    while (old_cols < new_cols)
    {
        for (int i = 0; i < new_rows; i++)
        {
            new_matrix[i * new_cols + old_cols] = 1;
        }
        ++old_cols;
    }
}

void filter_kernel::set_rows(int new_value)
{
    recreate_matrix(rows, cols, new_value, cols);
    rows = new_value;
}
void filter_kernel::set_cols(int new_value)
{
    recreate_matrix(rows, cols, rows, new_value);
    cols = new_value;
}
void filter_kernel::set_divider(int new_value)
{
    divider = new_value;
}

filter_kernel::~filter_kernel()
{
    delete[] matrix;
}


cv::Mat filter_kernel::to_cv_Mat() const
{
    // Mat (int rows, int cols, int type, void *data, size_t step=AUTO_STEP)

    int matrix_size = rows * cols;
    float *data = new float[matrix_size];
    memcpy(data, matrix, matrix_size * sizeof(float));

    return cv::Mat(rows, cols, TYPE, data) / divider;
}


const filter_kernel filter_kernel_const::NINEFILTER = filter_kernel(3, 3, 1, new float[9] {
    -1, -1, -1,
    -1, 9, -1,
    -1, -1, -1,
});

const filter_kernel filter_kernel_const::GAUSSIAN = filter_kernel(3, 3, 1, new float[9] {
    1, 2, 1,
    2, 4, 2,
    1, 2, 1,
});
