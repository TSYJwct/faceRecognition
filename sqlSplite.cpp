#include "sqlSplite.h"
#include <QtSql/qsqldriver.h>

/**
- �������ݿ�
*/
SqlSplite::SqlSplite()
{
	//int rc = sqlite3_open("../database/faceDB.db", &db);
	//if (rc)  //��ʧ��
	//{
	//	TODO:
	//}

	//�������ݿ�

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "faceDB");
	db.setDatabaseName("faceDB.db");

	if (!db.open())
	{
		qDebug() << SQ("�޷��������ݿ�����");
	}
	//������
	createTable();
}
void SqlSplite::createTable()
{
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	QSqlQuery query(db);
	//�������sql���
	char *user = "create table faceInfo(" \
		"NO char(20) primary key not null," \
		"NAME char(30) not null," \
		"COLLEGE char(50) not null," \
		"CLASS char(40) not null," \
		"FEATURE varchar(4096)," \
		"PICTUREROUTE varchar(100));";
	char *activity = "create table activity(" \
		"ID integer primary key AUTOINCREMENT," \
		"NAME varchar(50) not null );";
	char *record = "create table record(" \
		"RECORDID integer not null," \
		"NO char(20) not null," \
		"SIGNDATE timestamp default (datetime('now', 'localtime')),"\
		"FOREIGN KEY(NO) REFERENCES faceInfo(NO)," \
		"FOREIGN KEY(RECORDID) REFERENCES conTitle(RECORDID)," \
		"PRIMARY KEY(RECORDID,NO));";
	char *conTitle = "create table conTitle(" \
		"RECORDID integer primary key  AUTOINCREMENT ," \
		"ID integer not null,"\
		"STARTTIME timestamp default (datetime('now', 'localtime')), " \
		"FOREIGN KEY(ID) REFERENCES activity(ID));";
	bool successUser = query.exec(user);
	bool successActivity = query.exec(activity);
	bool successConTitle = query.exec(conTitle);
	bool successSign = query.exec(record);
	if (successUser){
		qDebug() << SQ("user��ṹ�����ɹ���\n");
	}else{
		qDebug() << SQ("user��ṹ����ʧ��, ���Ѿ����ڣ�\n");
	}
	if (successActivity) {
		qDebug() << SQ("activity��ṹ�����ɹ���\n");
	}
	else {
		qDebug() << SQ("activity��ṹ����ʧ��, ���Ѿ����ڣ�\n");
	}
	if (successSign) {
		qDebug() << SQ("record��ṹ�����ɹ���\n");
	}
	else {
		qDebug() << SQ("record��ṹ����ʧ��, ���Ѿ����ڣ�\n");
	}
	if (successConTitle) {
		qDebug() << SQ("conTitle��ṹ�����ɹ���\n");
	}
	else {
		qDebug() << SQ("conTitle��ṹ����ʧ��, ���Ѿ����ڣ�\n");
	}
}

