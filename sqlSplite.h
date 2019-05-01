/*
�������ݿ��DBMS
sqlite
*/

#ifndef SQLSPLITE_H
#define SQLSPLITE_H

//#include <sqlite3.h>
#include <QtSql\QSqlDatabase>
#include <QtSql\QSqlQuery>
#include <QtSql\QSqlError>
#include <QtDebug>
#include <QtSql\QSqlDriver>
#include <QtSql\QSqlRecord>

#include <vector>

#include "datastructcommon.h"
#include "mxnet_inference.h"
#include "common.h"
using namespace std;

class SqlSplite
{

public:
	SqlSplite();
	~SqlSplite();

	//���룺
	void insert(NDArray featureMap, struct InformationParam &infoParam);
	// ������
	bool insertActivity(const QString activity_name);
	//��ѯ:
	vector<InformationParam> query();
	
	void close();
	// ���
	vector<QString> selectActivity();
	// ���뿼�ڼ�¼��
	bool insertRecord(int recordId,QString no);
	// ��ȡ���ڱ�ID
	int getRecordId();
	bool insertConTitle(int id);
	vector<QString> getAllRecord(int recordId);
	vector<QString> getRecordMessage();

private:
	//����
	void expand();

	//������
	void createTable();


	//���ݿ�	
	QSqlDatabase db;

};

#endif // !
