/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

// This original code was written by
//	Onkar Raut
// 	Graduate Student,
//	University of North Carolina at Charlotte

#include "polyfit.h"

using namespace cv;

void cvPolyfit(cv::Mat &src_x, cv::Mat &src_y, cv::Mat &dst, int order)
{
	CV_FUNCNAME("cvPolyfit");
	__CV_BEGIN__;
	{
		CV_ASSERT((src_x.rows>0)&&(src_y.rows>0)&&(src_x.cols==1)&&(src_y.cols==1)
				&&(dst.cols==1)&&(dst.rows==(order+1))&&(order>=1));
		Mat X;
		X = Mat::zeros(src_x.rows, order+1,CV_64FC1); // Was CV_32FC1
		Mat copy;
		for(int i = 0; i <=order;i++)
		{
			copy = src_x.clone();
			pow(copy,i,copy);
			Mat M1 = X.col(i);
			copy.col(0).copyTo(M1);
		}
		Mat X_t, X_inv;
		transpose(X,X_t);
		Mat temp = X_t*X;
		Mat temp2;
		invert (temp,temp2);
		Mat temp3 = temp2*X_t;
		Mat W = temp3*src_y;
#ifdef DEBUG
		cout<<"PRINTING INPUT AND OUTPUT FOR VALIDATION AGAINST MATLAB RESULTS\n";
		cout<<"SRC_X: "<<src_x<<endl;
		cout<<"SRC_Y: "<<src_y<<endl;
		cout<<"X: "<<X<<endl;
		cout<<"X_T: "<<X_t<<endl;
		cout<<"W:"<<W<<endl;
#endif
		dst = W.clone();
	}
	__CV_END__;
}
