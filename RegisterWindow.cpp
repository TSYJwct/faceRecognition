#include "common.h"
#include "RegisterWindow.h"
#include <QHBoxLayout>
#include <qmessagebox.h>
#include <io.h>
#include <direct.h>

//QWidget *parent, 
RegisterWindow::RegisterWindow(FaceDetector *faceDetector,FaceAlignment *faceAlignment,FaceRecognition *faceRecognition) : QWidget()
{
	//��ʼ�������
	this->faceDetector = faceDetector;  //��MainWindw�д��ݹ����ļ�����������Է�ֹ�ظ���ʼ�����������Լʱ����ڴ棩
	this->faceAlignment = faceAlignment;
	this->faceRecognition = faceRecognition;
	//��ʼ������ͷ
	initCapture();
	sqlSplite = new SqlSplite();

	//��ʼ������
	initView();
}
RegisterWindow::~RegisterWindow()
{
}
/**
��ʼ������
*/
void RegisterWindow::initView()
{
	this->setWindowTitle(SQ("ע��"));
	this->setFixedSize(1000, 700);

	//���
	mainShow = new QLabel();
	mainShow->setFixedSize(650, 650);
	mainShow->setStyleSheet("border:1px groove #242424");
	QHBoxLayout *left = new QHBoxLayout();
	left->addWidget(mainShow);
	left->setMargin(10);

	//�ұ�
	//��
	subShow = new QLabel();
	subShow->setFixedSize(300, 300);
	subShow->setStyleSheet("border:1px groove #242424");
	QHBoxLayout *rightTop = new QHBoxLayout();
	rightTop->addWidget(subShow);
	//rightTop->setAlignment(Qt::AlignLeft);
	//��
	nameLabel = new QLabel(SQ("����:"));
	noLabel = new QLabel(SQ("ѧ��:"));
	collegeLabel = new QLabel(SQ("ѧԺ:"));
	classLabel = new QLabel(SQ("�༶:"));
	QVBoxLayout *rightMidL = new QVBoxLayout();
	rightMidL->setAlignment(Qt::AlignLeft);
	rightMidL->addWidget(nameLabel);
	rightMidL->addWidget(noLabel);
	rightMidL->addWidget(collegeLabel);
	rightMidL->addWidget(classLabel);

	nameEdit = new QLineEdit();
	nameEdit->setFixedSize(200, 30);
	noEdit = new QLineEdit();
	noEdit->setFixedSize(200, 30);
	collegeEdit = new QLineEdit();
	collegeEdit->setFixedSize(200, 30);
	classEdit = new QLineEdit();
	classEdit->setFixedSize(200, 30);
	QVBoxLayout *rightMidR = new QVBoxLayout();
	rightMidR->setAlignment(Qt::AlignLeft);
	rightMidR->addWidget(nameEdit);
	rightMidR->addWidget(noEdit);
	rightMidR->addWidget(collegeEdit);
	rightMidR->addWidget(classEdit);

	QHBoxLayout *rightMid = new QHBoxLayout();
	rightMid->addLayout(rightMidL);
	rightMid->addLayout(rightMidR);

	//��
	shotButton = new QPushButton();
	shotButton->setText(SQ("����"));
	shotButton->setFixedSize(70, 30);
	connect(shotButton, SIGNAL(clicked()), this, SLOT(shotButtonSlot()));

	confirmButton = new QPushButton();
	confirmButton->setText(SQ("ȷ��"));
	confirmButton->setFixedSize(70, 30);
	connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmButtonSlot()));

	quitButton = new QPushButton();
	quitButton->setText(SQ("�˳�"));
	quitButton->setFixedSize(70, 30);
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButtonSlot()));

	QHBoxLayout *rightButtom = new QHBoxLayout();
	rightButtom->addWidget(shotButton);
	rightButtom->addWidget(confirmButton);
	rightButtom->addWidget(quitButton);
	rightButtom->setAlignment(Qt::AlignHCenter);
	rightButtom->setSpacing(10);

	QVBoxLayout *right = new QVBoxLayout();
	right->addLayout(rightTop);
	right->addLayout(rightMid);
	right->addLayout(rightButtom);

	//����
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addLayout(left);
	mainLayout->addLayout(right);
}
/**
��ʼ������ͷ
*/
void RegisterWindow::initCapture()
{
	if (!capture.isOpened()) {
		capture.open(0);
	}
	
}

/**
�ͷŽ���
*/
void RegisterWindow::cleanView()
{
	if (mainShow)
	{
		delete mainShow;
		mainShow = NULL;
	}
	if (subShow)
	{
		delete subShow;
		subShow = NULL;
	}
	if (nameLabel)
	{
		delete nameLabel;
		nameLabel = NULL;
	}
	if (nameEdit)
	{
		delete nameEdit;
		nameEdit = NULL;
	}
	if (noLabel)
	{
		delete noLabel;
		noLabel = NULL;
	}
	if (noEdit)
	{
		delete noEdit;
		noEdit = NULL;
	}
	if (collegeEdit)
	{
		delete collegeEdit;
		collegeEdit = NULL;
	}
	if (classLabel)
	{
		delete classLabel;
		classLabel = NULL;
	}
	if (classEdit)
	{
		delete classEdit;
		classEdit = NULL;
	}
	if (shotButton)
	{
		delete shotButton;
		shotButton = NULL;
	}
	if (confirmButton)
	{
		delete confirmButton;
		confirmButton = NULL;
	}
	if (quitButton)
	{
		delete quitButton;
		quitButton = NULL;
	}
}

