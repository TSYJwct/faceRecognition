#include "MainWindow.h"
#include "RegisterWindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMenu>
#include <qmenubar.h>
#include <qDebug.h>
#include <QMessageBox>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	sqlSplite = new SqlSplite();
	
	/*   ��ʼ������  */

	initView();

	/*��ȡxml*/
	readXmlData("./params.xml");

	/*  ��ʼ�����������  */
	faceDetector = new FaceDetector(names_file, cfg_file,weights_file);
	/* ��ʼ���������� */
	faceAlignment = new FaceAlignment(alignType);
	/* ��ʼ������ʶ�� */
	faceRecognition = new FaceRecognition(useGpuRecognize == 1 ? true: false);
	

}

MainWindow::~MainWindow()
{
	cleanMenu();  //�ͷŲ˵�
	cleanLayout();  //�ͷŲ���
	cleanModel();   //�ͷż���� & ʶ����
}

/**
* @brief MainWindow::initView - ��ʼ�����棺������ʼ���˵��Ͳ���
*/
void MainWindow::initView()
{
	/*  �˵�  */
	initMenu();
	/*  ����  */
	initLayout();
}
/**
* @brief MainWindow::initMenu - ��ʼ���˵���
*/
void MainWindow::initMenu()
{
	/* �˵� - ģʽѡ��mode*/
	openFileMenu = new QMenu(SQ("ģʽ"));

	openPictureAction = new QAction(SQ("ͼƬ"), this);
	openPictureAction->setShortcut(tr("Ctrl+p"));
	connect(openPictureAction, SIGNAL(triggered()), this, SLOT(openPictureSlot()));
	openFileMenu->addAction(openPictureAction);

	openVideoAction = new QAction(SQ("��Ƶ"), this);
	openVideoAction->setShortcut(tr("Ctrl+V"));
	connect(openVideoAction, SIGNAL(triggered()), this, SLOT(openVideoSlot()));
	openFileMenu->addAction(openVideoAction);

	openCameraAction = new QAction(SQ("����ͷ"), this);
	openCameraAction->setShortcut(tr("Ctrl+C"));
	connect(openCameraAction, SIGNAL(triggered()), this, SLOT(openCameraSlot()));
	openFileMenu->addAction(openCameraAction);

	registerAction = new QAction(SQ("�û�ע��"), this);
	connect(registerAction, SIGNAL(triggered()), this, SLOT(openRegisterSlot()));

	quitAction = new QAction(SQ("�˳�"), this);
	quitAction->setShortcut(tr("Ctrl+q"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(quitSlot()));
	openFileMenu->addSeparator();
	openFileMenu->addAction(quitAction);

	/*  �˵� - ����ѡ��func   */
	functionMenu = new QMenu(SQ("����"));
	
	detAction = new QAction(SQ("���"), this);
	//openPictureAction->setShortcut(tr("Ctrl+p"));
	connect(detAction, SIGNAL(triggered()), this, SLOT(detFunctionSlot()));
	functionMenu->addAction(detAction);

	detAliRecAction = new QAction(SQ("���+ʶ��"));
	connect(detAliRecAction, SIGNAL(triggered()), this, SLOT(detAliRecFunctionSlot()));
	functionMenu->addAction(detAliRecAction);

	/* �Ѳ˵���ӵ��˵�����  */
	bar = this->menuBar();
	bar->addMenu(openFileMenu);
	bar->addMenu(functionMenu);
	bar->addAction(registerAction);

	/* ���� */
	this->setWindowTitle(SQ("���������ʶ��ϵͳ"));
}

/**
* @brief MainWindow::cleanMenu - ���ղ˵���
*/
void MainWindow::cleanMenu()
{
	if (openFileMenu)
	{
		delete openFileMenu;
		openFileMenu = NULL;
	}
	if (openPictureAction)
	{
		delete openPictureAction;
		openPictureAction = NULL;
	}
	if (openVideoAction)
	{
		delete openVideoAction;
		openVideoAction = NULL;
	}
	if (openCameraAction)
	{
		delete openCameraAction;
		openCameraAction = NULL;
	}
	if (detAction)
	{
		delete detAction;
		detAction = NULL;
	}
	if (detAliRecAction)
	{
		delete detAliRecAction;
		detAliRecAction = NULL;
	}
	if (functionMenu)
	{
		delete functionMenu;
		functionMenu = NULL;
	}
}
/**
* @brief MainWindow::initLayout - ��ʼ���ؼ�����
*/
void MainWindow::initLayout()
{
	centralWidget = new QWidget(); //��������
	//��ʼ�� - ��ʾͼƬ��QLabel
	mainShow = new QLabel();
	mainShow->setAlignment(Qt::AlignCenter);  //����
	mainShow->setScaledContents(true);  //ͼƬ����Ӧ
	QSize mainShowSize(1320, 960);
	mainShow->setFixedSize(mainShowSize);
	mainShow->setStyleSheet("border: 1px groove #242424");

	QSize upLabelSize(1920, 60);
	upLable = new QLabel();
	upLable->setFixedSize(upLabelSize);

	//��ʼ�� - ����
	/*leftLine = new QFrame();
	leftLine->setStyleSheet("border:2px groove #242424");
	leftLine->setFrameShape(QFrame::HLine);
	leftLine->setFrameShadow(QFrame::Raised);*/

	leftSplitLine = new QLabel();
	leftSplitLine->setFixedWidth(5);
	leftSplitLine->setStyleSheet("background-color:black");
	
	/*rightLine = new QFrame();
	rightLine->setFrameShape(QFrame::HLine);
	rightLine->setFrameShadow(QFrame::Sunken);*/
	rightSplitLine = new QLabel();
	rightSplitLine->setFixedWidth(5);
	rightSplitLine->setStyleSheet("background-color:black");

	centralLine = new QFrame();
	centralLine->setStyleSheet("border: 5px groove #242424");
	centralLine->setFrameShape(QFrame::HLine);
	centralLine->setFrameShadow(QFrame::Sunken);


	//��ʼ�� - ���Ͻ�
	QSize subLabelSize(150, 150);
	QSize simiInfoSize(100, 100);
	rightTopLayout = new QGridLayout();
	rightTopLayout->setSpacing(20);
	rightTopLayout->setHorizontalSpacing(60);
	//rightTopLayout->setAlignment(Qt::AlignCenter);
	rightTopLayout->setMargin(5);

	
	// ��������
	QFont ft;
	ft.setPointSize(20);
	subShow11 = new QLabel();
	subShow11->setStyleSheet("border:1px groove #242424");
	subShow11->setFixedSize(subLabelSize);
	subShow11->setScaledContents(true);
	subShow12 = new QLabel();
	subShow12->setStyleSheet("border:1px groove #242424");
	subShow12->setFixedSize(subLabelSize);
	subShow12->setScaledContents(true);
	simiInfo1 = new QLabel();
	simiInfo1->setFixedSize(simiInfoSize);
	simiInfo1->setStyleSheet("border-radius: 50px; border: 1px solid black;");
	simiInfo1->setFont(ft);
	simiInfo1->setAlignment(Qt::AlignCenter);

	subShow21 = new QLabel();
	subShow21->setStyleSheet("border:1px groove #242424");
	subShow21->setFixedSize(subLabelSize);
	subShow21->setScaledContents(true);

	subShow22 = new QLabel();
	subShow22->setStyleSheet("border:1px groove #242424");
	subShow22->setFixedSize(subLabelSize);
	subShow22->setScaledContents(true);

	simiInfo2 = new QLabel();
	simiInfo2->setFixedSize(simiInfoSize);
	simiInfo2->setStyleSheet("border-radius: 50px; border: 1px solid black;");
	simiInfo2->setFont(ft);
	simiInfo2->setAlignment(Qt::AlignCenter);

	subShow31 = new QLabel();
	subShow31->setStyleSheet("border:1px groove #242424");
	subShow31->setFixedSize(subLabelSize);
	subShow31->setScaledContents(true);

	subShow32 = new QLabel();
	subShow32->setStyleSheet("border:1px groove #242424");
	subShow32->setFixedSize(subLabelSize);
	subShow32->setScaledContents(true);

	simiInfo3 = new QLabel();
	simiInfo3->setFixedSize(simiInfoSize);
	simiInfo3->setStyleSheet("border-radius: 50px; border: 1px solid black;");
	simiInfo3->setFont(ft);
	simiInfo3->setAlignment(Qt::AlignCenter);

	subShow41 = new QLabel();
	subShow41->setStyleSheet("border:1px groove #242424");
	subShow41->setFixedSize(subLabelSize);
	subShow41->setScaledContents(true);

	subShow42 = new QLabel();
	subShow42->setStyleSheet("border:1px groove #242424");
	subShow42->setFixedSize(subLabelSize);
	subShow42->setScaledContents(true);

	simiInfo4 = new QLabel();
	simiInfo4->setFixedSize(simiInfoSize);
	simiInfo4->setStyleSheet("border-radius: 50px; border: 1px solid black;");
	simiInfo4->setFont(ft);
	simiInfo4->setAlignment(Qt::AlignCenter);

	rightTopLayout->addWidget(subShow11, 0, 0);
	rightTopLayout->addWidget(simiInfo1, 0, 1);
	rightTopLayout->addWidget(subShow12, 0, 2);

	rightTopLayout->addWidget(subShow21, 1, 0);
	rightTopLayout->addWidget(simiInfo2, 1, 1);
	rightTopLayout->addWidget(subShow22, 1, 2);

	rightTopLayout->addWidget(subShow31, 2, 0);
	rightTopLayout->addWidget(simiInfo3, 2, 1);
	rightTopLayout->addWidget(subShow32, 2, 2);

	rightTopLayout->addWidget(subShow41, 3, 0);
	rightTopLayout->addWidget(simiInfo4, 3, 1);
	rightTopLayout->addWidget(subShow42, 3, 2);

	subShowWidget = new QWidget(centralWidget);
	subShowWidget->setLayout(rightTopLayout);
	
	//��ʼ�� - ���½�
	rightDownLayout = new QGridLayout();
	rightDownLayout->setSpacing(10);
	rightDownLayout->setHorizontalSpacing(10);
	rightDownLayout->setMargin(5);

	addActButton = new QPushButton();
	addActButton->setFixedSize(60, 30);
	addActButton->setText(SQ("��ӻ"));
	startRecordButton = new QPushButton();
	startRecordButton->setFixedSize(60, 30);
	startRecordButton->setText(SQ("��ʼ����"));
	informationShow = new QLabel();
	informationShow->setStyleSheet("border:1px groove #242424");

	selectBox = new QComboBox();
	selectBox->setFixedSize(100, 30);
	std::vector<QString> comBoxStr = sqlSplite->selectActivity();
	for (auto str :comBoxStr) {
		selectBox->addItem(str);
	}
	// ���û
	// setActivityName(selectBox->currentText());
	//qDebug() <<"sdsdsd"<< getActivityName();
	connect(addActButton, SIGNAL(clicked()), this, SLOT(addActSlot()));
	connect(startRecordButton, SIGNAL(clicked()), this, SLOT(startRecordSlot()));
	connect(selectBox, SIGNAL(activated(int)), this, SLOT(selectBoxIndex(int)));

	rightDownLayout->addWidget(addActButton, 0, 0, 1, 1);
	rightDownLayout->addWidget(startRecordButton, 0, 2, 1, 1);
	rightDownLayout->addWidget(informationShow, 1, 0, 1, 3);
	rightDownLayout->addWidget(selectBox, 0, 1, 1, 1);
	rightDownWidget = new QWidget(centralWidget);
	rightDownWidget->setLayout(rightDownLayout);
	//��ʼ�� - ������
	mainGridLayout = new QGridLayout(centralWidget);
	mainGridLayout->setSpacing(10);

	//��������
	mainGridLayout->addWidget(upLable, 0, 0, 1, 2);
	mainGridLayout->addWidget(mainShow, 1, 0, 3, 1);
	//mainGridLayout->addWidget(leftLine, 0, 1, 3, 1);
	//mainGridLayout->addWidget(leftSplitLine, 0, 1, 3, 1);

	//mainGridLayout->addLayout(rightTopLayout, 0, 2, 1, 1);
	mainGridLayout->addWidget(subShowWidget, 1, 1, 1, 1);
	mainGridLayout->addWidget(centralLine, 2, 1, 1, 1);
	mainGridLayout->addWidget(rightDownWidget, 3, 1, 1, 1);
	//mainGridLayout->addWidget(rightSplitLine, 0, 3, 3, 1);

	// centralWidget->setAutoFillBackground(true);
	QPalette pale;
	pale.setBrush(QPalette::Background, QBrush(QPixmap("./mainw.png")));
	//centralWidget->setPalette(pale);
	this->setCentralWidget(centralWidget);
	// this->showMaximized();//����ȫ����ʾ
	this->setPalette(pale);
	this->setFixedSize(1920, 960);

}

/**
* @brief MainWindow::cleanLayout - �ͷŲ���
*/
void MainWindow::cleanLayout()
{
	if (centralWidget)
	{
		delete centralWidget;
		centralWidget = NULL;
	}
	if (subShowWidget)
	{
		delete subShowWidget;
		subShowWidget = NULL;
	}
	if (leftSplitLine)
	{
		delete leftSplitLine;
		leftSplitLine = NULL;
	}
	if (rightSplitLine)
	{
		delete rightSplitLine;
		rightSplitLine = NULL;
	}
	if (centralLine)
	{
		delete centralLine;
		centralLine = NULL;
	}
	if (mainGridLayout)
	{
		delete mainGridLayout;
		mainGridLayout = NULL;
	}
	if (rightTopLayout)
	{
		delete rightTopLayout;
		rightTopLayout = NULL;
	}
	if (mainShow)
	{
		delete mainShow;
		mainShow = NULL;
	}
	if (subShow11)
	{
		delete subShow11;
		subShow11 = NULL;
	}
	if (subShow12)
	{
		delete subShow12;
		subShow12 = NULL;
	}
	if (subShow21)
	{
		delete subShow21;
		subShow21 = NULL;
	}
	if (subShow22)
	{
		delete subShow22;
		subShow22 = NULL;
	}
	if (subShow31)
	{
		delete subShow31;
		subShow31 = NULL;
	}
	if (subShow32)
	{
		delete subShow32;
		subShow32 = NULL;
	}
	if (subShow41)
	{
		delete subShow41;
		subShow41 = NULL;
	}
	if (subShow42)
	{
		delete subShow42;
		subShow42 = NULL;
	}
	if (simiInfo1)
	{
		delete simiInfo1;
		simiInfo1 = NULL;
	}
	if (simiInfo2)
	{
		delete simiInfo2;
		simiInfo2 = NULL;
	}
	if (simiInfo3)
	{
		delete simiInfo3;
		simiInfo3 = NULL;
	}
	if (simiInfo4)
	{
		delete simiInfo4;
		simiInfo4 = NULL;
	}
	if (informationShow)
	{
		delete informationShow;
		informationShow = NULL;
	}
}

void MainWindow::changeMode(int mode)
{
	if (this->mode == 3 || this->mode == 2) // ����ͷ������Ƶ������capture�ͷŵ�
	{
		//TODO: ������ͷ
		if (capture.isOpened()) {
			capture.release();
		}
	}
	//�ı�״̬
	this->mode = mode;

	//���  mainShow   ������Ҫ�Ĳ�����
	//this->mainShow->repaint();
	//this->mainShow->clear();
}

/*   �ͷ� - �Լ��ļ����   */
void MainWindow::cleanModel()
{
	if (faceDetector)
	{
		delete faceDetector;
		faceDetector = NULL;
	}
	if (faceRecognition) {
		delete faceRecognition;
		faceRecognition = NULL;
	}
	
}

/**
* @brief MainWindow::openPictureSlot - ���&ʶ�� - ͼƬ
*/
void MainWindow::openPictureSlot()
{
	this->setDataSetInfomations();
	//���ļ��� - ѡ��ͼƬ
	QString fileName = QFileDialog::getOpenFileName(this, SQ("ѡ��ͼƬ"), "", tr("Images (*.png *.bmp *.jpg)"));
	if (fileName.isEmpty())
		return;

	//��ȡͼƬ
	//picture = cv::imread(QS(fileName));
	//imageAndParam.image = cv::imread(QS(fileName));

	faceStructParams.image = cv::imread(QS(fileName));
	//setImage2Label(imageAndParam.image, mainShow);  //������ͼƬ���ص�mainShow��

	//�ı�ģʽ - ͼƬ
	changeMode(1);
	//��鹦��
	checkFunction();
	//setImage2Label(imageAndParam.image, mainShow);  //������ͼƬ���ص�mainShow��
	setImage2Label(faceStructParams.image, mainShow);
}

/**
* @brief MainWindow::openPictureSlot - ���&ʶ�� - ��Ƶ
*/
void MainWindow::openVideoSlot()
{
	this->setDataSetInfomations();
	//���ļ��� - ѡ����Ƶ
	QString fileName = QFileDialog::getOpenFileName(this, SQ("ѡ����Ƶ"), "", tr("Images (*.avi *.mp4)"));
	if (fileName.isEmpty())
		return;
	//�ı�ģʽ - ��Ƶ��
	changeMode(2);

	capture.open(QS(fileName));
	if (!capture.isOpened())
		return;
	//int numberFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
}
/**
* @brief MainWindow::openPictureSlot - ���&ʶ�� - ����ͷ
*/
void MainWindow::openCameraSlot()
{
	this->setDataSetInfomations();
	if (this->mode == 3 &&capture.isOpened()) {
		capture.release();
		openCameraAction->setText(SQ("������ͷ"));
		changeMode(0);
		qDebug() << "mode change :" << mode;
	}
	else //���򣺸ı�mode��������ͷ����������ͷ�ж�ȡ��֡
	{
		openCameraAction->setText(SQ("�ر�����ͷ"));
		changeMode(3); //�ı�modeΪ3������ͷģʽ��

		//capture.open(0);//�򿪵�һ������ͷ
		openVedio();

		if (!capture.isOpened()) {
			qDebug() << "open video erro";
			return;  //���ܴ�����ͷ
		}
	}
}
struct InformationParam  MainWindow::predictFace(cv::Mat img, bool isRegister, struct FaceStructParam::FaceParam &faceParam) {
	struct InformationParam infParam;
	NDArray feature = faceRecognition->makeFeature(img);
	std::string strFeature = featureMapToString(feature);
	// �������ݿ�ȶ�
	if (!isRegister)
	{
		vector<InformationParam> detSet = this->getDataSetInfomations();

		int maxIndex = 0;
		float maxSim = -1, sim;

		if (detSet.size() == 0)
		{
			qDebug() << SQ("���ݿ���û������!");
			return infParam;
		}

		for (int i = 0; i < detSet.size(); i++)
		{
			sim = faceRecognition->caculateSim(strFeature, detSet[i].getStringFeature());
			qDebug() << "���ƶ�:"<<sim;
			if (sim > maxSim)
			{
				maxSim = sim;
				maxIndex = i;
			}
		}
		faceParam.score = maxSim;
		infParam = detSet[maxIndex];
		qDebug() << "maxSim" << maxSim << " name:" << SQ(infParam.getName());
	}
	// �������ݿ��record
	if (this->isStartRecord) {
		sqlSplite->insertRecord(this->getRecordId(), SQ(infParam.getNo()), getActivityId());
	}
	return infParam;
}

/**
* @brief MainWindow::checkFunction
* ������� - this->picture;
* ������� - ����������this->picture;
*/
void MainWindow::checkFunction()
{
	cv::Mat drawMat = faceStructParams.image.clone();
	std::vector<cv::Point2f> points;
	double simScore;
	std::string name;
	qDebug() << this->func << endl;
	if (this->func == 1) //���
	{
		std::vector<bbox_t> boxes = faceDetector->faceDetectBoxes(faceStructParams.image);
		for (int i = 0; i < boxes.size(); i++) {
			struct FaceStructParam::FaceParam faceParam;
			faceParam.detectBox = boxes[i];
			faceStructParams.faceParams.push_back(faceParam);
			drawAllMessages(drawMat, boxes[i], points, simScore, name,false);
		}
		
	}
	else if (this->func == 2) //��� + ʶ��
	{
		//		qDebug() << this->func << endl;
		//
		//		//DONE:��� - ��ȡbbox_t
		//		//test
		//		/*bbox_t tmp;
		//		tmp.x = 1;
		//		tmp.y = 1;
		//		tmp.w = 108;
		//		tmp.h = 154;
		//		std::vector<bbox_t> tt;
		//		tt.push_back(tmp);
		//		imageAndParam.setVBox(tt);*/
		//		/*tmp.x = 1;
		//		tmp.y = 1;
		//		tmp.w = 185;
		//		tmp.h = 239;*/
		//
		//		/*tmp.x = 1;
		//		tmp.y = 1;
		//		tmp.w = 108;
		//		tmp.h = 154;*/
		//
		//		//imageAndParam.vbox.push_back(tmp);
		//		
		qDebug() << this->func << endl;
		std::vector<bbox_t> boxes = faceDetector->faceDetectBoxes(faceStructParams.image);
		bool hasRe;
		int index;
		qDebug() << "boxesNumber" << boxes.size();
		for (int i = 0; i < boxes.size(); i++) {
			struct FaceStructParam::FaceParam faceParam;
			cv::Mat detectImg;
			faceParam.detectBox = boxes[i];
			std::vector<cv::Point2f> landmarkPoints;
			// �ؼ�����
			faceAlignment->landmarkFace(faceStructParams.image, boxes[i], landmarkPoints);
			faceAlignment->transformImgAndPoint(faceStructParams.image, boxes[i],imageSize,detectImg, landmarkPoints);
			// ��ֵ
			faceParam.landmarks = landmarkPoints;
			// ����
			cv::Mat alignFace;
			faceAlignment->alignFace(detectImg, landmarkPoints, alignFace);
			// ʶ��
			reInfParam = this->predictFace(alignFace, false, faceParam);

			faceStructParams.faceParams.push_back(faceParam);

			double sim = (double)faceParam.score;
			hasRe = false;
			if (sim >= simTheta) {
				hasRe = true;
				index = findNoIndex(reInfParam.getNo());
				cv::Mat srcImg = cv::imread(reInfParam.getPictureRoute());
				switch (index)
				{
				case 0:
					if (!detectImg.empty()) {
						setImage2Label(detectImg, subShow12);
					}
					if (!srcImg.empty() && sim >= simTheta) {
						//simiInfo1->setText(QString::number((sim)));
						simiInfo1->setText(SQ(reInfParam.getName()));
						setImage2Label(srcImg, subShow11);
					}
					else {
						simiInfo1->setText(SQ("���ݿ��޴���"));
					}
					break;
				case 1:
					if (!detectImg.empty()) {
						setImage2Label(detectImg, subShow22);

					}
					if (!srcImg.empty() && sim >= simTheta) {
						setImage2Label(srcImg, subShow21);
						simiInfo2->setText(SQ(reInfParam.getName()));
					}
					else {
						simiInfo2->setText(SQ("���ݿ��޴���"));
					}
					break;
				case 2:
					if (!detectImg.empty()) {
						setImage2Label(detectImg, subShow32);

					}
					else {
						simiInfo3->setText(SQ("���ݿ��޴���"));
					}
					if (!srcImg.empty() && sim >= simTheta) {
						setImage2Label(srcImg, subShow31);
						simiInfo3->setText(SQ(reInfParam.getName()));
					}
					else {
						simiInfo3->setText(SQ("���ݿ��޴���"));
					}
					break;
				case 3:
					if (!detectImg.empty()) {
						setImage2Label(detectImg, subShow42);

					}
					if (!srcImg.empty() && sim >= simTheta) {
						setImage2Label(srcImg, subShow41);
						simiInfo4->setText(SQ(reInfParam.getName()));
					}
					else {
						simiInfo4->setText(SQ("���ݿ��޴���"));
					}
					break;
				default:
					break;
				}
			}
			drawAllMessages(drawMat, boxes[i], points, simScore, name, hasRe);
		}
	}
	faceStructParams.image = drawMat.clone();

}
void MainWindow::paintEvent(QPaintEvent *e)
{

	if (this->mode == 3 || this->mode == 2)//����ͷģʽ   ||  ��Ƶģʽ
	{
		if (capture.isOpened()) {
			cv::Mat capImg;
			capture >> capImg;
            this->faceStructParams.image = capImg.clone();//�������ݽṹ


			//auto start = std::chrono::steady_clock::now();

			checkFunction(); //�������ڵ� �����ܡ� ������Ӧ�Ķ���

			//auto end = std::chrono::steady_clock::now();
			//std::chrono::duration<double> spent = end - start;

			//setImage2Label(imageAndParam.image, mainShow);
			setImage2Label(faceStructParams.image, mainShow);
		}
		/*mode = 4;*/
	}
}

/**
* @brief MainWindow::openPictureSlot - �û�ע��
*/
void MainWindow::openRegisterSlot()
{
	if (capture.isOpened()) {
		capture.release();
	}
	RegisterWindow *registerWindow = new RegisterWindow(faceDetector,faceAlignment, faceRecognition);
    registerWindow->show();
}

void MainWindow::quitSlot()
{
	this->close();
}

/**
* @brief MainWindow::detFunctionSlot - ���
*/
void MainWindow::detFunctionSlot()
{
	this->func = 1;
	functionMenu->setTitle(SQ("���"));
}
/**
* @brief MainWindow::detAliRecFunctionSlot - ��� + ���� + ʶ��
*/
void MainWindow::detAliRecFunctionSlot()
{
	this->func = 2;
	functionMenu->setTitle(SQ("���+ʶ��"));
}
bool MainWindow::readXmlData(cv::String xmlFileName) {
	cv::FileStorage fs(xmlFileName, cv::FileStorage::READ | cv::FileStorage::FORMAT_XML);;
	if (fs.isOpened()) {
		float simTheta;
		std::string videoStreamRtsp; 
		int useUSBCamera;
		int USBPort;
		int useGpuRecognize;
		float detectTheta;
		fs["videoStreamRtsp"] >> videoStreamRtsp;
		fs["useUSBCamera"] >> useUSBCamera;
		fs["USBPort"] >> USBPort;
		fs["useGpuRecognize"] >> useGpuRecognize;
		fs["simTheta"] >> simTheta;
		fs["detectTheta"] >> detectTheta;
#ifdef DEBUG_PR
		qDebug() << "videoStreamRtsp:" << SQ(videoStreamRtsp);
		qDebug() << "useUSBCamera:" << useUSBCamera;
		qDebug() << "USBPort:" << USBPort;
		qDebug() << "useGpuRecognize:" << useGpuRecognize;
		qDebug() << "simTheta:" << simTheta;
#endif // DEBUG_PR
		setVideoStreamRtsp(videoStreamRtsp);
		setUseGpuRecognize(useGpuRecognize);
		setUSBPort(USBPort);
		setUseUSBCamera(useUSBCamera);
		setSimTheta(simTheta);
		setDetectTheta(detectTheta);
	}
	else {
		QMessageBox::information(this, SQ("���ز����ļ�����param.xml"), SQ("�����ļ�����ʧ�ܣ������ļ������ڻ��ʽ����"), QMessageBox::Ok); // QObject::trUtf8()
	}
	
}
void MainWindow::addActSlot() {      // ��ӻ�¼�
	QString activityName = QInputDialog::getText(this, SQ("�"),
		SQ("��������:"));
	qDebug() << activityName;
	bool success = sqlSplite->insertActivity(activityName);
	if (success) {
		selectBox->clear();
		std::vector<QString> comBoxStr = sqlSplite->selectActivity();
		for (auto str : comBoxStr) {
			selectBox->addItem(str);
		}
	}
}
void MainWindow::startRecordSlot() {
	if (isStartRecord) {
		startRecordButton->setText(SQ("��ʼ����"));
		this->isStartRecord = false;
	}
	else {
		startRecordButton->setText(SQ("��������"));
		this->isStartRecord = true;
	}
}
void MainWindow::selectBoxIndex(int index) {
	qDebug() << index;
	qDebug() << this->selectBox->currentIndex();
	// �ID
	setActivityId(this->selectBox->currentIndex() + 1);
	// ��¼����
	setRecordId(sqlSplite->getRecordId() + 1);
	qDebug() << "id:"<<getRecordId();
}
