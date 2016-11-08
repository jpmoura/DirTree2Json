#include "filetreebuilder.h"

FileTreeBuilder::FileTreeBuilder(QObject *parent) : QObject(parent)
{
    qDebug("Created");
}

QFileInfoList FileTreeBuilder::getDirsOnlyOf(QString targetDir) {
    QDir directory(targetDir);
    QFileInfoList onlyDir, allFiles;

    allFiles = directory.entryInfoList();

    foreach (QFileInfo file, allFiles) if(file.isDir()) onlyDir.append(file);

    return onlyDir;
}

QFileInfoList FileTreeBuilder::getFilesOnlyOf(QString targetDir) {
    QDir directory(targetDir);
    QFileInfoList onlyFiles, allFiles;

    allFiles = directory.entryInfoList();

    foreach (QFileInfo file, allFiles) if(file.isFile()) onlyFiles.append(file);

    return onlyFiles;
}

QJsonObject FileTreeBuilder::buildFileTree(QString baseDirPath) {
    QJsonObject finalJson;
    QJsonArray currentDirectoryFilesArray;

    QFileInfoList filesList = getFilesOnlyOf(baseDirPath);
    foreach (QFileInfo file, filesList) {
        if(file.fileName() != "") currentDirectoryFilesArray.append(file.fileName());
    }

    if(!currentDirectoryFilesArray.isEmpty()) finalJson.insert("files", currentDirectoryFilesArray);
    else qDebug() << "No files in" << baseDirPath;

    QFileInfoList directoriesList = getDirsOnlyOf(baseDirPath);
    foreach (QFileInfo directory, directoriesList) {

        if(directory.baseName() != "") {

            QJsonObject directoryFileTree = buildFileTree(directory.absoluteFilePath());

            if(!directoryFileTree.isEmpty()) finalJson.insert(directory.baseName(), directoryFileTree);
            else qDebug() << "No directories in" << directory.absoluteFilePath();
        }
    }

    if(directoriesList.isEmpty()) qDebug() << "No directories in" << baseDirPath;

    return finalJson;
}
