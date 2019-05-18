#ifndef __FACELANDMARKAPI_H__
#define __FACELANDMARKAPI_H__

#include <opencv2/opencv.hpp>

#define FLAPI __declspec(dllexport)

class FaceLandmarkBase;

class FLAPI FaceLandmarkAPI
{
public:
	FaceLandmarkAPI();
	~FaceLandmarkAPI();

	void loadModel(std::string &faceLandmarksPath);

	/**
	* @brief landmarkFaces                 �����궨����ģ��
	* @param faceImage                     ����ͼƬ
	* @param faceLandmarks                 ����������
	* @return null
	*
	* @note
	*/
	void landmarkFaces(const cv::Mat &faceImage, std::vector<cv::Point> &faceLandmarks);

private:
	FaceLandmarkBase *mFaceLandmarkBase;

};


#endif // __FACELANDMARKAPI_H__