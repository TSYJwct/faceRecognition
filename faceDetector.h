/*��һ����װ yolo  �����*/
/*   ԭʼͼƬ   ->    ������bbox_t    */

#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include "yolo.h"
#include "alignment\FaceDetector2.h"
#include "dbg.h"
#include <vector>
#include <string>


class FaceDetector {
public:
	FaceDetector(std::string names_file, std::string cfg_file, std::string weights_file);
	~FaceDetector();

	/*  ���         */
	cv::Mat drawFaceBoxes(cv::Mat);//���ػ��ÿ��ͼƬ
	std::vector<bbox_t> faceDetectBoxes(cv::Mat); //����bbox_t
	
private:
	/*  �����   */
	Detector *detector;
	seeta::FaceDetector2 *FD;
	/*  ��ʼ�������  */
	void initDetector();

	/*  �ͼ������صĺ���    */
	std::vector<std::string> objects_names_from_file(std::string);

	/*   ����   */
	std::vector<std::string> obj_names;
	std::string names_file = "../data/face.names";
	std::string cfg_file = "../cfg/yolov3-spp-focal_loss-test.cfg";
	std::string weights_file = "../model/yolov3-spp-focal_loss_12000.weights";
	float theta = 0.7;
	int detectType = 0; // 0 mean yolo,1 mean seeta
};
#endif

