#include "downloadrecordconfigmanager.h"

DownloadRecordConfigManager::DownloadRecordConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadRecordConfigManager::readBuffer(DownloadRecordList &records)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        const QDomElement &element = nodes.item(i).toElement();

        DownloadRecord record;
        record.m_path = element.attribute("name");
        record.m_time = element.attribute("time");
        record.m_size = element.attribute("size");
        record.m_url = element.attribute("url");
        records << record;
    }
}

void DownloadRecordConfigManager::writeBuffer(const DownloadRecordList &records)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot(TTK_APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "history");

    for(const DownloadRecord &record : qAsConst(records))
    {
        writeDomMutilElement(recordDom, "value", {TTKXmlAttribute("name", record.m_path),
                                                  TTKXmlAttribute("size", record.m_size),
                                                  TTKXmlAttribute("time", record.m_time),
                                                  TTKXmlAttribute("url", record.m_url)});
    }

    save();
}
