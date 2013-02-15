#include <QGraphicsItem>
#include <QFileDialog>
#include <QDateTime>
#include <QGraphicsTextItem>
//#include "cnode.h"
//#include "figure.h"
#include "imagedraw.h"

ImageDraw::ImageDraw(int argc, char** argv, QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
        , C11node(argc,argv,this)
{
	ui.setupUi(this);
	ImageAreaCount = 0;
	IsUpdateCurrentImg = false;

	connect(this,SIGNAL(SigOnNewImg(QImage)),this,SLOT(SltOnNewImg(QImage)),Qt::QueuedConnection);
	connect(ui.btnPlayPause,SIGNAL(clicked(bool)),this,SLOT(SltOnPlayPauseClick(bool)));
	connect(ui.btnCreate,SIGNAL(clicked(bool)),this,SLOT(SltOnCreateClick(bool)));
	connect(ui.btnPath,SIGNAL(clicked(bool)),this,SLOT(SltOnPathClick(bool)));

	C11node.init();

//	QString fileName = QFileDialog::getOpenFileName(this,
//	     tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
//
//	QImage image;
//	image.load(fileName);
//	SltOnNewImg(image);
}

ImageDraw::~ImageDraw()
{

}

void ImageDraw::CreateNewImageArea(QString imageName)
{
	CloseOpenedImages();

	QRectF rect(0,0,520,428);
	QGraphicsScene* pScene = new QGraphicsScene(rect,this);

	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateStr = dateTime.toString("dd.MM.yyyy");
	QString timeStr = dateTime.toString("hh:mm:ss");
	QString DateTimeStr = dateStr + " " + timeStr;

	CGraphicsView* pCGraphicsView = new CGraphicsView(ImageAreaCount,imageName,DateTimeStr,this);
	ImageAreaCount++;

	pCGraphicsView->setScene(pScene);
	pCGraphicsView->setSceneRect(rect);

	ui.layImages->addWidget(pCGraphicsView);

	ImageAreas.insert(pCGraphicsView->GetId(),pCGraphicsView);

	for(int i=ImageAreaCount-1; i>=0; i--)
	{
		if(i != pCGraphicsView->GetId())
		{
			ui.layImages->removeWidget(ImageAreas[i]);
			ui.layImages->addWidget(ImageAreas[i]);
		}
	}

	connect(pCGraphicsView,SIGNAL(SigOpened(int)),this,SLOT(SltImageAreaOpened(int)));
}

void ImageDraw::CloseOpenedImages()
{
	for(int i=0; i<ImageAreaCount; i++)
	{
		if(ImageAreas[i]->IsOpen())
		{
			ImageAreas[i]->MinimizeView();
		}
	}
}

void ImageDraw::SltImageAreaOpened(int id)
{
	for(int i=0; i<ImageAreaCount; i++)
	{
		if(ImageAreas[i]->GetId() != id)
		{
			ImageAreas[i]->MinimizeView();
		}
	}
}

void ImageDraw::OnImgReceived(QImage image)
{
	std::cout << "Step2" << std::endl;
	QImage myImage(image);
	emit SigOnNewImg(myImage);
	std::cout << "Step3" << std::endl;

}

void ImageDraw::OnImgReceived(std::string fileName)
{
	QImage myImage;
	QString qfileName = QString::fromStdString(fileName);
	myImage.load(qfileName);
	emit SigOnNewImg(myImage);
}

void ImageDraw::OnOccupancyGridReceived(int grid[48][48])
{
	ui.mapWidget->UpdateGrid(grid);
}

void ImageDraw::SltOnNewImg(QImage image)
{
//	QLabel* lbl = new QLabel(this);
//	lbl->setPixmap(QPixmap::fromImage(image));
//	ui.layImages->addWidget(lbl);
	if(!IsUpdateCurrentImg)
	{
//		IsUpdateCurrentImg = true;
		std::cout << "Step4" << std::endl;
		CloseOpenedImages();

		std::cout << "Step5" << std::endl;
		QRectF rect(0,0,image.size().width(),image.size().height());
		QGraphicsScene* pScene = new QGraphicsScene(rect,this);

		QDateTime dateTime = QDateTime::currentDateTime();
		QString dateStr = dateTime.toString("dd.MM.yyyy");
		QString timeStr = dateTime.toString("hh:mm:ss");
		QString DateTimeStr = dateStr + " " + timeStr;

		std::cout << "Step6" << std::endl;
		CGraphicsView* pCGraphicsView = new CGraphicsView(ImageAreaCount,image,DateTimeStr,this);
		ImageAreaCount++;
		std::cout << "Step7" << std::endl;

		pCGraphicsView->setScene(pScene);
		pCGraphicsView->setSceneRect(rect);

		ui.layImages->addWidget(pCGraphicsView);

		ImageAreas.insert(pCGraphicsView->GetId(),pCGraphicsView);

		for(int i=ImageAreaCount-1; i>=0; i--)
		{
			if(i != pCGraphicsView->GetId())
			{
				ui.layImages->removeWidget(ImageAreas[i]);
				ui.layImages->addWidget(ImageAreas[i]);
			}
		}

		connect(pCGraphicsView,SIGNAL(SigOpened(int)),this,SLOT(SltImageAreaOpened(int)));
		std::cout << "Step8" << std::endl;
	}
	else
	{
//		QDateTime dateTime = QDateTime::currentDateTime();
//		QString dateStr = dateTime.toString("dd.MM.yyyy");
//		QString timeStr = dateTime.toString("hh:mm:ss");
//		QString DateTimeStr = dateStr + " " + timeStr;
//
//		CGraphicsView* pCGraphicsView = ImageAreas[ImageAreaCount-1];
//		pCGraphicsView->UpdateImage(image,DateTimeStr);
	}
}

void ImageDraw::SltOnRectClick()
{
/*	CNode* node1 = new CNode(275,290,ui.graphicsView->scene());
	ui.graphicsView->scene()->addItem(node1);
	CNode* node2 = new CNode(435,290,ui.graphicsView->scene());
	ui.graphicsView->scene()->addItem(node2);
	CNode* node3 = new CNode(435,460,ui.graphicsView->scene());
	ui.graphicsView->scene()->addItem(node3);
	CNode* node4 = new CNode(275,460,ui.graphicsView->scene());
	ui.graphicsView->scene()->addItem(node4);

	CFigure* figure = new CFigure(ui.graphicsView->scene());
	figure->AddNode(node1);
	figure->AddNode(node2);
	figure->AddNode(node3);
	figure->AddNode(node4);*/
}

void ImageDraw::SltOnOpenUImgClick()
{
/*	QString fileName = QFileDialog::getOpenFileName(this,
     tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	image.load(fileName);
	image = image.scaled(696,529);
	ui.graphicsView->setBackgroundBrush(image);
	update();*/
}

void ImageDraw::SltOnPlayPauseClick(bool checked)
{
	if(checked)
	{
		QString curMission = ui.cmbMissions->currentText();
		if(!curMission.isEmpty())
		{
			int index=0;
			if(curMission == "Task1")
			{
				index = 0;
			}
			else if(curMission == "Task2")
			{
				index = 1;
			}
			else if(curMission == "Task3")
			{
				index = 2;
			}
			C11node.LoadMission(index);
		}
	}
}

void ImageDraw::SltOnCreateClick(bool checked)
{
	if(checked)
	{
		ui.btnPath->setEnabled(true);
		ui.btnNoGo->setEnabled(true);
		ui.btnDoor->setEnabled(true);
		ui.btnCarInt->setEnabled(true);
	}
	else
	{
		ui.btnPath->setEnabled(true);
		ui.btnNoGo->setEnabled(true);
		ui.btnDoor->setEnabled(true);
		ui.btnCarInt->setEnabled(true);
	}
}

void ImageDraw::SltOnPathClick(bool checked)
{
	if(checked)
	{
		ui.mapWidget->setMode(E_PATH_MODE);
	}
}
