#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "filetreebuilder.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString outputFile = "FileTree.json";
    QString targetDirectory;
    QString jsonFormat = "indented";
    QStringList arguments = a.arguments();

    if(arguments.size() < 2) {
        qDebug("\t\tUsage\n"
               "FileTree.exe targetDirectory [outputFile] [jsonFormat]\n"
               "targetDirectory: Path of desired folder\n"
               "outputFile (Optional): Path of the output JSON\n"
               "jsonFormat (Optional): compact or indented (intended by default)"
               );
        return 0;
    }
    else {
        targetDirectory = arguments.at(1);
        if(arguments.size() >= 3) outputFile = arguments.at(2);
        if(arguments.size() >= 4) jsonFormat = arguments.at(3);
    }

    qDebug("Starting building...");

    QJsonObject rawFileTree = FileTreeBuilder::buildFileTree(targetDirectory);
    QJsonDocument jsonFile(rawFileTree);

    qDebug("File tree builded, writting the result in file...");

    QFile *output = new QFile(outputFile);
    if(output->open(QFile::WriteOnly)) {
        if(jsonFormat == "compact") output->write(jsonFile.toJson(QJsonDocument::Compact));
        else output->write(jsonFile.toJson(QJsonDocument::Indented));
        output->close();
    }
    else qDebug("Not able to open the file");

    qDebug("Done.");

    return 0;
}