/*

*/
bool RegisterWindow::checkInformation()
{
	if (rFaceStructParam.faceParams.empty())  //û������ͼƬ��˵��û�м�⵽����
	{
		return false;
	}
	else if (nameEdit->text().isEmpty() || noEdit->text().isEmpty() || collegeEdit->text().isEmpty() || classEdit->text().isEmpty())
	{
		return false;
	}
	return true;
}

/**
���㰴ť - ����
�� mainShow �е�����ͼƬ�ŵ� subShow ��,��ȡ����
*/
void RegisterWindow::shotButtonSlot()
{
	//ʶ����Ҫ��Ϊ�˻�ȡfeatureMap
	if (capture.isOpened()) {
		capture.release();
	}
	else {
		capture.open(0);
	}
	if (rFaceStructParam.faceParams.size() == 0) {
		QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ���������� </font>"));
		message.exec();
		return;
	}
	//this->faceRecognition->recognize(rImageAndParam, 0, true);
	/*struct FaceStructParam faceStructParam;
	rFaceStructParam = faceStructParam;
	struct FaceStructParam::FaceParam faceParam;*/
	std::vector<cv::Point2f> landmarkPoints;
	cv::Mat detectImg;
	// �ؼ�����
	faceAlignment->landmarkFace(rFaceStructParam.image,rFaceStructParam.faceParams[0].detectBox, landmarkPoints);
	faceAlignment->transformImgAndPoint(rFaceStructParam.image, rFaceStructParam.faceParams[0].detectBox, 112, detectImg, landmarkPoints);
	
	// ����
	cv::Mat alignFace;
	faceAlignment->alignFace(detectImg, landmarkPoints, alignFace);
	rFaceStructParam.faceParams[0].featureMap =faceRecognition->makeFeature(alignFace);
	// ��ֵ
	rFaceStructParam.faceParams[0].landmarks = landmarkPoints;
	// rFaceStructParam.faceParams[0].push_back(faceParam);
	// faceParam.landmarks = landmarkPoints;
	// ����
	// cv::Mat alignFace;
	//faceAlignment->alignFace(detectImg, landmarkPoints, alignFace);
	/*  �ȼ����д��Ϣ��������   */
	if (checkInformation() == false)
	{
		//qDebug() << "22OK!";
		QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ������������Ϣ </font>"));
		message.exec();
		return;
	}
	/*    ��Ϣ��������   */
	setImage2Label(detectImg, subShow);

	//qDebug() << "OK!";
	QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'blue'> ��Ϣ��ȷ </font>"));
	message.exec();
}

void RegisterWindow::paintEvent(QPaintEvent *e)
{
	
	if (capture.isOpened())
	{
		FaceStructParam faceStructParam;
		rFaceStructParam = faceStructParam;
		capture >> img;
		rFaceStructParam.image = img.clone();
		cv::Mat drawMat = img.clone();
		std::vector<cv::Point2f> points;
		double simScore;
		std::string name;
		std::vector<bbox_t> boxes = faceDetector->faceDetectBoxes(img);
		for (int i = 0; i < boxes.size(); i++) {
			struct FaceStructParam::FaceParam faceParam;
			faceParam.detectBox = boxes[i];
			rFaceStructParam.faceParams.push_back(faceParam);
			drawAllMessages(drawMat, boxes[i], points, simScore, name, false);
		}
		
		//draw_boxes(picture, result_vec, obj_names, spent.count());//����
		setImage2Label(drawMat, mainShow);
	}
}
/**
ȷ����ť - ȷ��
���û���������Ϣ������������Ϣ��������ݿ���
*/
void RegisterWindow::confirmButtonSlot()
{
	if (rFaceStructParam.faceParams.size() == 0 || checkInformation() == false ) {
		QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> �������պ���д��Ϣ </font>"));
		message.exec();
		return;
	}
	string savePath = "../faces/";
	if (_access(savePath.c_str(), 0) == -1) //������
		mkdir(savePath.c_str());
	//�ѽ�ȡ������ͼƬ���뵽������
	std::string pictureRoute = savePath + QS(noEdit->text()) + ".png";
	cv::Mat rectImage;
	// �ü�����
	bbox_t bbox = rFaceStructParam.faceParams[0].detectBox;
	cv::Rect rect(bbox.x, bbox.y, bbox.w, bbox.h);
	rFaceStructParam.image(rect).copyTo(rectImage);
	cv::imwrite(pictureRoute,rectImage);
	//TODO:  ������Ϣ�����ݿ���

	infParam.setName(QS(QString(nameEdit->text())));
	infParam.setNo(QS(QString(noEdit->text())));
	infParam.setCollege(QS(QString(collegeEdit->text())));
	infParam.setClass(QS(QString(classEdit->text())));
	infParam.setPictureRoute(pictureRoute);

	//���뵽���ݿ���
	//�������
	//1��featureMap
	//2��ע����Ϣ
	sqlSplite->insert(rFaceStructParam.faceParams[0].featureMap, infParam);//featureMap �� ��������Ϣ

															 ///////
															 //��ʾ������ɹ����Ի���
															 //if(success)
	QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ��Ϣ����ɹ� </font>"));
	message.setIconPixmap(QPixmap(SQ(pictureRoute)));  //TODO::������ͼƬ�������
	message.exec();
}
/**
�˳���ť - �˳�
�˳��˶Ի���
*/
void RegisterWindow::quitButtonSlot()
{
	cleanView();

	if (capture.isOpened())//һ��ʼ������ʱ������ͷ�ǹ��ŵģ����Գ�ȥҲҪ�ͷŵ�
		this->capture.release();
	this->close();
	//this->close();
}

void RegisterWindow::quitSlot() {
	if (capture.isOpened()) {
		capture.release();
	}
	this->close();
}