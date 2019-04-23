#pragma once
#include <opencv2/opencv.hpp>
#include "datastructcommon.h"
#include "dbg.h"
#include "FaceLandmarkAPI.h"
#include "alignment\PointDetector2.h"
class FaceLandmarkAPI;

class FaceAlignment
{
public:
	FaceAlignment(int mode);
	FaceAlignment();
	~FaceAlignment();
	// ����궨�ĵ�
	void landmarkFace(cv::Mat faceImage ,bbox_t bbox,std::vector<cv::Point2f>&landmark);
	// ������������
	void alignFace(cv::Mat landmarkFace, std::vector<cv::Point2f>landmarkPoints,cv::Mat &alignFaceImg);
	// ת������ϵ
	void transformImgAndPoint(cv::Mat srcImg, bbox_t bbox,int imageSize,cv::Mat &detectImg, std::vector<cv::Point2f> &landkmarkPoint);
private:
	// dlib 
	FaceLandmarkAPI * mFaceLandmarkAPI = NULL;
	std::string landmarkModelFile = "../model/shape_predictor_68_face_landmarks.dat";
	// seta landmark
	seeta::PointDetector2 *seetaLandmark = NULL;
	char *seetaModel = "../model/SeetaPointDetector2.0.pts5.ats";
	//ʶ�����Ļ�ȡfeature�Ľӿ�
	int alignType = 0; // 0�������seetaFace2,1�������dlib

};

