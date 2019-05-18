#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <qstring.h>

#define SQ(str) str2qstr(str)
#define QS(qstr) std::string(qstr2str(QString(qstr)))
// ����������������
inline QString str2qstr(const std::string& str)
{
	return QString::fromLocal8Bit(str.data());
}

inline std::string qstr2str(const QString& qstr)
{
	QByteArray cdata = qstr.toLocal8Bit();
	return std::string(cdata);
}



#endif // COMMON_H
