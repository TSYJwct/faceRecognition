#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
//#include "yolo.h"
#include "faceDetector.h"    // ���������
#include "faceAlignment.h"   // �������� 
#include "faceRecognition.h"  // ����ʶ����
#include "datastructcommon.h"  //���ݽṹ
#include "sqlSplite.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>
#include <QFrame>
#include <vector>
#include <string>
#include <qDebug.h>
#include <QCombobox>
#include <QAxObject>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	/*   �ı�ģʽ   */
	void changeMode(int);

	/*  ��ʼ�����溯��   */
	void initView();
	void initMenu();
	void cleanMenu();
	void initLayout();
	void cleanLayout();

	struct InformationParam predictFace(cv::Mat img, bool isRegister, struct FaceStructParam::FaceParam &faceParam);
	/**
	* @brief MainWindow::transformImgAndPoint
	* ��òü����������resize��������ͼƬresize�ؼ���任
	* 
	*/
/* old	/*   yolo    
	std::vector<std::string> objects_names_from_file(std::string);
	void initDetector();
*/
	inline void setDataSetInfomations() {
		this->dataSetInfomations = sqlSplite->query();
	}
	inline std::vector<InformationParam> getDataSetInfomations() {
		return this->dataSetInfomations;
	}

	void cleanModel();

	void checkFunction(); //����־λfunc��������Ӧ�Ķ���
	inline void setSimTheta(float simTheta) {
		this->simTheta = simTheta;
	}
	inline float getSimTheta() {
		return this->simTheta;
	}

	inline void setVideoStreamRtsp(std::string videoStreamRtsp) {
		this->videoStreamRtsp = videoStreamRtsp;
	}
	inline std::string getVideoStreamRtsp() {
		return this->videoStreamRtsp;
	}

	inline void setUseUSBCamera(int useUSBCamera) {
		this->useUSBCamera = useUSBCamera;
	}
	inline int getUseUSBCamera() {
		return this->useUSBCamera;
	}

	inline void setUSBPort(int  USBPort) {
		this->USBPort = USBPort;
	}
	inline int getUSBPort() {
		return this->USBPort;
	}

	inline void setUseGpuRecognize(int  useGpuRecognize) {
		this->useGpuRecognize = useGpuRecognize;
	}
	inline int getUseGpuRecognize() {
		return this->useGpuRecognize;
	}
	inline void setDetectTheta(float theta) {
		this->detectTheta = theta;
	}
	inline float getDetectTheta() {
		return this->detectTheta;
	}
	// xml 
	bool readXmlData(cv::String xmlFileName);
	// open����ͷ
	inline bool  openVedio()
	{
		// ʹ���Դ�����ͷ
		int cameraMode = getUseUSBCamera();
		if (cameraMode == 0) {
			if (!capture.isOpened()) {
				capture.open(getUSBPort());
			}
		}
		// ʹ��USB����ͷ
		else if (cameraMode == 1) {
			if (!capture.isOpened()) {
				qDebug() << "open usb camera!";
				capture.open(getUSBPort());
			}
		}
		// ʹ����������ͷ
		else if (cameraMode == 2) {
			if (!capture.isOpened()) {
				capture.open(getVideoStreamRtsp());
			}
		}
		else {
			return false;
		}
		if (capture.isOpened()) {
			return true;
		}
		else {
			return false;
		}
	}
	// �ر�����ͷ
	inline void releaseVedio()
	{
		capture.release();
	}
	inline std::vector<std::string> getStuNos() {
		return this->stuNos;
	}
	inline int findNoIndex(std::string number) {
		int index = -1;
		for (int i = 0; i < this->stuNos.size(); i++) {
			if (stuNos[i] == "0") {
				stuNos[i] = number;
				index = i;
				break;
			}
			if (this->stuNos[i] == number) {
				index = i;
				break;
			}
		}
		return index;
	}
	
	inline void setActivityId(int activityId) {
		this->activityId = activityId;
	}
	inline int getActivityId() {
		return this->activityId;
	}
	inline void setRecordId(int recordId) {
		this->recordId = recordId;
	}
	inline int getRecordId() {
		return this->recordId;
	}
	inline void setPushRecordId(int pushRecordId) {
		this->pushRecordId = pushRecordId;
	}
	inline int getPushRecordId() {
		return this->pushRecordId;
	}
	/*д��excel����*/
	void writeExcel();
private slots:

	/*   �� - ģʽѡ��   */
	void openPictureSlot();   //ͼƬ��ť����Ӧ��
	void openVideoSlot();     //������ť����Ӧ��
	void openCameraSlot();    //����ͷ��ť����Ӧ��
	void openRegisterSlot();  //ע�ᰴť����Ӧ��
	void quitSlot();

	/*   �� - ����ѡ��   */
	void detFunctionSlot();    //��⹦��
	void detAliRecFunctionSlot();  //��� + ���� + ʶ����

	void paintEvent(QPaintEvent *e);
	void addActSlot();      // ��ӻ�¼�
	void startRecordSlot(); 
	void selectBoxIndex(int index);
	void selectRecordIndex(int index);
	void pushRecordSlot();
