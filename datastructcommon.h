/*  ������ݽṹ  */

#ifndef __DATASTRUCTCOMMON_H__
#define __DATASTRUCTCOMMON_H__

#include <opencv2/opencv.hpp>
#include "yolo.h"
#include "mxnet_inference.h"
#include "common.h"

/*!< ���ݱ�ע�ṹ�� - ���� */
//FaceStructParm   ����һ��ͼƬ
//FaceStructParm   ����һ��ͼƬ��ÿһ������

struct FaceStructParam {

	cv::Mat image;											/*!< ԭʼͼƬ */
	cv::Mat detImage;                                       /*!< ���֮���ͼƬ������ */
	// std::vector<bbox_t> vbox;                               /*!< ����λ��              */
	// cv::Mat tailorFace;                                     //��Ųü��������Mat
	// cv::Mat alignFace;                                      //��Ŷ��������ͼƬ
	std::vector<cv::Point2f> landmarkPoints;                  //��ű궨��

	struct FaceParam {										/*!< �������� */
		bbox_t detectBox;                                   /*!< �������� - �������� */
		std::vector<cv::Point2f> landmarks;					/*!< �������� - �����ؼ��� */
		int id = -1;										/*!< �������� - ����ID��� */
		NDArray featureMap;                                 /*!< �������� - ��������ֵ */
		float score;                                        /*!< �������� - �������ƶ� */
		cv::Mat alignFace;                                   /*!< �������� - ��������� */
	};
	std::vector<FaceParam> faceParams;						/*!< ����������Ϣ */
	//NDArray featureMap;                                     //���alignface��featureMap
	//float score;                                            //���������ݿ��������ıȽϵ÷�
};
//public:
//	void setImage(cv::Mat i);
//	void setDetImage(cv::Mat det);
//	void setVBox(std::vector<bbox_t> vb);
//	void setTailorFace(cv::Mat tailor);
//	void setAlignFace(cv::Mat align,int i);
//	void setLandmarkPoints(std::vector<cv::Point2f> landmark);
//	void setFeatureMap(NDArray tmp);
//	void setScore(float s);
//
//	cv::Mat getImage();
//	cv::Mat getDetImage();
//	std::vector<bbox_t> getVBox();
//	cv::Mat getTailorFace();
//	cv::Mat getAlignFace();
//	std::vector<cv::Point2f> getLandmarkPoints();
//	NDArray getFeatureMap();
//	float getScore();
//
//	void clearVBox();
//
//	//std::vector<cv::Mat> recFace;//��Ųü��������Mat
//	//std::vector<cv::Mat> alignmentFace;//��Ŷ���������Mat
//	//std::vector<std::vector<cv::Point> > landmarkPoints;  //���������5���궨��
//	// TODO �ɸ���ʵ���������
//};
//
//inline void FaceStructParam::setImage(cv::Mat i) {
//	i.copyTo(image);
//}
//inline void FaceStructParam::setDetImage(cv::Mat det) {
//	detImage = det.clone();
//}
//inline void FaceStructParam::setVBox(std::vector<bbox_t> vb) {
//	std::vector<bbox_t> tmp;
//	this->vbox = tmp;
//	if (vb.size() == 0) {
//		return;
//	}
//	else {
//		for (auto rect : vb) {
//			this->vbox.push_back(rect);
//		}
//	}
//}
//inline void FaceStructParam::setTailorFace(cv::Mat tailor) {
//	tailor.copyTo(tailorFace);
//}
//inline void FaceStructParam::setAlignFace(cv::Mat align) {
//	alignFace = align.clone();
//}
//inline void FaceStructParam::setLandmarkPoints(std::vector<cv::Point2f> landmark) {
//	std::vector<cv::Point2f> landmark5;
//	landmarkPoints = landmark5;
//	for (auto point : landmark) {
//		landmarkPoints.push_back(point);
//	}
//}
//
//inline cv::Mat FaceStructParam::getImage() {
//	return image;
//}
//inline cv::Mat FaceStructParam::getDetImage() {
//	return detImage;
//}
//inline std::vector<bbox_t> FaceStructParam::getVBox() {
//	return vbox;
//}
//inline cv::Mat FaceStructParam::getTailorFace() {
//	return tailorFace;
//}
//inline cv::Mat FaceStructParam::getAlignFace() {
//	return alignFace;
//}
//inline std::vector<cv::Point2f> FaceStructParam::getLandmarkPoints() {
//	return landmarkPoints;
//}
//
//inline void FaceStructParam::clearVBox() {
//	vbox.clear();
//}
//inline NDArray FaceStructParam::getFeatureMap() { return featureMap; }
//inline void FaceStructParam::setFeatureMap(NDArray tmp) { featureMap = tmp; }
//inline void FaceStructParam::setScore(float s) { score = s; }
//inline float FaceStructParam::getScore() { return score; }



/*   ���Edit�е���Ϣ������÷��͵����ݿ���   */
struct InformationParam {
private:
	std::string nameInf;  //����
	std::string noInf;  //ѧ��
	std::string collegeInf;  //ѧԺ
	std::string classInf;  //�༶
	std::string stringFeature;  //�仯��string֮���feature
	std::string pictureRoute; //ͼƬ·��

public:
	void setName(std::string name) { nameInf = name; };
	void setNo(std::string no) { noInf = no; };
	void setCollege(std::string college) { collegeInf = college; };
	void setClass(std::string cl) { classInf = cl; };
	void setPictureRoute(std::string route) { pictureRoute = route; };
	void setStringFeature(std::string sf) { stringFeature = sf; };

	std::string getName() { return nameInf; };
	std::string getNo() { return noInf; };
	std::string getCollege() { return collegeInf; };
	std::string getClass() { return classInf; };
	std::string getPictureRoute() { return pictureRoute; };
	std::string getStringFeature() { return stringFeature; };
};


inline std::string featureMapToString(NDArray featureMap)
{
	std::string stringFeature;
	float value;
	for (int i = 0; i < featureMap.Size(); i++)
	{
		value = featureMap.At(0, i);
		stringFeature = stringFeature + QS(QString::number(value, 'f', 4)) + ",";
	}
	return stringFeature;
}

#endif //__DATASTRUCTCOMMON_H__