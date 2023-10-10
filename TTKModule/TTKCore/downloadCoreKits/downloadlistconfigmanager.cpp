#include "downloadlistconfigmanager.h"

DownloadListConfigManager::DownloadListConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadListConfigManager::readBuffer(DownloadItemList &records)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        const QDomElement &element = nodes.item(i).toElement();

        DownloadItem record;
        record.m_url = element.attribute("url");
        record.m_name = element.attribute("name");
        records << record;
    }
}

void DownloadListConfigManager::writeBuffer(const DownloadItemList &records)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot(TTK_APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "list");

    for(const DownloadItem &record : qAsConst(records))
    {
        writeDomMutilElement(recordDom, "value", {TTKXmlAttribute("url", record.m_url),
                                                  TTKXmlAttribute("name", record.m_name)});
    }

    save();
}