SqlSplite::~SqlSplite()
{
	close();
}
/*
--����
*/
void SqlSplite::insert(NDArray featureMap, struct InformationParam &infoParam)
{
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	std::string no = infoParam.getNo();
	std::string name = infoParam.getName();
	std::string college = infoParam.getCollege();
	std::string cl = infoParam.getClass();
	std::string pictureRoute = infoParam.getPictureRoute();
	std::string stringFeature = featureMapToString(featureMap);  //datastructcommon.h

	infoParam.setStringFeature(stringFeature);

	//SQL ���
	/*	char *sql = "insert into faceInfo(NO, NAME, COLLEGE, CLASS, FEATURE, PICTURE)" \
	"values(no, name, college, cl, stringFeature, pictureRoute)";
	*/

	//ִ��SQL���
	QSqlQuery query(db);

	query.exec(("select * from faceInfo where NO = " + no).c_str());
	//��������ڴ�ѧ�ţ������
	if (query.next() == NULL)
	{
		qDebug() << "no this NO";
		query.prepare("insert into faceInfo values(?, ?, ?, ?, ?, ?)");
		query.bindValue(0, SQ(no));
		query.bindValue(1, SQ(name));
		query.bindValue(2, SQ(college));
		query.bindValue(3, SQ(cl));
		query.bindValue(4, SQ(stringFeature));
		query.bindValue(5, SQ(pictureRoute));

		//bool success = query.exec(sql);
		bool success = query.exec();
		if (!success)
		{
			QSqlError lastError = query.lastError();
			qDebug() << lastError.driverText() << SQ("����ʧ��");
		}
		else
		{
			qDebug() << "success";
			qDebug() << SQ("����ɹ�!");
		}
	}
	else  //���ڴ�ѧ�ţ�ִ�и��²���
	{
		query.prepare(QString(("update faceInfo set NO=?,NAME=?,COLLEGE=?,CLASS=?,FEATURE=?,PICTUREROUTE=?"
			"where NO=" + no).c_str()));
		query.bindValue(0, SQ(no));
		query.bindValue(1, SQ(name));
		query.bindValue(2, SQ(college));
		query.bindValue(3, SQ(cl));
		query.bindValue(4, SQ(stringFeature));
		query.bindValue(5, SQ(pictureRoute));
		bool success = query.exec();

		if (!success)
		{
			QSqlError lastError = query.lastError();
			qDebug() << lastError.driverText() << SQ("����ʧ��");
		}
		else
		{
			qDebug() << SQ("���³ɹ�!");
		}
	}
}

/*
--��ѯ
*/
vector<InformationParam>SqlSplite::query()
{
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	QSqlQuery query(db);
	char *sql = "select * from faceInfo";
	bool success = query.exec(sql);
	if (!success)
	{
		qDebug() << SQ("��ѯ������Ϣʧ��!");
	}

	QSqlRecord rec = query.record();
	vector<InformationParam> ans;
	struct InformationParam tmp;

	while (query.next())
	{
		tmp.setNo(QS(query.value(0).toString()));
		tmp.setName(QS(query.value(1).toString()));
		tmp.setCollege(QS(query.value(2).toString()));
		tmp.setClass(QS(query.value(3).toString()));
		tmp.setStringFeature(QS(query.value(4).toString()));
		tmp.setPictureRoute(QS(query.value(5).toString()));

		ans.push_back(tmp);
	}
	return ans;
}

/*
	--�ر����ݿ�
*/
void SqlSplite::close()
{
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	db.close();
}

