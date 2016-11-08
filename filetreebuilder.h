#ifndef FILETREEBUILDER_H
#define FILETREEBUILDER_H

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>

class FileTreeBuilder : public QObject
{
    Q_OBJECT
public:
    explicit FileTreeBuilder(QObject *parent = 0);

    static QJsonObject buildFileTree(QString baseDirPath);

private:
    static QFileInfoList getDirsOnlyOf(QString baseDirPath);
    static QFileInfoList getFilesOnlyOf(QString baseDirPath);

signals:

public slots:
};

#endif // FILETREEBUILDER_H
