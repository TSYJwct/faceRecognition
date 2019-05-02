#include "common.h"
#include "RegisterWindow.h"
#include <QHBoxLayout>
#include <qmessagebox.h>
#include <QFileDialog>
#include <io.h>
#include <direct.h>

//QWidget *parent, 
RegisterWindow::RegisterWindow(FaceDetector *faceDetector,FaceAlignment *faceAlignment,FaceRecognition *faceRecognition) 
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
	cleanView();
	releaseModel();
}
void RegisterWindow::releaseModel() {
	if (faceDetector) {
		delete faceDetector;
		faceDetector = NULL;
	}
	if (faceAlignment) {
		delete faceAlignment;
		faceAlignment = NULL;
	}
	if (faceRecognition) {
		delete faceRecognition;
		faceRecognition = NULL;
	}
}
/**
��ʼ������
*/
void RegisterWindow::initView()
{
	centralWidget = new QWidget(); //��������
	/*�ұ߲��ֳ�ʼ��*/
	rightTopLayout = new QGridLayout();
	rightTopLayout->setSpacing(5);
	rightTopLayout->setHorizontalSpacing(5);
	//rightTopLayout->setAlignment(Qt::AlignCenter);
	rightTopLayout->setMargin(5);
	mainGridLayout = new QGridLayout(centralWidget);
	mainGridLayout->setSpacing(5);

	this->setWindowTitle(SQ("ע��"));
	this->setFixedSize(1000, 700);

	//���
	mainShow = new QLabel();
	mainShow->setFixedSize(640, 480);
	mainShow->setStyleSheet("border:1px groove #242424");

	//�ұ�
	//��
	subShow = new QLabel();
	subShow->setFixedSize(300, 300);
	subShow->setStyleSheet("border:1px groove #242424");
	//��
	nameLabel = new QLabel(SQ("����:"));
	nameLabel->setAlignment(Qt::AlignRight);
	noLabel = new QLabel(SQ("ѧ��:"));
	noLabel->setAlignment(Qt::AlignRight);
	collegeLabel = new QLabel(SQ("ѧԺ:"));
	collegeLabel->setAlignment(Qt::AlignRight);
	classLabel = new QLabel(SQ("�༶:"));
    classLabel->setAlignment(Qt::AlignRight);

	nameEdit = new QLineEdit();
	nameEdit->setFixedSize(180, 30);
	noEdit = new QLineEdit();
	noEdit->setFixedSize(180, 30);
	collegeEdit = new QComboBox();
	collegeEdit->setFixedSize(180, 30);
	for (auto name : collegeNames) {
		collegeEdit->addItem(name);
	}
	classEdit = new QLineEdit();
	classEdit->setFixedSize(180, 30);
	//��
	shotButton = new QPushButton();
	shotButton->setText(SQ("������ͷ"));
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

	upFaceButton = new QPushButton();
	upFaceButton->setText(SQ("�ϴ�����ͼƬ"));
	upFaceButton->setFixedSize(100, 30);
	connect(upFaceButton, SIGNAL(clicked()), this, SLOT(upFaceButtonSlot()));

	upBatchFaceButton = new QPushButton();
	upBatchFaceButton->setText(SQ("�����ϴ���Ƭ"));
	upBatchFaceButton->setFixedSize(100, 30);
	connect(upBatchFaceButton, SIGNAL(clicked()), this, SLOT(upBatchFaceButtonSlot()));

	rightTopLayout->addWidget(subShow, 0, 0, 1, 3);
	rightTopLayout->addWidget(nameLabel, 1, 0, 1, 1);
	rightTopLayout->addWidget(nameEdit, 1, 1, 1, 2);
	rightTopLayout->addWidget(noLabel, 2, 0, 1, 1);
	rightTopLayout->addWidget(noEdit, 2, 1, 1, 2);
	rightTopLayout->addWidget(collegeLabel, 3, 0, 1, 1);
	rightTopLayout->addWidget(collegeEdit, 3, 1, 1, 2);
	rightTopLayout->addWidget(classLabel, 4, 0, 1, 1);
	rightTopLayout->addWidget(classEdit, 4, 1, 1, 2);
	rightTopLayout->addWidget(shotButton, 5, 0, 1, 1);
	rightTopLayout->addWidget(upFaceButton, 5, 1, 1, 1);
	rightTopLayout->addWidget(upBatchFaceButton, 5, 2, 1, 1);
	rightTopLayout->addWidget(confirmButton, 6, 0,1, 1);
	rightTopLayout->addWidget(quitButton, 6, 1, 1, 1);

	subShowWidget = new QWidget(centralWidget);
	subShowWidget->setLayout(rightTopLayout);

	mainGridLayout->addWidget(mainShow, 0, 0, 1, 1);
	mainGridLayout->addWidget(subShowWidget, 0, 1, 1, 1);
	// this->showMaximized();//����ȫ����ʾ
	this->setCentralWidget(centralWidget);
	this->setFixedSize(1000, 600);
}
/**
��ʼ������ͷ
*/
void RegisterWindow::initCapture()
{
	if (capture.isOpened()) {
		capture.release();
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
	if (upFaceButton) {
		delete upFaceButton;
		upFaceButton = NULL;
	}
	if (upBatchFaceButton) {
		delete upBatchFaceButton;
		upBatchFaceButton = NULL;
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
	else if (nameEdit->text().isEmpty() || noEdit->text().isEmpty() || collegeEdit->currentText().isEmpty() || classEdit->text().isEmpty())
	{
		return false;
	}
	return true;
}

void RegisterWindow::upFaceButtonSlot() {
	registerType = 1;
	QString fileName = QFileDialog::getOpenFileName(this, SQ("ѡ��ͼƬ"), "", tr("Images (*.png *.bmp *.jpg)"));
	if (fileName.isEmpty()) {
		QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ͼƬѡ�����������ѡ�� </font>"));
		message.exec();
		return;
	}
	// ��ϴ
	FaceStructParam faceStructParam;
	rFaceStructParam = faceStructParam;

	cv::Mat image = cv::imread(QS(fileName));
	rFaceStructParam.image = image.clone();

	cv::Mat drawMat = image.clone();
	std::vector<cv::Point2f> points;
	double simScore;
	std::string name;
	std::vector<bbox_t> boxes = faceDetector->faceDetectBoxes(image);
	for (int i = 0; i < boxes.size(); i++) {
		struct FaceStructParam::FaceParam faceParam;
		faceParam.detectBox = boxes[i];
		rFaceStructParam.faceParams.push_back(faceParam);
		drawAllMessages(drawMat, boxes[i], points, simScore, name, false);
	}
	if (boxes.size() == 0) {
		QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> δ��⵽�������������ϴ�ͼƬ </font>"));
		message.exec();
		return;
	}
	//draw_boxes(picture, result_vec, obj_names, spent.count());//����
	setImage2Label(drawMat, mainShow);
	cv::Mat detectImg;
	this->predictFace(detectImg);
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
void RegisterWindow::upBatchFaceButtonSlot() {
	registerType = 2;
	QString file = QFileDialog::getExistingDirectory(this, SQ("ѡ���ļ���"), ""); //getOpenFileName(this, SQ("ѡ��ͼƬ"), "", tr("Images (*.png *.bmp *.jpg)"));
	QDir dirPath(file);
	QStringList nameFilters;
	nameFilters << "*.jpg" << "*.png"<<"*.bmp";
	QStringList files = dirPath.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	if (files.isEmpty()) {
		QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ������ѡ���ļ��У�ֻ֧��jpg��png��bmp��ʽͼƬ </font>"));
		message.exec();
		return;
	}
	for (auto path : files) {
		QString fileName = file +"/"+ path;
		FaceStructParam faceStructParam;
		rFaceStructParam = faceStructParam;

		cv::Mat image = cv::imread(QS(fileName));
		rFaceStructParam.image = image.clone();
		std::vector<cv::Point2f> points;
		std::vector<bbox_t> boxes = faceDetector->faceDetectBoxes(image);
		for (int i = 0; i < boxes.size(); i++) {
			struct FaceStructParam::FaceParam faceParam;
			faceParam.detectBox = boxes[i];
			rFaceStructParam.faceParams.push_back(faceParam);
		}
		if (boxes.size() > 0) {
			cv::Mat detectImg;
			this->predictFace(detectImg);
			this->saveMessage(fileName);
			qDebug() << fileName;
		}
	}
}
/**
���㰴ť - ����
�� mainShow �е�����ͼƬ�ŵ� subShow ��,��ȡ����
*/
void RegisterWindow::shotButtonSlot()
{
	//ʶ����Ҫ��Ϊ�˻�ȡfeatureMap
	registerType = 0;
	if (this->shotButton->text()== SQ("������ͷ")){
		shotButton->setText(SQ("����"));
		capture.open(0);
	}
	else if (this->shotButton->text() == SQ("����")) {
		capture.release();
		shotButton->setText(SQ("������ͷ"));
		// mainShow->clear();
		if (rFaceStructParam.faceParams.size() == 0) {
			QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ���������� </font>"));
			message.exec();
			return;
		}
		cv::Mat detectImg;
		this->predictFace(detectImg);

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
}

void RegisterWindow::paintEvent(QPaintEvent *e)
{
	if (registerType == 0) {
		if (capture.isOpened()) {
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
	else {
		if (capture.isOpened()) {
			capture.release();
		}
		
	}
}

void RegisterWindow::saveMessage(const QString imagePath) {
	QFileInfo fileInfo = QFileInfo(imagePath);
	string savePath = "../faces/";
	if (_access(savePath.c_str(), 0) == -1) //������
		mkdir(savePath.c_str());
	//�ѽ�ȡ������ͼƬ���뵽������
	std::string pictureRoute;
	if (registerType == 2) {
		pictureRoute = savePath + QS(fileInfo.fileName());
	}
	else {
		pictureRoute = savePath + QS(noEdit->text()) + ".png";
	}
	cv::Mat rectImage;
	// �ü�����
	bbox_t bbox = rFaceStructParam.faceParams[0].detectBox;
	cv::Rect rect(bbox.x, bbox.y, bbox.w, bbox.h);
	rFaceStructParam.image(rect).copyTo(rectImage);
	cv::imwrite(pictureRoute, rectImage);
	//TODO:  ������Ϣ�����ݿ���
	if (registerType == 2) { // �����ϴ�
		QString file_name = fileInfo.fileName();
		QString messagesList = file_name.split(".")[0]; // ��Ϣ
		QStringList datas = messagesList.split("_");
		infParam.setName(QS(datas[0]));
		infParam.setNo(QS(datas[1]));
		infParam.setCollege(QS(datas[2]));
		infParam.setClass(QS(datas[3]));
		infParam.setPictureRoute(pictureRoute);
	}
	else {
		infParam.setName(QS(QString(nameEdit->text())));
		infParam.setNo(QS(QString(noEdit->text())));
		infParam.setCollege(QS(QString(collegeEdit->currentText())));
		infParam.setClass(QS(QString(classEdit->text())));
		infParam.setPictureRoute(pictureRoute);
	}

	//���뵽���ݿ���
	//�������
	//1��featureMap
	//2��ע����Ϣ
	sqlSplite->insert(rFaceStructParam.faceParams[0].featureMap, infParam);//featureMap �� ��������Ϣ

																		   ///////
																		   //��ʾ������ɹ����Ի���
																		   //if(success)
	
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
	saveMessage();
	QMessageBox message(QMessageBox::NoIcon, SQ("ȷ��"), SQ("<font color = 'red'> ��Ϣ����ɹ� </font>"));
	//message.setIconPixmap(QPixmap(SQ(pictureRoute)));  //TODO::������ͼƬ�������
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
void RegisterWindow::predictFace(cv::Mat &detectImg) {
	std::vector<cv::Point2f> landmarkPoints;
	
	// �ؼ�����
	faceAlignment->landmarkFace(rFaceStructParam.image, rFaceStructParam.faceParams[0].detectBox, landmarkPoints);
	faceAlignment->transformImgAndPoint(rFaceStructParam.image, rFaceStructParam.faceParams[0].detectBox, 112, detectImg, landmarkPoints);

	// ����
	cv::Mat alignFace;
	faceAlignment->alignFace(detectImg, landmarkPoints, alignFace);
	rFaceStructParam.faceParams[0].featureMap = faceRecognition->makeFeature(alignFace);
	// ��ֵ
	rFaceStructParam.faceParams[0].landmarks = landmarkPoints;
}