private:
	

	QWidget *centralWidget;
	QWidget *subShowWidget;
	QWidget *rightDownWidget;

	/*  �˵�                    */
	QMenuBar *bar;
	/*  �˵��ؼ� - ģʽѡ��mode  */
	QMenu *openFileMenu;
	QAction *openPictureAction;
	QAction *openVideoAction;
	QAction *openCameraAction;
	QAction *registerAction;
	QAction *quitAction;

	/*  �˵��ؼ� - ����ѡ��func  */
	QMenu *functionMenu;
	QAction *detAction;
	QAction *detAliRecAction;

	/*   �߽���      */

	//QFrame * line = new QFrame();
	//line->setStyleSheet("border:10px groove #242424");
	//line->setFrameShape(QFrame::HLine);
	//line->setFrameShadow(QFrame::Sunken);
	QLabel *leftSplitLine;
	//QFrame *leftLine;
	//QFrame *rightLine;
	QLabel *rightSplitLine;
	QFrame *centralLine;

	/*   ����            */
	QGridLayout *mainGridLayout;
	QGridLayout *rightTopLayout;
	QGridLayout *rightDownLayout;

	/*   �����еĿؼ�    */
	QLabel *mainShow;

	QLabel *upLable;
	QLabel *subShow11;
	QLabel *subShow12;
	QLabel *simiInfo1;

	QLabel *subShow21;
	QLabel *subShow22;
	QLabel *simiInfo2;

	QLabel *subShow31;
	QLabel *subShow32;
	QLabel *simiInfo3;

	QLabel *subShow41;
	QLabel *subShow42;
	QLabel *simiInfo4;

	QLabel *informationShow;
	// ��ӻ
	QPushButton *addActButton;      // ��ӻ����
	QPushButton *startRecordButton; // ��ʼ���ڰ�ť
	QComboBox *selectBox;           // �ѡ��
	QLabel *selectLabel;            //
	QLabel *selectRecordLabel;
	QComboBox *selectRecord;
	QPushButton *pushButton;
	/*   ��־λ    */
	//mode = 1   ->   picture;
	//mode = 2   ->   video;
	//mode = 3   ->   camera;
	int mode = 0;

	/*  ���������   */
	 FaceDetector *faceDetector = NULL;
	 /* ��������*/
	 FaceAlignment *faceAlignment = NULL;
	/*  ����ʶ����   */
	 FaceRecognition *faceRecognition = NULL;

	//cv::Mat picture;  //ԭʼͼƬ
	struct FaceStructParam faceStructParams;//�������ݽṹ
	struct InformationParam reInfParam; // ������Ϣ

    // �����������ļ���ַ
	std::string names_file = "../data/face.names";
	std::string cfg_file = "../cfg/yolov3-spp-focal_loss-test.cfg";
	std::string weights_file = "../model/yolov3-spp-focal_loss_12000.weights";
	

	/* ����ͷ   */
	cv::VideoCapture capture;
	/*    ���� - ��־λ    */
	//func = 1   ->   ���
	//func = 2   ->   ��� + ���� + ʶ��
	//Ĭ��ģʽ - �����
	int func = 1;

	int faceSumNumber = 0; // ��¼������Ŀ������1000 ��Ϊ0
	
	/*xml �ļ�����*/
	// ����ͷ
	float simTheta = 0.5;        // ������ֵ
	std::string videoStreamRtsp; // ��������ͷ
	int useUSBCamera = 1;        // 0��ʾ��ʹ������ͷ��1��ʾʹ��USB����ͷ��2��ʾʹ����������ͷ
	int USBPort = 0;             // ����ͷ�ӿ� 0��1��2��3
	int useGpuRecognize = 1;     // ʶ���Ƿ�ʹ��GPU
	float detectTheta = 0.7;     // ���������� 
	std::vector<std::string>stuNos = {"0","0","0","0"};
	int currentShowFace = -1;
	int imageSize = 112;
	int alignType = 0; // 0����seeta2,1����dlib
					   //���ݿ������
	 SqlSplite *sqlSplite = NULL;

	// ���ݿ���������Ϣ
	std::vector<InformationParam> dataSetInfomations;
	/*<���ڱ���>*/
	// ѡ������
	int activityId;
	//�Ƿ�������
	bool isStartRecord = false;
	// �Ѽ�¼������
	std::vector<QString> recordNames;
	// ����ID
	int recordId = -1;
	// ����ID
	int pushRecordId = -1;
};

#endif // MAINWINDOW_H