/*
--����
*/
void SqlSplite::expand()
{

}
bool SqlSplite::insertActivity(const QString activity_name) {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	//ִ��SQL���
	bool success;
	std::string name = QS(activity_name);
	qDebug() << activity_name;
	QSqlQuery query(db);
	query.prepare("select * from activity where name = :name");
	query.bindValue(":name", activity_name);   // �����ݵ�ָ����λ��
	query.exec();

	
	if (query.next() == NULL) {
		query.prepare("insert into activity(NAME) values(?)");
		// query.bindValue(0, query.lastInsertId().toInt()+1);
		query.bindValue(0, activity_name);
		success = query.exec();
		if (!success)
		{
			QSqlError lastError = query.lastError();
			qDebug() << lastError.driverText() << SQ("����ʧ��");
		}
		else
		{
			qDebug() << "success";
			qDebug() << SQ("����ɹ�!");
		}
	}
	else {
		qDebug() << SQ("�Ѵ���!");
		success = false;
	}
	return success;
	
}
vector<QString> SqlSplite::selectActivity() {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	QSqlQuery query(db);
	char *sql = "select * from activity";
	bool success = query.exec(sql);
	if (!success)
	{
		qDebug() <<SQ("��ѯ��activity������Ϣʧ��!");
	}
	QSqlRecord rec = query.record();
	std::vector<QString> datas;
	while (query.next())
	{
		
		datas.push_back(query.value(1).toString());
		qDebug() << query.value(1).toString();
	}
	return datas;
}
int SqlSplite::getRecordId() {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
	int max = 0;													//ִ��SQL���
	bool success;
	QSqlQuery query(db);
	char *sql = "select max(RECORDID) from conTitle";
	query.exec(sql);
	while (query.next()) {
		max = query.value(0).toInt();;
		qDebug() << SQ("���ֵ:") << max;
	}
	return max;
}
bool SqlSplite::insertRecord(int recordId, QString no) {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����
														//ִ��SQL���
	bool success;
	QSqlQuery query(db);
	query.prepare("select * from record where RECORDID = :recordId and NO = :no ");
	query.bindValue(":recordId", recordId);   // �����ݵ�ָ����λ��
	query.bindValue(":no", no);
	query.exec();
	if (query.next() == NULL) {
		query.prepare("insert into record(RECORDID,NO) values(?,?)");
		// query.bindValue(0, query.lastInsertId().toInt()+1);
		query.bindValue(0, recordId);
		query.bindValue(1, no);
		success = query.exec();
		if (!success)
		{
			QSqlError lastError = query.lastError();
			qDebug() << lastError.driverText() << SQ("record����ʧ��");
		}
		else
		{
			qDebug() << SQ("record����ɹ�!");
		}
	}
	else {
		qDebug() << SQ("record�Ѵ���!");
		success = false;
	}
	return success;

}
bool SqlSplite::insertConTitle(int id) {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����												//ִ��SQL���
	bool success;
	QSqlQuery query(db);
	query.prepare("insert into conTitle(ID) values(?)");
	// query.bindValue(0, query.lastInsertId().toInt()+1);
	query.bindValue(0, id);
	success = query.exec();
	if (success) {
		qDebug() << "conTitle insert data success";
	}
	else {
		qDebug() << "conTitle insert data fail";
	}
	return success;
}
vector<QString> SqlSplite:: getAllRecord(int recordId){
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����												//ִ��SQL���
	bool success;
	vector<QString>result;
	QSqlQuery query(db);
	QString  sql = "select f.CLASS,f.NAME,r.NO,a.NAME,STARTTIME,SIGNDATE " \
		          "from faceInfo f, conTitle t, record r,activity a " \
	              "where f.NO = r.NO and r.RECORDID = t.RECORDID and " \
                   "t.RECORDID =:recordId and a.ID = t.ID;";
	query.prepare(sql);
	query.bindValue(":recordId", recordId);   // �����ݵ�ָ����λ��
	query.exec();
	while (query.next()) {
		QString data = query.value(0).toString() + "|" + query.value(1).toString() + "|" + query.value(2).toString() \
			+ "|" + query.value(3).toString() + "|" + query.value(4).toString() + "|" +  query.value(5).toString();
		result.push_back(data);
		qDebug()<<SQ("��ѯ��¼")<<data<<"\n";
	}
	return result;
}
vector<QString> SqlSplite::getRecordMessage() {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����												//ִ��SQL���
	bool success;
	vector<QString>result;
	QSqlQuery query(db);
	char * sql = "select RECORDID,NAME,STARTTIME from conTitle c, activity a where c.ID = a.ID";
	success = query.exec(sql);
	if (!success)
	{
		qDebug() << SQ("��ѯ��activity������Ϣʧ��!");
	}
	while (query.next())
	{
		QString data = (query.value(0).toString()) + "|" + (query.value(1).toString()) + "|" + (query.value(2).toString());
		result.push_back(data);
		qDebug() << data;
	}	
	return result;
}
vector<QString> SqlSplite::getFaceInfoNos() {
	QSqlDatabase db = QSqlDatabase::database("faceDB"); //�������ݿ�����												//ִ��SQL���
	bool success;
	vector<QString>result;
	QSqlQuery query(db);
	char * sql = "select CLASS,NAME,NO from faceInfo";
	success = query.exec(sql);
	if (!success)
	{
		qDebug() << SQ("��ѯ��faceInfo No������Ϣʧ��!");
	}
	while (query.next())
	{
		QString data = (query.value(0).toString()) + "|" + (query.value(1).toString()) + "|" + (query.value(2).toString());
		result.push_back(data);
		//qDebug() << data;
	}
	return result;
}