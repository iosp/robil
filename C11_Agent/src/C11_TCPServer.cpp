#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "C11_TCPServer.h"

CTcpServer::CTcpServer(QString ipAddress,int port, QObject *parent)
        : QObject(parent)
{
          IpAddress = new  QHostAddress(ipAddress);
          Port = port;
          isConnected = false;
          isWaitToContinue = false;
          MsgIdToContinue = 0;
          DataSizeToContinue = 0;
          SpareToContinue = 0;
          Counter = 0;
          pClientConnection = NULL;
          IsPathComing = false;

          pTcpServer = new QTcpServer(this);
          if (!pTcpServer->listen(QHostAddress::Any,Port))
          {
              std::cout<<"TCP: Connection initialization fail\n";
           return;
          }
          connect(pTcpServer, SIGNAL(newConnection()), this, SLOT(SltOnNewConnection()));
          std::cout<<"TCP: TcpServer on\n";
//          if(pTcpServer->waitForNewConnection(10000))
//            {
//              std::cout<<"true\n";
//            }
//          else
//            {
//              std::cout<<"false\n";
//            }
}

CTcpServer::~CTcpServer()
{
          pTcpServer->close();
          if(IpAddress != NULL)
              {
                delete IpAddress;
              }
}

void CTcpServer::SltOnNewConnection()
{
          std::cout<<"TCP: New connection from operator\n";
          pClientConnection = pTcpServer->nextPendingConnection();
          connect(pClientConnection, SIGNAL(disconnected()),
                   this, SLOT(SltOnDisconnect()));
          connect(pClientConnection, SIGNAL(readyRead()),
                   this, SLOT(SltOnDataReceived()));
          isConnected = true;

}

void CTcpServer::SltOnDisconnect()
{

}

void CTcpServer::SltOnDataReceived()
{
  std::cout<<"TCP: Bytes avaliable: " << pClientConnection->bytesAvailable() << "\n";
  int bufSize;
  short msgId;
  unsigned int dataSize;
  unsigned int counter;
  QDataStream in(pClientConnection);
  in.setByteOrder(QDataStream::LittleEndian);

  while(pClientConnection->bytesAvailable() > 0)
    {
      bufSize = pClientConnection->bytesAvailable();
      if(IsPathComing)
        {
          if(bufSize < DataSizeToContinue)
            {

            }
          else
            {
              IsPathComing = false;
            }
          if(!IsPathComing)
            {
              short pathLength;
              std::vector<StructPoint> points;
              in >> pathLength;
              for(int i=0; i<pathLength; i++)
                {
                  StructPoint point;
                  in >> point.x;
                  in >> point.y;
                  std::cout<<"TCP: Point "<<i<<" is: "<<point.x<<" "<< point.y<<":\n";
                  points.push_back(point);
                }
              emit SigPathUpdated(points);
            }
        }
      else
        {
          if (pClientConnection->bytesAvailable() < (int)sizeof(short))
            {
              return;
            }
          in >> msgId;
          bufSize = pClientConnection->bytesAvailable();
          if (pClientConnection->bytesAvailable() < (int)sizeof(unsigned int))
          {
                  return;
          }
          in >> dataSize;
          std::cout<<"TCP: image coming size = " << dataSize << "\n";
          bufSize = pClientConnection->bytesAvailable();
          if (pClientConnection->bytesAvailable() < (int)sizeof(unsigned int))
          {
                  return;
          }
          in >> counter;
          if(11 == msgId)
            {
              emit SigResume();
              std::cout<<"TCP: Resume received!\n";
            }
          else if(12 == msgId)
            {
              int missionId;
              in >> missionId;
              emit SigLoadMission(missionId);
              std::cout<<"TCP: Load Mission received!\n";
            }
          else if(13 == msgId)
            {
              emit SigPause();
              std::cout<<"TCP: Pause received!\n";
            }
          else if(14 == msgId)
          {
            emit SigHMIResponded();
            std::cout<<"TCP: HMI respended!\n";
          }
          else if(15 == msgId)
            {
              std::cout<<"TCP: Receiving path update!\n";
              IsPathComing = true;
              DataSizeToContinue = dataSize;
            }
          else if(16 == msgId)
            {
              emit SigImageRequest();
              std::cout<<"TCP: ImageRequest received!\n";
            }
          else if(17 == msgId)
            {
              emit SigGridRequest();
              std::cout<<"TCP: GridRequest received!\n";
            }
          else if(18 == msgId)
            {
              emit SigPathRequest();
              std::cout<<"TCP: PathRequest received!\n";
            }
          else if(19 == msgId)
            {
              emit SigAllRequest();
              std::cout<<"TCP: AllRequest received!\n";
            }
          else if(20 == msgId)
            {
              emit SigStopRequest();
              std::cout<<"TCP: Stop received!\n";
            }
          else if(21 == msgId)
            {
              StructPoint goal;
              in >> goal.x;
              in >> goal.y;
              emit SigNewGoalRequest(goal);
              std::cout<<"TCP: New goal received!\n";
            }
          else if(22 == msgId)
            {
              emit SigResetRequest();
              std::cout<<"TCP: Reset received!\n";
            }
          else if(23 == msgId)
		  {
			emit SigGridAndPathRequest();
			std::cout<<"TCP: Reset received!\n";
		  }
        }
    }
}

