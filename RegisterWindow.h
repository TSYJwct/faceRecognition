#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>

#include "faceDetector.h"
#include "faceRecognition.h"
#include "faceAlignment.h"

#include "sqlSplite.h"

class RegisterWindow :public QMainWindow
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
	// �ͷ�ģ��
	void releaseModel();
	
	void saveMessage(const QString imagePath="");

	//��ʼ������ͷ
	void initCapture();
	// predict()
	void predictFace(cv::Mat &detectImg);

private slots:
	void shotButtonSlot();
	void confirmButtonSlot();
	void quitButtonSlot();
	void upFaceButtonSlot();
	void upBatchFaceButtonSlot();
	void quitSlot();
	void paintEvent(QPaintEvent *e);
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

	QPushButton *shotButton;    // ���㰴ť
	QPushButton *confirmButton; // ȷ�ϰ�ť
	QPushButton *upFaceButton;   // �ϴ�������Ƭ
	QPushButton *upBatchFaceButton; // �����ϴ���Ƭ
	QPushButton *quitButton;    // �˳���ť
	/*���*/
	QWidget *centralWidget;
	QWidget *subShowWidget;
	QGridLayout *mainGridLayout;
	QGridLayout *rightTopLayout;
	bool checkInformation();
	int registerType = -1;

};


#endif // REGISTERWINDOW_H
