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