void CTcpServer::SendImage(QImage img)
{
  std::cout<<"TCP: SendImage\n";
              if(NULL == pClientConnection)
                {
                  std::cout<<"TCP: No connection\n";
                  return;
               }
              StructHeader header;
              header.MessageID = 1;
              header.Counter = Counter;
              Counter++;
//              StructImage msg;
//              QByteArray block;
//              msg.Header.MessageID = 1;
//              msg.Header.DataSize = 0/*sizeof(img)*/;
//              msg.Header.Counter = Counter;
//              std::cout<<"TCP: msg.Header.Counter = Counter\n";
//              msg.Img = img;
//              std::cout<<"msg.Img = img\n";
//              QDataStream out(&block, QIODevice::WriteOnly);
//              out.setByteOrder(QDataStream::LittleEndian);
//              out << img;
//              msg.Header.DataSize = block.size();
//              std::cout<<"TCP: msg.Header.DataSize = " << block.size() << "\n";
//              block.clear();
//              out << msg;
//              pClientConnection->write(block);
              QByteArray block;
              QByteArray block2;
              QDataStream out(&block, QIODevice::WriteOnly);
              out.setByteOrder(QDataStream::LittleEndian);
              QDataStream test(&block2, QIODevice::WriteOnly);
              test.setByteOrder(QDataStream::LittleEndian);
//              out << msgId;
//              pClientConnection->write(block);
              test << img;
              //size = block2.size();
              header.DataSize = block2.size();
              out << header;
              std::cout<<"img size = " << header.DataSize << "\n";
//              pClientConnection->write(block);
              out << img;
              pClientConnection->write(block);
              pClientConnection->flush();
              if(!pClientConnection->waitForBytesWritten())
                {
                  std::cout<<"TCP: Image send timeout\n";
                }
              else
                {
                  std::cout<<"TCP: Image sent\n";
                }
}

void CTcpServer::SendGrid(StructGridData grid)
{
  std::cout<<"TCP: SendGrid\n";
  if(NULL == pClientConnection)
  {
    std::cout<<"TCP: No connection\n";
    return;
  }
  StructHeader header;
  header.MessageID = 2;
  header.DataSize = sizeof(StructGridData);
  header.Counter = Counter;
  Counter++;
  std::cout<<"TCP: Counter++\n";
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setByteOrder(QDataStream::LittleEndian);
  out << header;
  std::cout<<"TCP: out << header";
  out << grid;
  std::cout<<"TCP: out << grid";
  pClientConnection->write(block);
  pClientConnection->flush();
  pClientConnection->waitForBytesWritten();
  std::cout<<"TCP: Grid sent\n";
}

void CTcpServer::SendPath(vector<StructPoint> path)
{
  std::cout<<"TCP: SendPath\n";
    if(NULL == pClientConnection)
    {
      std::cout<<"TCP: No connection\n";
      return;
    }
    StructHeader header;
    header.MessageID = 3;
    header.DataSize = path.size()*sizeof(StructPoint) + sizeof(short);
    header.Counter = Counter;
    Counter++;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out << header;
    short pathLength = path.size();
    out << pathLength;
    for(int i=0; i<pathLength; i++)
    {
        out << path[i];
    }
    pClientConnection->write(block);
    pClientConnection->flush();
    pClientConnection->waitForBytesWritten();
    std::cout<<"TCP: Path sent\n";
}

