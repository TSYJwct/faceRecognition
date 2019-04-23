#include "faceDetector.h"
#include "qdebug.h"

#include <iostream>
using namespace std;

FaceDetector::FaceDetector(std::string names_file, std::string cfg_file, std::string weights_file)
{
	//��ʼ�������
	this->names_file = names_file;
	this->cfg_file = cfg_file;
	this->weights_file = weights_file;
	initDetector();
}
FaceDetector::~FaceDetector()
{
	if (detector)
	{
		delete detector;
		detector = NULL;
	}
}

std::vector<std::string> FaceDetector::objects_names_from_file(std::string const filename)
{
	std::ifstream file(filename);
	std::vector<std::string> file_lines;
	if (!file.is_open()) return file_lines;
	for (std::string line; getline(file, line);) file_lines.push_back(line);

	return file_lines;
}


void FaceDetector::initDetector()
{
	obj_names = objects_names_from_file(names_file);
	detector = new Detector(cfg_file, weights_file);
}

/**
��ʼ���
���������cv::Mat - ԭʼͼ��
���������cv::Mat - �����ͼ�񣨻���
*/
cv::Mat FaceDetector::drawFaceBoxes(cv::Mat picture)
{
	// auto start = std::chrono::steady_clock::now();//��¼��⿪ʼʱ��
	std::vector<bbox_t> result_vec = faceDetectBoxes(picture);
	//auto end = std::chrono::steady_clock::now();//��¼������ʱ��
	// std::chrono::duration<double> spent; //= end - start;//���ʱ��

	draw_boxes(picture, result_vec, obj_names, 1.2);//����

	return picture;//���ؼ�����ͼƬ���ѻ���
}
/**
��ʼ���
���������cv::Mat - ԭʼͼ��
���������cv::Mat - �����ͼ�񣨻���
*/
std::vector<bbox_t> FaceDetector::faceDetectBoxes(cv::Mat picture)
{
	int width = picture.cols - 1;
	int height = picture.rows - 1;
	std::vector<bbox_t> result_vec_new;
	std::vector<bbox_t> result_vec = detector->detect(picture);  //��������� - ��⣬���bounding boxes
	for (auto data : result_vec) {
		/*if (data.prob < theta) {
		continue;
		}*/
		// qDebug() <<"src rect:" << data.x << " " << data.y << " " << data.w << " " << data.h;
		int x2 = data.x + data.w;
		int y2 = data.y + data.h;
		data.w = (x2 > width ? data.w - (x2 - width) : data.w);
		data.h = (y2 > height ? data.h - (y2 - height) : data.h);
		data.x = (data.x < 0 ? 0 : data.x);
		data.y = (data.y < 0 ? 0 : data.y);
		data.x = (data.x > width ? width : data.x);
		data.y = (data.y > height ? height : data.y);
		// qDebug() << "process rect:" << data.x << " " << data.y << " " << data.w << " " << data.h;
		result_vec_new.push_back(data);
	}
	return result_vec_new;
}