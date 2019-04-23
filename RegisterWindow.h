#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "faceDetector.h"
#include "faceRecognition.h"
#include "faceAlignment.h"

#include "sqlSplite.h"

class RegisterWindow : public QWidget
{
	Q_OBJECT

public:
	//QWidget *parent, 
	RegisterWindow(FaceDetector *faceDetector, FaceAlignment *faceAlignment, FaceRecognition *faceRecognition);
	~RegisterWindow();

	//��ʼ������
	void initView();

	//�ͷŽ���
	void cleanView();
	//
	void paintEvent(QPaintEvent *e);

	//��ʼ������ͷ
	void initCapture();


private slots:
	void shotButtonSlot();
	void confirmButtonSlot();
	void quitButtonSlot();
	void quitSlot();
private:
	/*   ����� & ����ͷ & ʶ����  ���Ǵ�MainWindow�д��ݹ���*/
	/*  �����   */
	FaceDetector * faceDetector;
	/* ����*/
	FaceAlignment  *faceAlignment;
	/*  ʶ����   */
	FaceRecognition *faceRecognition;
	/*  ����ͷ   */
	cv::VideoCapture capture;

	bool hasOpen = false;  //�ж�����ͷ�Ƿ��Ǵ򿪵�״̬
						   /*  ���ݽṹ   */
	struct FaceStructParam rFaceStructParam;  //ע�����ĺ������ݽṹ
	cv::Mat img;

	struct InformationParam infParam;

	SqlSplite *sqlSplite = NULL;


	QLabel *mainShow;
	QLabel *subShow;

	QLabel *nameLabel;
	QLineEdit *nameEdit;
	QLabel *noLabel;
	QLineEdit *noEdit;
	QLabel *collegeLabel;
	QLineEdit *collegeEdit;
	QLabel *classLabel;
	QLineEdit *classEdit;

	QPushButton *shotButton;//���㰴ť
	QPushButton *confirmButton;//ȷ�ϰ�ť
	QPushButton *quitButton;//�˳���ť

	bool checkInformation();
};


#endif // REGISTERWINDOW_H