void CTcpServer::SendHMIResponse()
{
  std::cout<<"TCP: SendHMIResponse\n";
  if(NULL == pClientConnection)
  {
    std::cout<<"TCP: No connection\n";
    return;
  }
  StructHeader header;
  header.MessageID = 4;
  header.DataSize = 0;
  header.Counter = Counter;
  Counter++;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setByteOrder(QDataStream::LittleEndian);
  out << header;
  pClientConnection->write(block);
  pClientConnection->flush();
  pClientConnection->waitForBytesWritten();
  std::cout<<"TCP: HMIResponse sent\n";
}

void CTcpServer::SendExecutionStatusChange(int status)
{
  std::cout<<"TCP: SendExecutionStatusChange\n";
  if(NULL == pClientConnection)
  {
    std::cout<<"TCP: No connection\n";
    return;
  }
  StructHeader header;
  header.MessageID = 5;
  header.DataSize = 0;
  header.Counter = Counter;
  Counter++;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setByteOrder(QDataStream::LittleEndian);
  out << header;
  out << status;
  pClientConnection->write(block);
  pClientConnection->flush();
  pClientConnection->waitForBytesWritten();
  std::cout<<"TCP: SendExecutionStatusChange sent\n";
}

void CTcpServer::SendExecuterStack(QString str)
{
	std::cout<<"TCP: SendExecuterStack\n";
//	std::cout<<"The string is: "<< str.toStdString()<<std::endl;
	if(NULL == pClientConnection)
	  {
	    std::cout<<"TCP: No connection\n";
	    return;
	  }
	StructHeader header;
	  header.MessageID = 31;
	  header.DataSize = str.length();
	  header.Counter = Counter;
	  Counter++;
	  QByteArray block;
	  std::cout<<"TCP: String size = "<<header.DataSize<<"\n";
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setByteOrder(QDataStream::LittleEndian);
	out << header;
	out<<str;
//	string data = str.toStdString();
//	std::cout<<"The string is: "<< data<<std::endl;
//	header.DataSize = strlen(data.data());
	pClientConnection->write(block);
//	pClientConnection->write(data.data());
	pClientConnection->flush();
	pClientConnection->waitForBytesWritten();
	std::cout<<"TCP: SendExecuterStack sent\n";
}

void CTcpServer::SendVRCScoreData(double timeSec, int competionScore, int falls, QString message)
{
//  std::cout<<"TCP: SendVRCScoreData\n";
  if(NULL == pClientConnection)
  {
    std::cout<<"TCP: No connection\n";
    return;
  }
  StructHeader header;
  header.MessageID = 6;
  header.DataSize = 0;
  header.Counter = Counter;
  Counter++;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setByteOrder(QDataStream::LittleEndian);
  out << header;
  out << timeSec << competionScore << falls << message;
  pClientConnection->write(block);
  pClientConnection->flush();
  pClientConnection->waitForBytesWritten();
//  std::cout<<"TCP: SendVRCScoreData sent\n";
}

void CTcpServer::SendDownlink(QString down)
{
  if(NULL == pClientConnection)
  {
    std::cout<<"TCP: No connection\n";
    return;
  }
  StructHeader header;
  header.MessageID = 7;
  header.DataSize = 0;
  header.Counter = Counter;
  Counter++;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setByteOrder(QDataStream::LittleEndian);
  out << header;
  out << down;
  pClientConnection->write(block);
  pClientConnection->flush();
  pClientConnection->waitForBytesWritten();
}

void CTcpServer::SendUplink(QString up)
{
  if(NULL == pClientConnection)
  {
    std::cout<<"TCP: No connection\n";
    return;
  }
  StructHeader header;
  header.MessageID = 8;
  header.DataSize = 0;
  header.Counter = Counter;
  Counter++;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setByteOrder(QDataStream::LittleEndian);
  out << header;
  out << up;
  pClientConnection->write(block);
  pClientConnection->flush();
  pClientConnection->waitForBytesWritten();
}

void CTcpServer::SendRobotData(StructPoint& pos, StructOrientation& orient)
{
	 if(NULL == pClientConnection)
	  {
	    std::cout<<"TCP: No connection\n";
	    return;
	  }
	 StructHeader header;
	header.MessageID = 9;
	header.DataSize = 0;
	header.Counter = Counter;
	Counter++;
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setByteOrder(QDataStream::LittleEndian);
	out << header;
	out << pos.x << pos.y << orient.yaw << orient.pitch << orient.roll;
//	std::cout<<"TCP: Robot data -> "<<pos.x<<pos.y<<orient.yaw<<orient.pitch<<orient.roll<<"\n";
	pClientConnection->write(block);
	pClientConnection->flush();
	pClientConnection->waitForBytesWritten();
}
