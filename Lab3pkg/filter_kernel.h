#ifndef FILTER_KERNEL_H
#define FILTER_KERNEL_H


#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>


class filter_kernel
{

private:

    int TYPE = CV_32F;

    int rows = 0, cols = 0;
    float divider = 1;
    float *matrix = nullptr;

    void recreate_matrix(
        int old_rows, int old_cols,
        int rows, int cols
    );


public:

    filter_kernel();
    filter_kernel(int rows, int cols, float divider, float *matrix);
    filter_kernel(const filter_kernel &other);

    int get_rows()
    {
        return rows;
    }
    int get_cols()
    {
        return cols;
    }
    int get_divider()
    {
        return divider;
    }
    float *get_matrix()
    {
        return matrix;
    }

    void set_rows(int new_value);
    void set_cols(int new_value);
    void set_divider(int new_value);

    ~filter_kernel();


    cv::Mat to_cv_Mat() const;

};

namespace filter_kernel_const
{
    extern const filter_kernel NINEFILTER;
    extern const filter_kernel GAUSSIAN;
}

#endif
